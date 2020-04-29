#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <map>

#include "../include/mesh.h"
#include "../include/lighting.h"

class Model
{
    public:
        std::vector<Mesh> meshes;

        void setup(std::vector<std::string> filepaths, std::vector<glm::vec3> meshPos,
                   std::string texturePath);
        void draw(Shader shader);
        void drawLighting(Shader shader, Shader lightingShader);
        void refresh();

        void unselect();
        void select(int direction);

        void translate(glm::vec2 direction);

        void drawLighting( Shader shader);

};

#endif
