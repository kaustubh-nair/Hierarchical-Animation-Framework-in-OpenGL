#include "../include/mesh.h"

int ID = 1;
int num_segments = 10;

Mesh::Mesh(std::string filepath, glm::vec3 position, std::string texture)
{
    id = ID;
    selected = false;
    ID++;
    PlyParser parser;
    parser.parse(filepath, vertices, indices); 
    position = position;
    inCircles = parser.inCircles;
    translationMatrix = glm::translate(glm::mat4(1.0f), position);
    scalingMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::mat4(1.0f);
    splatMultipler = 1.0f;
    texturePath = texture;

    // compute and save texture map coordinates
    std::vector<Vertex>::iterator vertex;
    for(vertex = vertices.begin(); vertex < vertices.end(); vertex++)
        vertex->computeTextureCoords();

}

void Mesh::subdivide()
{
    edges.clear();
    Vertex::updateNeighbours(vertices, indices);
    Edge::computeEdges(indices, edges);
    Vertex::subdivide(vertices, indices, edges);
}

void Mesh::setupSplats()
{
    computeInCirleVertices();

    glGenVertexArrays(1 ,&VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, inCircleVertices.size() * sizeof(Vertex), &inCircleVertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void Mesh::generateTextureObject()
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load and generate the texture
    int width, height, nrChannels;
    const char* path = texturePath.c_str();
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void Mesh::setup(int textureRenderingStyle)
{

    generateTextureObject();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));

    setTextureBufferAttribute(textureRenderingStyle);

    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void Mesh::drawSplats(Shader shader)
{
    glm::mat4 model = translationMatrix * rotationMatrix * scalingMatrix;
    shader.setMat4("model", model);
    shader.setVec3("objectColor", 0.5f, 0.1f, 0.1f);
    if(selected)
        shader.setVec3("objectColor", 0.3f, 0.6f, 0.3f);

    glBindVertexArray(VAO); 

    GLint startingElements[fanStartingElements.size()];
    GLint counts[inCircles.size()];
    for(int i=0;i<inCircles.size();i++){counts[i]=num_segments+2;}

    std::copy(fanStartingElements.begin(), fanStartingElements.end(), startingElements);

    glMultiDrawArrays(GL_TRIANGLE_FAN, startingElements, counts, inCircles.size()); // 2 fans
}

void Mesh::draw(Shader shader)
{
    glm::mat4 model = translationMatrix * rotationMatrix * scalingMatrix;
    shader.setMat4("model", model);
    shader.setVec3("objectColor", 0.5f, 0.1f, 0.1f);
    if(selected)
        shader.setVec3("objectColor", 0.3f, 0.6f, 0.3f);

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, texture);
}


int indexCount;
void Mesh::computeInCirleVertices()
{
    indexCount = 0;
    std::vector<InCircle>::iterator inCircle;
    float radius;
    inCircleVertices.clear();

    for(inCircle = inCircles.begin(); inCircle < inCircles.end(); inCircle++)
    {
        radius = this->splatMultipler * inCircle->radius;    
        glm::vec3 normal = inCircle->normal;
        glm::vec3 circlePlane;
        glm::vec3 center = inCircle->center;

        addToInCircles(normal, center, true);

        circlePlane = glm::vec3(normal.z, 0.0f, -normal.x);
        if(circlePlane == glm::vec3(0.0f,0.0f,0.0f))
            circlePlane = glm::vec3(0, normal.z, -normal.y);

        glm::vec3 circleVertex = center + (radius * normalize(circlePlane));
        addToInCircles(normal, circleVertex, false);

        float angle = 360.0f/num_segments;
        for(int i = 1; i < num_segments; i++)
        {
            glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(i*angle), normal);

            glm::vec3 a = glm::vec3(rotationMat * glm::vec4(circleVertex-center,1.0f)) + center;
            addToInCircles(normal, a, false);
        }
        addToInCircles(normal,circleVertex,false);
    }
}

void Mesh::addToInCircles(glm::vec3 normal, glm::vec3 vertex, bool center)
{
    if(center)
        this->fanStartingElements.push_back(indexCount);
    Vertex x;
    x.normal = normal;
    x.position = vertex;
    inCircleVertices.push_back(x);
    indexCount++;
}

void Mesh::rotate(glm::vec2 direction)
{
    glm::vec3 dir = glm::normalize(glm::vec3(direction,1.0f));
    float angle = glm::radians(5.0f);
    float x = dir.x * sin(angle/2);
    float y = dir.y * sin(angle/2);
    float z = dir.z * sin(angle/2);
    float w = cos(angle/2);
    glm::quat q = glm::quat(w,x,y,z);
    glm::mat4 matrix = glm::mat4_cast(q);
    rotationMatrix = matrix * rotationMatrix;
}

void Mesh::translate(glm::vec2 direction)
{
    translationMatrix = glm::translate(translationMatrix, glm::vec3(0.0004f * direction.x, 0.0006f*direction.y, 0.0f));
}

void Mesh::scale(int direction)
{
    if(direction == UP)
        scalingMatrix = glm::scale(scalingMatrix, glm::vec3(1.1,1.1,1.1));
    else if(direction == DOWN)
        scalingMatrix = glm::scale(scalingMatrix, glm::vec3(0.9,0.9,0.9));
}


void Mesh::changeSplatRadius(int direction)
{
    if(direction == UP)
    {
        this->splatMultipler += 0.1f;
        this->setupSplats();
    }
    else if(direction == DOWN)
    {
        this->splatMultipler -= 0.1f;
        this->setupSplats();
    }
}

void Mesh::setTextureBufferAttribute(int textureRenderingStyle)
{
    switch(textureRenderingStyle)
    {
        case CYLINDER_PROJECT:
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)((2*sizeof(glm::vec3)) + (5*sizeof(glm::vec2))));
            break;
        case CYLINDER_NORMAL_FROM_OBJECT:
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)((2*sizeof(glm::vec3)) + (4*sizeof(glm::vec2))));
            break;
        case SPHERICAL_PROJECT:
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)((2*sizeof(glm::vec3)) + (2*sizeof(glm::vec2))));
            break;
        case SPHERICAL_NORMAL_FROM_OBJECT:
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)((2*sizeof(glm::vec3)) + (sizeof(glm::vec2))));
            break;
    }
}
