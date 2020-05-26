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


void GroupNode::setup(Shader shader)
{
    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->setup(shader);
}


void GroupNode::update(int timer, int event, int eventTargetId, Shader shader, bool isConnection)
{
    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->update(timer, event, eventTargetId, shader, isConnection);
}
