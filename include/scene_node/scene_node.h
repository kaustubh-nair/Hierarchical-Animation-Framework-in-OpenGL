#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>

#include "../../include/definitions.h"
#include "../../include/shader.h"


class SceneNode
{
  public:
    SceneNode *leftChild = nullptr;
    SceneNode *rightChild = nullptr;
    glm::vec3 position;


    virtual void render(Shader shader) = 0;
    virtual void update() = 0;
    static SceneNode* insertNode(int nodeId, int parentId, SceneNode *newNode, SceneNode *root);


  protected:
    int id;

  private:

};

#endif
