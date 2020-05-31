#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../include/lighting.h"
#include "../include/settings.h"


#include "../include/scene_node/scene_node.h"
#include "../include/scene_node/mesh_node.h"
#include "../include/scene_node/camera_node.h"
#include "../include/scene_node/light_node.h"
#include "../include/scene_node/group_node.h"
#include "../include/scene_node/camera_group_node.h"

extern struct Settings settings;

class Model
{
    public:
        SceneNode *sceneRoot = nullptr;

        int firstCameraId = 0;
        int numCameras = 0;
        int numLights = 0;

        Model();
        void setup(Shader shader);

        void addNode(SceneNode *node, int parentId);
        SceneNode* addLightNode(int id, int parentId, glm::vec3 position,
                                std::string meshPath, glm::vec3 direction, int type);
        void addCameraNode(SceneNode *node, int parentId);

        void addConnection(SceneNode *node1, SceneNode *node2);

        CameraNode* getCamera(int camId);
        CameraGroupNode* getCameraGroup();
        void render(Shader shader);
        void update(int timer, int event, int eventTargetNodeId, Shader shader, GLFWwindow *activeWindow);

        void unselect();
        void select(int direction);

        void translate(glm::vec2 direction);

        void drawLighting( Shader shader);
        void toggleObjectsActive();
        void toggleObjectsInActive();

        void destroyBalloon();

};

#endif
