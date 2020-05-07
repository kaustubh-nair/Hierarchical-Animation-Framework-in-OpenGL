#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H

#include "../../include/scene_node/scene_node.h"



class CameraNode : public SceneNode
{
    public:
        void render(Shader shader);
        void update();
};

#endif
