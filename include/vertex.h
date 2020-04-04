#ifndef VERTEX_H
#define VERTEX_H

//careful: no multiple declarations for glm allowed
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <cmath>



struct Vertex 
{
    glm::vec3 position;
    glm::vec3 normal;

    glm::vec2 sphTexCoords1;  //normal from sphere to vertex
    glm::vec2 sphTexCoords2;  //normal from vertex to sphere
    glm::vec2 sphTexCoords3;  //vertex to sphere

    glm::vec2 cylTexCoords1;  //normal from cylinder to vertex
    glm::vec2 cylTexCoords2;  //normal from vertex to cylinder
    glm::vec2 cylTexCoords3;  //vertex to cylinder
    std::vector<glm::vec3> face_normals;

    void computeTextureCoords();

};

#endif
