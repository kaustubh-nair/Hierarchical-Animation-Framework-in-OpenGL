#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H


#include "../../include/scene_node/target_node.h"

// TODO: Remove all occurances of this.
#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/gtx/string_cast.hpp>


class CameraNode : public SceneNode
{
    public:
        CameraNode(int Id, int meshID, glm::vec3 positionVec, glm::vec3 frontVec, glm::vec3 upVec);

        void render(Shader shader, std::vector <glm::mat4> *stack) {};
        void update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data, GLFWwindow *activeWindow);
        void setup(Shader shader) {};

        TargetNode *target = nullptr;
        
        glm::mat4 lookAt;

        float yaw;
        float pitch;
        glm::vec3 position;
        glm::vec3 up;
        glm::vec3 front;
        void updateLookAt();
        int meshId;    //Mesh id that uses this camera - change later
    private:
};

#endif
