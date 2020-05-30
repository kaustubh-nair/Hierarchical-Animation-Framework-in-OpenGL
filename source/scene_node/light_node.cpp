#include "../../include/scene_node/light_node.h"


LightNode::LightNode(int nodeId, glm::vec3 nodePos, int lightID, std::string meshPath, glm::vec3 Direction, int Type)
{
    id = nodeId;
    position = nodePos;
    lightId = lightID;
    type = Type;
    direction = Direction;

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
    shader.setVec3("lights[" + std::to_string(lightId) + "].dir",direction);
    shader.setFloat("lights[" + std::to_string(lightId) + "].diffuseStrength", 0.6f);  //TODO: set this in main
    shader.setFloat("lights[" + std::to_string(lightId) + "].specularStrength", 0.5f);

    if(type == SPOTLIGHT)
        shader.setInt("lights[" + std::to_string(lightId) + "].type", 1);
    else if(type == POINTLIGHT)
        shader.setInt("lights[" + std::to_string(lightId) + "].type", 0);
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

void LightNode::update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data)
{
    if(event == TOGGLE_LIGHTS)
    {
        if(eventTargetNodeId == lightId)
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

    // if target constrained
    if(target != nullptr)
    {
        direction = glm::normalize(target->data);
        shader.setVec3("lights[" + std::to_string(lightId) + "].dir", direction);
    }
}
