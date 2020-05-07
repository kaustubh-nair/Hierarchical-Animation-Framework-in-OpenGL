#ifndef LIGHT_NODE_H
#define LIGHT_NODE_H

#include "../../include/scene_node/scene_node.h"



class LightNode : public SceneNode
{
    public:
        void render(Shader shader);
        void update();
};

#endif
