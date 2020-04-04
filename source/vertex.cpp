#include "../include/vertex.h"

float PI = 3.14159265;

glm::vec2 findCylMapping(glm::vec3 position)
{
    float u = acos(position.x);
    float v = position.z;
    return glm::vec2(u, v);
}

glm::vec2 findSphMapping(glm::vec3 position)
{
    float u = 0.5 + (atan2(position.z, position.x)/(2*PI));
    float v = 0.5 + (position.y * 0.5);
    return glm::vec2(u, v);
}

// parameterize line and solve in cylinder equation
glm::vec2 findCylPointFromObjectNormal(glm::vec3 position, glm::vec3 normal)
{
    float x = position.x; float y = position.y; float z = position.z;
    float v1 = normal.x; float v2 = normal.y; float v3 = normal.z;

    //quadratic in parameter t
    float a = pow(v1, 2) + pow(v2, 2);
    float b = 2*( (x*v1) + (y*v2));
    float c = pow(x, 2) + pow(y, 2) - 0.36;

    float D = sqrt(pow(b, 2) - (4*a*c));

    float t = (-D - b) / (2*a);

    float x_cyl = x + (v1*t);
    float y_cyl = y + (v2*t);
    float z_cyl = z + (v3*t);

    glm::vec3 intersection = glm::vec3(x_cyl, y_cyl, z_cyl);

    // verify direction else return the other solution
    if(glm::normalize(intersection - position) == glm::normalize(normal))
        return findCylMapping(glm::normalize(intersection));

    t = (D - b) / (2*a);
    x_cyl = x + (v1*t);
    y_cyl = y + (v2*t);
    z_cyl = z + (v3*t);

    intersection = glm::vec3(x_cyl, y_cyl, z_cyl);

    return findCylMapping(glm::normalize(intersection));
}


glm::vec2 findSphPointFromObjectNormal(glm::vec3 position, glm::vec3 normal)
{
    float x = position.x; float y = position.y; float z = position.z;
    float v1 = normal.x; float v2 = normal.y; float v3 = normal.z;

    float a = pow(v1, 2) + pow(v2, 2) + pow(v3, 2);
    float b = 2*( (x*v1) + (y*v2) + (z*v3));
    float c = pow(x, 2) + pow(y, 2) + pow(z, 3) - 0.25;

    float D = sqrt(pow(b, 2) - (4*a*c));

    float t = (D - b) / (2*a);

    float x_cyl = x + (v1*t);
    float y_cyl = y + (v2*t);
    float z_cyl = z + (v3*t);

    glm::vec3 intersection = glm::vec3(x_cyl, y_cyl, z_cyl);

    // verify direction else return the other solution
    if(glm::normalize(intersection - position) == glm::normalize(normal))
        return findSphMapping(glm::normalize(intersection));

    t = (D - b) / (2*a);
    x_cyl = x + (v1*t);
    y_cyl = y + (v2*t);
    z_cyl = z + (v3*t);

    intersection = glm::vec3(x_cyl, y_cyl, z_cyl);

    return findSphMapping(glm::normalize(intersection));
}


void Vertex::computeTextureCoords()
{
    //cylTexCoords2 = findCylPointFromObjectNormal(position, normal);
    //cylTexCoords3 = findCylMapping(position);

    //sphTexCoords2 = findSphPointFromObjectNormal(position, normal);
    //sphTexCoords3 = findSphMapping(position);
}

void Vertex::initializeNeighbours(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
{
    int n = indices.size();
    for(int i = 0; i < n; i+=3)
    {
        Vertex a = vertices[indices[i]];
        Vertex b = vertices[indices[i+1]];
        Vertex c = vertices[indices[i+2]];

        a.neighbours.insert(i+1);
        a.neighbours.insert(i+2);

        b.neighbours.insert(i);
        b.neighbours.insert(i+2);

        c.neighbours.insert(i+1);
        c.neighbours.insert(i);

        vertices[indices[i]] = a;
        vertices[indices[i+1]] = b;
        vertices[indices[i+2]] = c;
    }
}
