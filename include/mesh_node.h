#ifndef MESH_NODE_H
#define MESH_NODE_H

#include "../include/scene_node.h"

#include "../include/stb_image.h"
#include "../include/vertex.h"
#include "../include/triangle.h"
#include "../include/ply_parser.h"



class MeshNode : public SceneNode
{
    public:
        void render(Shader shader, std::vector<glm::mat4> *stack);
        void update(int timer, int event, int eventTargetId, Shader shader);
        void setup(Shader shader);


        MeshNode(int nodeId, std::string meshPath, std::string texturePath,
                 glm::mat4 translationMatrix);


        // TODO remove
        float angle;
    private:
        unsigned int VAO, VBO, EBO;
        unsigned int texture;
        std::vector<Vertex> vertices;
        std::vector<Triangle> triangles;
        glm::mat4 translationMat;
        glm::mat4 rotationMat;
        void generateTextureObject();
        std::string texPath;
};

#endif
