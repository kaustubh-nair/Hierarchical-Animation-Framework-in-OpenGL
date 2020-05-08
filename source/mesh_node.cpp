#include "../include/mesh_node.h"

MeshNode::MeshNode(int nodeId, std::string meshPath, std::string texturePath, glm::vec3 initialPosition)
{
    id = nodeId;

    /* load up vertices and indices */
    PlyParser parser;
    parser.parse(meshPath, vertices, triangles); 

    /* normals*/
    Vertex::computeAvgNormals(vertices, triangles);

    position = initialPosition;

    /* initialize transformation matrices */
    translationMatrix = glm::translate(glm::mat4(1.0f), position);


    /* compute and save texture map coordinates */
    for(auto vertex = vertices.begin(); vertex < vertices.end(); vertex++)
        vertex->computeTextureCoords();

    generateTextureObject(texturePath);
    setupBuffers();
}


void MeshNode::update()
{

}


void MeshNode::render(Shader shader)
{
    //glm::mat4 model = translationMatrix * rotationMatrix * scalingMatrix;
    glm::mat4 model = translationMatrix;
    shader.setMat4("model", model);
    shader.setVec3("objectColor", 0.5f, 0.1f, 0.1f);

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 3*triangles.size(), GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, texture);

    if(leftChild != nullptr)
        leftChild->render(shader);
    if(rightChild != nullptr)
        rightChild->render(shader);
}


void MeshNode::generateTextureObject(std::string texturePath)
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


void MeshNode::setupBuffers()
{
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