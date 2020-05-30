#ifndef ANIMAL_H
#define ANIMAL_H

#include "../../include/scene_node/mesh_node.h"

class Animal : public MeshNode
{
    public:
        void update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data);
        using MeshNode::MeshNode;
};

#endif
