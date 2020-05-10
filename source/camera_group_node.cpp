#include "../include/camera_group_node.h"


CameraGroupNode::CameraGroupNode(int nodeId) : GroupNode(nodeId)
{
    id = nodeId;
}

/* NOTE: Camera heirarchy can only be one level deep */
glm::mat4 CameraGroupNode::getCameraLookAt(int nodeId)
{
    for(auto itr = children.begin(); itr != children.end(); itr++)
    {
        if((*itr)->id == nodeId)
        {
            CameraNode *cam = (CameraNode *) (*itr);
            return cam->getLookat();
        }
    }
}
