#include "../include/camera_node.h"

CameraNode::CameraNode(int Id, glm::vec3 position, glm::vec3 front, glm::vec3 up)
{
    id = Id;
    updateCameraAttributes(position, front, up);
    updateLookAt();
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

    if(event != NONE)
        updateLookAt();
}

void CameraNode::updateLookAt()
{
    lookAt = glm::lookAt(position, front, up);
}
