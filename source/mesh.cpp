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
    translationMatrix = glm::translate(glm::mat4(1.0f), position);
    texturePath = texture;

    Vertex::computeAvgNormals(vertices, triangles);

    // compute and save texture map coordinates
    for(auto vertex = vertices.begin(); vertex < vertices.end(); vertex++)
        vertex->computeTextureCoords();
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
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(Triangle), &triangles[0], GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));

    setTextureBufferAttribute();

    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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
    glDrawElements(GL_TRIANGLES, 3*triangles.size(), GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Mesh::translate(glm::vec2 direction)
{
    translationMatrix = glm::translate(translationMatrix, glm::vec3(0.0004f * direction.x, 0.0006f*direction.y, 0.0f));
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
