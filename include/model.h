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

class Model
{
    public:
        std::vector<Mesh> meshes;
        SceneNode *sceneGraph = nullptr;


        void addMeshNode(int id, int parentId, std::string meshPath,
                         std::string texturePath, glm::vec3 initialPos);

        void addCameraNode(int id, int parentId, glm::vec3 position,
                           glm::vec3 front, glm::vec3 up);

        glm::mat4 getCameraLookAt(int camId);
        void render(Shader shader);
        void drawLighting(Shader shader, Shader lightingShader);
        void refresh();

        void unselect();
        void select(int direction);

        void translate(glm::vec2 direction);

        void drawLighting( Shader shader);

};

#endif
