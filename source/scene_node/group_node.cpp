#include "../../include/scene_node/group_node.h"

GroupNode::GroupNode(int nodeId)
{
    id = nodeId;
}


void GroupNode::render(Shader shader, std::vector <glm::mat4> *stack)
{
    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->render(shader, stack);
}


void GroupNode::setup(Shader shader)
{
    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->setup(shader);
}


void GroupNode::update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data, GLFWwindow *activeWindow)
{
    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->update(timer, event, eventTargetNodeId, shader, isConnection, glm::vec3(0.0f, 0.0f, 0.0f), activeWindow);
}
