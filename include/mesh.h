#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>
#include <cmath>

#include "../include/ply_parser.h"
#include "../include/vertex.h"
#include "../include/triangle.h"
#include "../include/in_circle.h"
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

    /* splat related info */
    std::vector<InCircle> inCircles;
    std::vector<Vertex> inCircleVertices;
    std::vector<GLuint> fanStartingElements;

    Mesh(std::string filepath, glm::vec3 position, std::string texturePath);
    void setup();
    void draw(Shader shader);
    void setupSplats();
    void drawSplats(Shader shader);
    void computeInCirleVertices();
    glm::mat4 translationMatrix;
    glm::mat4 scalingMatrix;
    glm::mat4 rotationMatrix;
    void scale(int direction);
    void translate(glm::vec2 direction);
    void rotate(glm::vec2 direction);
    void changeSplatRadius(int direction);
    void addToInCircles(glm::vec3 normal, glm::vec3 vertex, bool center);
    void generateTextureObject();
    void computeTextureMapping();
    void setTextureBufferAttribute();
    void subdivide();
    Vertex computeNewVertexPosition(Vertex vertex);

    std::string texturePath;
    unsigned int VAO, VBO, EBO;
    unsigned int texture;
    float splatMultipler;
    glm::vec3 position;

};


#endif
