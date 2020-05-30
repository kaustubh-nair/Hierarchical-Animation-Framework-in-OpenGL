#ifndef HEAD_H
#define HEAD_H

#include "../../include/scene_node/mesh_node.h"

class Head : public MeshNode
{
    public:
        void update(int timer, int event, int eventTargetId, Shader shader, bool isConnection);
        using MeshNode::MeshNode;
        bool userControlled = true;
};

#endif
