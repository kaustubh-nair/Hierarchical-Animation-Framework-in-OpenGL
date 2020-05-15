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
        std::vector<Vertex> vertices;
        std::vector<Triangle> triangles;
        unsigned int VAO, VBO, EBO;
        unsigned int texture;
        
        void render(Shader shader, std::vector<glm::mat4> *stack);
        void update(int event, int eventTargetId);
        void setup();


        // TODO: make private
        MeshNode(int nodeId, std::string meshPath, std::string texturePath,
                 glm::mat4 translationMatrix);


    private:
        glm::mat4 translationMat;
        void generateTextureObject();
        std::string texPath;
};

#endif
