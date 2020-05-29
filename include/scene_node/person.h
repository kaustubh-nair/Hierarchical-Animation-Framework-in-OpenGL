#ifndef PERSON_H
#define PERSON_H

#include "../../include/scene_node/mesh_node.h"

class Person : public MeshNode
{
    public:
        void update(int timer, int event, int eventTargetId, Shader shader, bool isConnection, GLFWwindow *activeWindow);
        using MeshNode::MeshNode;
};

#endif

