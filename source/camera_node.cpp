#include "../include/camera_node.h"

CameraNode::CameraNode(int Id, glm::vec3 positionVec, glm::vec3 frontVec, glm::vec3 upVec)
{
    id = Id;
    updateLookAt();
    yaw = 90.0f;
    pitch = 0.0f;
    position = positionVec;
    front = frontVec;
    up = upVec;
}


void CameraNode::update(int event, int eventTargetId)
{
    if(eventTargetId != id)
        return;

    float sensitivity = 0.5f;

    if(event == MOVE_FORWARD)
        position += sensitivity * front;

    else if(event == MOVE_BACKWARD)
        position -= sensitivity * front;
    
    else if(event == MOVE_RIGHT)
        position += sensitivity * glm::normalize(glm::cross(front, up));

    else if(event == MOVE_LEFT)
        position -= sensitivity * glm::normalize(glm::cross(front, up));
}


void CameraNode::updateLookAt()
{
    lookAt = glm::lookAt(position, front, up);
}
