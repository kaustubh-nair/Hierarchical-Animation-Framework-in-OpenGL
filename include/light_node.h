#ifndef LIGHT_NODE_H
#define LIGHT_NODE_H

#include "../include/scene_node.h"



class LightNode : public SceneNode
{
    public:
        LightNode(int nodeId, glm::vec3 nodePos, int shaderID);
        void render(Shader shader, std::vector<glm::mat4> *stack);
        void update(int timer, int event, int eventTargetId, Shader shader) {};
        void setup(Shader shader);
    private:
        unsigned int VAO, VBO;
        glm::vec3 position;
        int shaderId;        // index in the shader array
};

#endif
