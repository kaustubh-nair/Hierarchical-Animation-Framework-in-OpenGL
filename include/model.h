#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <map>

#include "../include/mesh.h"
#include "../include/lighting.h"

#include "../include/scene_node/scene_node.h"
#include "../include/scene_node/mesh_node.h"
#include "../include/scene_node/camera_node.h"
#include "../include/scene_node/light_node.h"
#include "../include/scene_node/group_node.h"
#include "../include/scene_node/camera_group_node.h"

class Model
{
    public:
        std::vector<Mesh> meshes;
        SceneNode *sceneRoot = nullptr;

        int firstCameraId = 0;
        int numCameras = 0;
        int numLights = 0;

        Model();
        void setup(Shader shader);

        void addNode(SceneNode *node, int parentId);
        SceneNode* addLightNode(int id, int parentId, glm::vec3 position);
        void addCameraNode(SceneNode *node, int parentId);

        void addConnection(SceneNode *node1, SceneNode *node2);

        CameraNode* getCamera(int camId);
        void render(Shader shader);
        void update(int timer, int event, int eventTargetId, Shader shader);

        void unselect();
        void select(int direction);

        void translate(glm::vec2 direction);

        void drawLighting( Shader shader);

};

#endif
