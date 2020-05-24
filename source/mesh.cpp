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
    texturePath = texture;
    translationMatrix = glm::translate(glm::mat4(1.0f), position);
    rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), position);

    Vertex::computeAvgNormals(vertices, triangles);

    // compute and save texture map coordinates
    //for(auto vertex = vertices.begin(); vertex < vertices.end(); vertex++)
        //vertex->computeTextureCoords();
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

void Mesh::setup(Shader shader)
{

    generateTextureObject();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(Triangle), &triangles[0], GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2*sizeof(glm::vec3)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void Mesh::draw(Shader shader)
{
    //glm::mat4 model = translationMatrix * rotationMatrix * scalingMatrix;
    glm::mat4 model = translationMatrix;
    shader.setMat4("model", model);
    shader.setVec3("objectColor", 0.5f, 0.1f, 0.1f);
    if(selected)
        shader.setVec3("objectColor", 0.3f, 0.6f, 0.3f);

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 3*triangles.size(), GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Mesh::translate(glm::vec2 direction)
{
    translationMatrix = glm::translate(translationMatrix, glm::vec3(0.0004f * direction.x, 0.0006f*direction.y, 0.0f));
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
