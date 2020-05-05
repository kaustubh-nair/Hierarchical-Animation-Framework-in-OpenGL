#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <map>

#include "../include/mesh.h"
#include "../include/lighting.h"
#include "../include/scene_node/scene_node.h"

class Model
{
    public:
        std::vector<Mesh> meshes;
        SceneNode *sceneGraph = nullptr;


        void addSceneNode(int id, std::string meshPath, std::string texturePath, glm::vec3 initialPos);
        void draw(Shader shader);
        void drawLighting(Shader shader, Shader lightingShader);
        void refresh();

        void unselect();
        void select(int direction);

        void translate(glm::vec2 direction);

        void drawLighting( Shader shader);

};

#endif
