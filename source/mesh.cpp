#include "../include/mesh.h"

int ID = 1;
int num_segments = 10;

Mesh::Mesh(std::string filepath, glm::vec3 position, std::string texture)
{
    id = ID;
    selected = false;
    ID++;
    PlyParser parser;
    parser.parse(filepath, vertices, triangles); 
    position = position;
    inCircles = parser.inCircles;
    translationMatrix = glm::translate(glm::mat4(1.0f), position);
    scalingMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::mat4(1.0f);
    splatMultipler = 1.0f;
    texturePath = texture;

    /* flat shading in scene 3 */
    /* TODO: probably move this into a scene class attribute*/
    setNonIndexedVertices();
    Vertex::computeAvgNormals(vertices, triangles);

    // compute and save texture map coordinates
    std::vector<Vertex>::iterator vertex;
    for(vertex = vertices.begin(); vertex < vertices.end(); vertex++)
        vertex->computeTextureCoords();
}

Vertex Mesh::computeNewVertexPosition(Vertex vertex)
{
    float piTimesTwo = 6.28318530718;
    glm::vec3 neighboursPos = glm::vec3(0.0f, 0.0f, 0.0f);
    auto neighbour = vertex.neighbours.begin();
    int n = vertex.neighbours.size();

    for(; neighbour != vertex.neighbours.end(); neighbour++)
    {
        neighboursPos += vertices[*neighbour].position;
    }
    float beta = (4 - (2*cos(piTimesTwo/n)))/(9*n);

    Vertex newVertex;
    newVertex.position = ((1-(n*beta))*vertex.position) + (beta*neighboursPos);
    newVertex.position = glm::normalize(newVertex.position);
    return newVertex;
}

void Mesh::subdivide()
{
    // Triangles with a shared old edge. Makes edge flipping faster.
    // Map from edge to pair of triangle indices.
    // TODO: change vector to pair?
    std::map<std::pair<unsigned int, unsigned int>, std::vector<unsigned int> > oldEdges;

    Vertex::updateNeighbours(vertices, triangles);


    int n = triangles.size();
    int m = vertices.size();
    // TODO
    Vertex newVertex;
    std::vector<Triangle> newTriangles;
    unsigned int u_index, v_index, w_index, triangle_index;
    Vertex u, v, w;
    Triangle triangle;

    int vertexCounter = vertices.size();
    for(int i = 0; i < n; i++)
    {
        triangle_index = newTriangles.size();
        triangle = triangles[i];
        u_index = triangle.vertices[0];  v_index = triangle.vertices[1];  w_index = triangle.vertices[2];
        u = vertices[u_index];  v = vertices[v_index];  w = vertices[w_index];


        newVertex.position = glm::normalize((u.position + v.position + w.position)/3.0f);

        // vertex counter = index of new vertex
        Triangle newTriangle1(vertexCounter, u_index, v_index);
        newTriangles.push_back(newTriangle1);
        oldEdges[std::minmax(u_index, v_index)].push_back(triangle_index);


        Triangle newTriangle2(vertexCounter, w_index, u_index);
        newTriangles.push_back(newTriangle2);
        oldEdges[std::minmax(u_index, w_index)].push_back(triangle_index+1);

        Triangle newTriangle3(vertexCounter, v_index, w_index);
        newTriangles.push_back(newTriangle3);
        oldEdges[std::minmax(w_index, v_index)].push_back(triangle_index+2);

        vertices.push_back(newVertex);
        vertexCounter++;
    }

    // TODO: change triangles to pointer so you can copy in constant time
    triangles = newTriangles;

    for(int i = 0; i < m; i++)
    {
        vertices[i] = computeNewVertexPosition(vertices[i]);
    }

    // flip edges
    auto itr = oldEdges.begin();
    unsigned int t1_index, t2_index;
    Triangle t1, t2;
    int shared_edge_vertex1, shared_edge_vertex2;
    unsigned int non_shared_vertex_1, non_shared_vertex_2;
    for(; itr != oldEdges.end(); itr++)
    {
        shared_edge_vertex1 = -1;
        shared_edge_vertex2 = -1;
        t1_index = (itr->second)[0];
        t2_index = (itr->second)[1];

        t1 = triangles[t1_index];
        t2 = triangles[t2_index];

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(t1.vertices[i] == t2.vertices[j])
                {
                    if(shared_edge_vertex1 == -1)
                    {
                        shared_edge_vertex1 = t1.vertices[i];
                    }
                    else if(shared_edge_vertex2 == -1)
                    {
                        if(shared_edge_vertex1 != t1.vertices[i])
                            shared_edge_vertex2 = t1.vertices[i];
                    }
                }
            }
        }
        for(int i = 0; i < 3; i++)
        {
            if((t1.vertices[i] != shared_edge_vertex1) and (t1.vertices[i] != shared_edge_vertex2))
                non_shared_vertex_1 = t1.vertices[i];

            if((t2.vertices[i] != shared_edge_vertex1) and (t2.vertices[i] != shared_edge_vertex2))
                non_shared_vertex_2 = t2.vertices[i];
        }

        Triangle newTriangle1(non_shared_vertex_1, non_shared_vertex_2, (unsigned int)shared_edge_vertex1);
        Triangle newTriangle2(non_shared_vertex_2, non_shared_vertex_1, (unsigned int)shared_edge_vertex2);
        triangles[t1_index] = newTriangle1;
        triangles[t2_index] = newTriangle2;

    }


    setNonIndexedVertices();
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

void Mesh::setup()
{

    generateTextureObject();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    if(settings.currentScene == SCENE_3)
    {
        glBufferData(GL_ARRAY_BUFFER, nonIndexedVertices.size() * sizeof(Vertex), &nonIndexedVertices[0], GL_STATIC_DRAW);
    }
    else
    {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(Triangle), &triangles[0], GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    }
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));

    setTextureBufferAttribute();

    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(0);
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
    if(settings.currentScene == SCENE_3)
    {
        glDrawArrays(GL_TRIANGLES, 0, nonIndexedVertices.size());
    }
    else
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 3*triangles.size(), GL_UNSIGNED_INT, 0);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
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

void Mesh::setTextureBufferAttribute()
{
    switch(settings.textureRenderingStyle)
    {
        case CYLINDER_PROJECT:
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)((2*sizeof(glm::vec3)) + (5*sizeof(glm::vec2))));
            glEnableVertexAttribArray(2);
            break;
        case CYLINDER_NORMAL_FROM_OBJECT:
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)((2*sizeof(glm::vec3)) + (4*sizeof(glm::vec2))));
            glEnableVertexAttribArray(2);
            break;
        case SPHERICAL_PROJECT:
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)((2*sizeof(glm::vec3)) + (2*sizeof(glm::vec2))));
            glEnableVertexAttribArray(2);
            break;
        case SPHERICAL_NORMAL_FROM_OBJECT:
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)((2*sizeof(glm::vec3)) + (sizeof(glm::vec2))));
            glEnableVertexAttribArray(2);
            break;
        case NO_TEXTURES:
            break;
    }
}

void Mesh::setNonIndexedVertices()
{
    nonIndexedVertices.clear();
    for(int i = 0; i < triangles.size(); i++)
    {
        nonIndexedVertices.push_back(vertices[triangles[i].vertices[0]]);
        nonIndexedVertices.push_back(vertices[triangles[i].vertices[1]]);
        nonIndexedVertices.push_back(vertices[triangles[i].vertices[2]]);
    }
    Vertex::computeNormals(nonIndexedVertices);
}
