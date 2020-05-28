#ifndef MOVABLE_PERSON_H
#define MOVABLE_PERSON_H

#include "../../include/scene_node/mesh_node.h"

class MovablePerson : public MeshNode
{
    public:
        void update(int timer, int event, int eventTargetId, Shader shader, bool isConnection);
};

#endif
