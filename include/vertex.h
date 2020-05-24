#ifndef VERTEX_H
#define VERTEX_H

//careful: no multiple declarations for glm allowed
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <cmath>
#include <map>
#include <set>
#include <iostream>
#include "../include/definitions.h"
#include "../include/triangle.h"



class Vertex 
{
    public:
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 TexCoords;

        std::vector<glm::vec3> face_normals;

        void computeTextureCoords(int mappingStyle);
        static void computeAvgNormals(std::vector<Vertex> &vertices, std::vector<Triangle> &triangles);

};

#endif
