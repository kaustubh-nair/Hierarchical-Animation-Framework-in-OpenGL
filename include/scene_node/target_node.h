#ifndef TARGET_NODE_H
#define TARGET_NODE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../include/scene_node/scene_node.h"


class TargetNode : public SceneNode
{
    public:
        void render(Shader shader, std::vector<glm::mat4> *stack) {};
        void update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data);
        void setup(Shader shader) {};
        TargetNode(int ID) {id = ID;};
        glm::vec3 data;
};

#endif
