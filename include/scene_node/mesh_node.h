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
        void render(Shader shader, std::vector<glm::mat4> *stack);
        void update(int timer, int event, int eventTargetId, Shader shader, bool isConnection);
        void setup(Shader shader);


        MeshNode(int nodeId, std::string meshPath, std::string texturePath,
                   glm::vec3 pos, glm::mat4 scalingMatrix,
                   glm::mat4 rotationMatrix);

    private:
        unsigned int VAO, VBO, EBO;
        unsigned int texture;
        std::vector<Vertex> vertices;
        std::vector<Triangle> triangles;
        void generateTextureObject();
        std::string texPath;

        glm::mat4 translationMat;
        glm::mat4 rotationMat;
        glm::mat4 scalingMat;

        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
};

#endif
