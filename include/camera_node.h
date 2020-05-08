#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H


#include "../include/scene_node.h"

// TODO: Remove all occurances of this.
#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/gtx/string_cast.hpp>


class CameraNode : public SceneNode
{
    public:

        CameraNode(glm::vec3 position, glm::vec3 front, glm::vec3 up);

        void render(Shader shader) {};
        void update() {};
        void updateCameraAttributes(glm::vec3 positionVec, glm::vec3 frontVec, glm::vec3 upVec);
        
        glm::mat4 getViewMatrix();
        glm::vec3 getPosition();

    private:
        glm::vec3 position;
        glm::vec3 up;
        glm::vec3 front;
};

#endif