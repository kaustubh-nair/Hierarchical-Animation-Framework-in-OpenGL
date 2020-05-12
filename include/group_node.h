#ifndef GROUP_NODE_H
#define GROUP_NODE_H

#include "../include/scene_node.h"

class GroupNode : public SceneNode
{
    public:
        GroupNode(int nodeId);
        void render(Shader shader, std::vector <glm::mat4> *stack);
        void update() {};
        void setup();
};
#endif
