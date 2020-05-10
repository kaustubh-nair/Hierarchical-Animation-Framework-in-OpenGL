#include "../include/camera_group_node.h"


CameraGroupNode::CameraGroupNode(int nodeId) : GroupNode(nodeId)
{
    id = nodeId;
}

glm::mat4 CameraGroupNode::getCameraLookAt(int nodeId)
{
    return glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
