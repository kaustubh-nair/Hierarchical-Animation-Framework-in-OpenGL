#ifndef VERTEX_H
#define VERTEX_H

struct Vertex 
{
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoord;
  std::vector<glm::vec3> face_normals;
};

#endif
