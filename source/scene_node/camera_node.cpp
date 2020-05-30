#include "../../include/scene_node/camera_node.h"

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


void CameraNode::update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data, GLFWwindow *activeWindow)
{
    //TODO Remove?
    if((eventTargetNodeId == id) || isConnection)
    {
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
            (*itr)->update(timer, event, eventTargetNodeId, shader, true, position, activeWindow);
    }

    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->update(timer, event, eventTargetNodeId, shader, false, position, activeWindow);
}


void CameraNode::updateLookAt()
{
    lookAt = glm::lookAt(position, position + front, up);
}
