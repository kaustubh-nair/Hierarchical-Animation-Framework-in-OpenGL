#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// TODO: Remove all occurances of this.
#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/gtx/string_cast.hpp>

#include <vector>
#include <string>

#include "../../include/definitions.h"
#include "../../include/shader.h"


class SceneNode
{
    public:
        // TODO: make private?
        std::vector<SceneNode*> children;           // Traversed during render and update.
        std::vector<SceneNode*> connections;        // Traversed during update.

        virtual void render(Shader shader, std::vector<glm::mat4> *stack) = 0;
        virtual void update(int timer, int event, int eventTargetId, Shader shader, bool isConnection, GLFWwindow *activeWindow) = 0;
        virtual void setup(Shader shader) = 0;
        static SceneNode* insertNode(int nodeId, int parentId, SceneNode *newNode, SceneNode *root);
        void addConnection(SceneNode *node);

        int id;

    private:

};

#endif
