#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <map>

#include "../include/mesh.h"
#include "../include/lighting.h"
#include "../include/scene.h"

class Model
{
    public:
        bool renderSplats;

        Model();
        void setup(std::vector<std::string> filepaths, std::vector<glm::vec3> meshPos,
                   std::vector<std::string> texturePaths, int sceneID);
        void draw(Shader shader, Shader lightingShader, glm::vec3 lightPos);
        void refresh();
        void changeSplatRadius(int direction);

        void unselect();
        void select(int direction);

        void translate(glm::vec2 direction);
        void scale(int direction);
        void rotate(glm::vec2 direction);

        void drawLighting( Shader shader);
        void subdivide();
    private:
        std::map<int, Scene> scenes;

};

#endif
