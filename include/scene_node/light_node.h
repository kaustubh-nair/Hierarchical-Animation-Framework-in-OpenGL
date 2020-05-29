#ifndef LIGHT_NODE_H
#define LIGHT_NODE_H

#include "../../include/scene_node/scene_node.h"

#include "../../include/vertex.h"
#include "../../include/triangle.h"
#include "../../include/ply_parser.h"


class LightNode : public SceneNode
{
    public:
        LightNode(int nodeId, glm::vec3 nodePos, int lightID, std::string meshPath);
        void render(Shader shader, std::vector<glm::mat4> *stack);
        void update(int timer, int event, int eventTargetId, Shader shader, bool isConnection, GLFWwindow *activeWindow);
        void setup(Shader shader);
    private:
        unsigned int VAO, VBO, EBO;
        glm::vec3 position;
        std::vector<Vertex> vertices;
        std::vector<Triangle> triangles;

        /* index in the shader array */
        /* Note that eventTargetID in update is based on this, since they are sequentially ordered. */
        int lightId;
        bool active = true;
};

#endif
