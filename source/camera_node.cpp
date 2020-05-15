#include "../include/camera_node.h"

CameraNode::CameraNode(int Id, glm::vec3 position, glm::vec3 front, glm::vec3 up)
{
    id = Id;
    updateCameraAttributes(position, front, up);
    lookAt = glm::lookAt(position, front, up);
}

glm::vec3 CameraNode::getPosition()
{
    return position;
}


//TODO REMOVE?
void CameraNode::updateCameraAttributes(glm::vec3 positionVec, glm::vec3 frontVec, glm::vec3 upVec)
{

    position = positionVec;
    front = frontVec;
    up = upVec;
}
