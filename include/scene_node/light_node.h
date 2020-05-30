#ifndef LIGHT_NODE_H
#define LIGHT_NODE_H

#include "../../include/scene_node/target_node.h"

#include "../../include/vertex.h"
#include "../../include/triangle.h"
#include "../../include/ply_parser.h"


class LightNode : public SceneNode
{
    public:
        LightNode(int nodeId, glm::vec3 nodePos, int lightID, std::string meshPath, glm::vec3 Direction, int Type);
        void render(Shader shader, std::vector<glm::mat4> *stack);
        void update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data, GLFWwindow *activeWindow);
        void setup(Shader shader);

        TargetNode *target = nullptr;
    private:
        unsigned int VAO, VBO, EBO;
        glm::vec3 position;
        glm::vec3 direction;
        std::vector<Vertex> vertices;
        std::vector<Triangle> triangles;

        /* index in the shader array */
        /* Note that eventTargetNodeID in update is based on this, since they are sequentially ordered. */
        int lightId;
        bool active = true;
        int type;
};

#endif
