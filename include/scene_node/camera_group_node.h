#ifndef CAMERA_GROUP_NODE_H
#define CAMERA_GROUP_NODE_H

#include "../../include/scene_node/group_node.h"
#include "../../include/scene_node/camera_node.h"

class CameraGroupNode : public GroupNode
{
    public:
        CameraGroupNode(int nodeId);
        CameraNode* getCamera(int camId);
        std::vector<int> leftCamIds;  //TODO: Change to vector of CameraNode*
        std::vector<int> rightCamIds;
};

#endif

