#ifndef HEAD_H
#define HEAD_H

#include "../../include/scene_node/mesh_node.h"

class Head : public MeshNode
{
    public:
        void update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data);
        using MeshNode::MeshNode;
        bool userControlled = true;
        float yaw = 90.0f;
        float pitch = 0.0f;
};

#endif
