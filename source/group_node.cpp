#include "../include/group_node.h"

GroupNode::GroupNode(int nodeId)
{
    id = nodeId;
}


void GroupNode::render(Shader shader, std::vector <glm::mat4> *stack)
{
    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->render(shader, stack);
}

void GroupNode::setup()
{
    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->setup();
}
