#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "../../include/vertex.h"
#include "../../include/triangle.h"
#include "../../include/shader.h"
#include "../../include/ply_parser.h"



class SceneNode
{
  public:
    SceneNode(std::string meshPath, std::string texturePath, glm::vec3 initialPosition);
    void render(Shader shader);
    void update();
    std::vector<SceneNode> children;

    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;
    unsigned int VAO, VBO, EBO;
    unsigned int texture;
    glm::vec3 position;
    glm::mat4 translationMatrix;
};

#endif
