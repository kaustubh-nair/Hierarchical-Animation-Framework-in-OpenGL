#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <map>

#include "../include/mesh.h"
#include "../include/lighting.h"

#include "../include/scene_node.h"
#include "../include/mesh_node.h"
#include "../include/camera_node.h"
#include "../include/light_node.h"
#include "../include/group_node.h"
#include "../include/camera_group_node.h"

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
        SceneNode* addGroupNode(int id, int parentId);
        SceneNode* addCameraGroupNode(int id, int parentId);

        SceneNode* addMeshNode(int id, int parentId, std::string meshPath,
                         std::string texturePath, int mappingStyle, glm::vec3 pos,
                         glm::mat4 scalingMat, glm::mat4 rotationMat);

        SceneNode* addCameraNode(int id, int parentId, glm::vec3 position,
                           glm::vec3 front, glm::vec3 up);

        SceneNode* addLightNode(int id, int parentId, glm::vec3 position);
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
