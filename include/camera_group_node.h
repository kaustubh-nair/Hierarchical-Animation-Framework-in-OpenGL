#ifndef CAMERA_GROUP_NODE_H
#define CAMERA_GROUP_NODE_H

#include "../include/group_node.h"
#include "../include/camera_node.h"

class CameraGroupNode : public GroupNode
{
    public:
        CameraGroupNode(int nodeId);
        CameraNode* getCamera(int camId);
};

#endif

