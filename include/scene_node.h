#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// TODO: Remove all occurances of this.
#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/gtx/string_cast.hpp>

#include <vector>
#include <string>

#include "../include/definitions.h"
#include "../include/shader.h"


class SceneNode
{
    public:
        std::vector<SceneNode*> children;

        virtual void render(Shader shader, std::vector<glm::mat4> *stack) = 0;
        virtual void update() = 0;
        virtual void setup() = 0;
        static SceneNode* insertNode(int nodeId, int parentId, SceneNode *newNode, SceneNode *root);

        int id;

    private:

};

#endif
