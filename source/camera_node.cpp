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


void CameraNode::update(int timer, int event, int eventTargetId, Shader shader)
{
    //TODO Remove?
    if(eventTargetId != id)
        return;

    float sensitivity = 0.5f;

    if(event == MOVE_FORWARD)
        position -= sensitivity * glm::normalize(position - front);

    else if(event == MOVE_BACKWARD)
        position += sensitivity * glm::normalize(position - front);
    
    else if(event == MOVE_RIGHT)
        position -= sensitivity * glm::normalize(glm::cross((position - front), up));

    else if(event == MOVE_LEFT)
        position += sensitivity * glm::normalize(glm::cross((position - front), up));


    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->update(timer, event, eventTargetId, shader);
}


void CameraNode::updateLookAt()
{
    lookAt = glm::lookAt(position, front, up);
}
