#ifndef BALLOON_H
#define BALLOON_H

#include "../../include/scene_node/mesh_node.h"

class Balloon : public MeshNode
{
    public:
        void update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data, GLFWwindow *activeWindow);
        using MeshNode::MeshNode;
};

#endif
