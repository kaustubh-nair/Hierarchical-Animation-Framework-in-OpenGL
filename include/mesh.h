#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

#include "../include/ply_parser.h"
#include "../include/vertex.h"
#include "../include/triangle.h"
#include "../include/shader.h"
#include "../include/stb_image.h"
#include "../include/settings.h"


extern int ID;
extern int num_segments;
extern struct Settings settings;

class Mesh {
  public:
    int id;
    bool selected;
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;
    glm::mat4 translationMatrix;
    std::string texturePath;
    unsigned int VAO, VBO, EBO;
    unsigned int texture;
    glm::vec3 position;

    Mesh(std::string filepath, glm::vec3 position, std::string texturePath);
    void setup();
    void draw(Shader shader);
    void translate(glm::vec2 direction);
    void generateTextureObject();
    void computeTextureMapping();
    void setTextureBufferAttribute();
    Vertex computeNewVertexPosition(Vertex vertex);

};


#endif
