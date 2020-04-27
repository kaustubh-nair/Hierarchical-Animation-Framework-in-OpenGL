#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <map>

#include "../include/mesh.h"
#include "../include/lighting.h"

class Model
{
    public:
        bool renderSplats;
        std::vector<Mesh> meshes;

        Model();
        void setup(std::vector<std::string> filepaths, std::vector<glm::vec3> meshPos,
                   std::string texturePath);
        void draw(Shader shader);
        void drawLighting(Shader shader, Shader lightingShader);
        void refresh();
        void changeSplatRadius(int direction);

        void unselect();
        void select(int direction);

        void translate(glm::vec2 direction);
        void scale(int direction);
        void rotate(glm::vec2 direction);

        void drawLighting( Shader shader);
        void subdivide();

};

#endif
