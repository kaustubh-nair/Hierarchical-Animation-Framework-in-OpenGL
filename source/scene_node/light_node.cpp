#include "../../include/scene_node/light_node.h"


LightNode::LightNode(int nodeId, glm::vec3 nodePos, int lightID, std::string meshPath)
{
    id = nodeId;
    position = nodePos;
    lightId = lightID;

    PlyParser parser;
    parser.parse(meshPath, vertices, triangles); 
}


void LightNode::setup(Shader shader)
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

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    shader.setVec3("lights[" + std::to_string(lightId) + "].Pos",position);
    shader.setFloat("lights[" + std::to_string(lightId) + "].diffuseStrength", 0.6f);  //TODO: set this in main
    shader.setFloat("lights[" + std::to_string(lightId) + "].specularStrength", 0.5f);
}

void LightNode::render(Shader shader, std::vector<glm::mat4> *stack)
{

    glm::mat4 model = glm::translate(glm::mat4(1.0f), position) 
                      * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f));
    shader.setMat4("model", model);

    glBindVertexArray(VAO); 

    glDrawElements(GL_TRIANGLES, 3*triangles.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0); 
}

void LightNode::update(int timer, int event, int eventTargetId, Shader shader, bool isConnection, GLFWwindow *activeWindow)
{
    if(event == TOGGLE_LIGHTS)
    {
        if(eventTargetId == lightId)
        {
            if(active)
            {
                shader.setFloat("lights[" + std::to_string(lightId) + "].diffuseStrength", 0.0f);
                shader.setFloat("lights[" + std::to_string(lightId) + "].specularStrength", 0.0f);
            }
            else
            {
                shader.setFloat("lights[" + std::to_string(lightId) + "].diffuseStrength", 0.5f);
                shader.setFloat("lights[" + std::to_string(lightId) + "].specularStrength", 0.5f);
            }
            active = !active;
        }
    }
}
