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
        void addGroupNode(int id, int parentId);
        void addCameraGroupNode(int id, int parentId);

        void addMeshNode(int id, int parentId, std::string meshPath,
                         std::string texturePath, int mappingStyle, glm::mat4 translationMat,
                         glm::mat4 scalingMat, glm::mat4 rotationMat);

        void addCameraNode(int id, int parentId, glm::vec3 position,
                           glm::vec3 front, glm::vec3 up);

        void addLightNode(int id, int parentId, glm::vec3 position);

        CameraNode* getCamera(int camId);
        void render(Shader shader);
        void update(int timer, int event, int eventTargetId, Shader shader);

        void unselect();
        void select(int direction);

        void translate(glm::vec2 direction);

        void drawLighting( Shader shader);

};

#endif
