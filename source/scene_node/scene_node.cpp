#include "../../include/scene_node/scene_node.h"

SceneNode::SceneNode(int nodeId, std::string meshPath, std::string texturePath, glm::vec3 initialPosition)
{
    id = nodeId;
    PlyParser parser;
    parser.parse(meshPath, vertices, triangles); 

    position = initialPosition;
    translationMatrix = glm::translate(glm::mat4(1.0f), position);

    //generateTextureObject();

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
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2*sizeof(glm::vec3)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    //glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


// TODO: break recursion stack if node inserted. Convert to iteration?
SceneNode* SceneNode::insertNode(int nodeId, int parentId, std::string meshPath, std::string texturePath, glm::vec3 initialPosition, SceneNode *root )
{
    if(root == nullptr)
        return root;

    if(root->id == parentId)
    {
        if(root->leftChild == nullptr)
            root->leftChild = new SceneNode(nodeId, meshPath, texturePath, initialPosition);
        else
            root->rightChild = new SceneNode(nodeId, meshPath, texturePath, initialPosition);
    }
    else
    {
        root->leftChild = insertNode(nodeId, parentId, meshPath, texturePath, initialPosition, root->leftChild);
        root->rightChild = insertNode(nodeId, parentId, meshPath, texturePath, initialPosition, root->rightChild);
    }
    return root;

}
void SceneNode::update()
{

}

void SceneNode::render(Shader shader)
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
