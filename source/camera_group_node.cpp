#include "../include/camera_group_node.h"


CameraGroupNode::CameraGroupNode(int nodeId) : GroupNode(nodeId)
{
    id = nodeId;
}

/* NOTE: Camera heirarchy can only be one level deep */
CameraNode* CameraGroupNode::getCamera(int camId)
{
    for(auto itr = children.begin(); itr != children.end(); itr++)
    {
        if((*itr)->id == camId)
        {
            CameraNode *cam = (CameraNode *) (*itr);
            return cam;
        }
    }
    return nullptr;
}
