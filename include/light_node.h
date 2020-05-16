#ifndef LIGHT_NODE_H
#define LIGHT_NODE_H

#include "../include/scene_node.h"



class LightNode : public SceneNode
{
    public:
        LightNode(int nodeId);
        void render(Shader shader, std::vector<glm::mat4> *stack);
        void update(int timer, int event, int eventTargetId) {};
        void setup();
    private:
        unsigned int VAO, VBO;
};

#endif
