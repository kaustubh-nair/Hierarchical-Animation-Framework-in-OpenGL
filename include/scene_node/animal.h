#ifndef ANIMAL_H
#define ANIMAL_H

#include "../../include/scene_node/mesh_node.h"

class Animal : public MeshNode
{
    public:
        void update(int timer, int event, int eventTargetId, Shader shader, bool isConnection);
        using MeshNode::MeshNode;
};

#endif
