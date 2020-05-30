#include "../../include/scene_node/target_node.h"

void TargetNode::update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data)
{
    this->data = data;
}
