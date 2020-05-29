#ifndef BALLOON_H
#define BALLOON_H

#include "../../include/scene_node/mesh_node.h"

class Balloon : public MeshNode
{
    public:
        void update(int timer, int event, int eventTargetId, Shader shader, bool isConnection);
        using MeshNode::MeshNode;
};

#endif
