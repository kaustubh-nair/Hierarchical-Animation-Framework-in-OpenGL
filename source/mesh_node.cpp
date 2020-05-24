#include "../include/mesh_node.h"

MeshNode::MeshNode(int nodeId, std::string meshPath, std::string texturePath,
                   glm::mat4 translationMatrix, glm::mat4 scalingMatrix,
                   glm::mat4 rotationMatrix)
{
    id = nodeId;

    /* load up vertices and indices */
    PlyParser parser;
    parser.parse(meshPath, vertices, triangles); 

    /* normals*/
    Vertex::computeAvgNormals(vertices, triangles);

    texPath = texturePath;

    /* initialize transformation matrix */
    translationMat = translationMatrix;
    rotationMat = rotationMatrix;
    scalingMat = scalingMatrix;


    /* compute and save texture map coordinates */
    for(auto vertex = vertices.begin(); vertex < vertices.end(); vertex++)
        vertex->computeTextureCoords();
}


void MeshNode::update(int timer, int event, int eventTargetId, Shader shader)
{
    /*
    if(timer > 1000)
    {
        angle += 1.0f;
        rotationMat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f,1.0f,1.0f));
    }
    */
}


void MeshNode::render(Shader shader, std::vector<glm::mat4> *stack)
{
    glm::mat4 model = glm::mat4(1.0f);

    stack->push_back(translationMat);
    stack->push_back(rotationMat);
    stack->push_back(scalingMat);

    for(auto i = stack->begin(); i != stack->end(); i++)
        model = model * (*i);

    shader.setMat4("model", model);

    glBindVertexArray(VAO); 
    glBindTexture(GL_TEXTURE_2D, texture);

    glDrawElements(GL_TRIANGLES, 3*triangles.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0); 
    glBindTexture(GL_TEXTURE_2D, 0);

    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->render(shader, stack);

    stack->pop_back();
    stack->pop_back();
    stack->pop_back();
}


void MeshNode::generateTextureObject()
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
    const char* path = texPath.c_str();
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
    glBindTexture(GL_TEXTURE_2D, 0);
}


void MeshNode::setup(Shader shader)
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

    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->setup(shader);

}
