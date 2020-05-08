#ifndef MESH_NODE_H
#define MESH_NODE_H

#include "../../include/scene_node/scene_node.h"

#include "../../include/stb_image.h"
#include "../../include/vertex.h"
#include "../../include/triangle.h"
#include "../../include/ply_parser.h"



class MeshNode : public SceneNode
{
    public:
        std::vector<Vertex> vertices;
        std::vector<Triangle> triangles;
        unsigned int VAO, VBO, EBO;
        unsigned int texture;
        glm::mat4 translationMatrix;
        
        void render(Shader shader);
        void update();


        // TODO: make private
        MeshNode(int nodeId, std::string meshPath, std::string texturePath, glm::vec3 initialPosition);

    private:
        void generateTextureObject(std::string texturePath);
        void setupBuffers();
};

#endif
