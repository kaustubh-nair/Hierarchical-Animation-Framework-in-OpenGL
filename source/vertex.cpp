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
    float v = 0.5 - (asin(position.y)/PI);
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


void Vertex::computeTextureCoords(int id)
{
    // WARNING: head nodes hard coded for now
    if(id == 100 || id == 101 || id == 102)
        TexCoords = findSphPointFromObjectNormal(position, normal);
    else
        TexCoords = findCylPointFromObjectNormal(position, normal);
}

void Vertex::computeAvgNormals(std::vector<Vertex> &vertices, std::vector<Triangle> &triangles)
{
    auto itr = vertices.begin();
    for(; itr != vertices.end(); itr++)
    {
        itr->face_normals.clear();
    }

    // TODO check if declaring inside decreases performace
    Vertex a,b,c;
    unsigned int x,y,z;
    Triangle triangle;
    for(int i = 0; i < triangles.size(); i++)
    {
        triangle = triangles[i];
        x = triangle.vertices[0];   a = vertices[x];
        y = triangle.vertices[1];   b = vertices[y];
        z = triangle.vertices[2];   c = vertices[z];


        glm::vec3 normal = glm::normalize( glm::cross(b.position - a.position, c.position - a.position) );

        a.face_normals.push_back(normal);
        b.face_normals.push_back(normal);
        c.face_normals.push_back(normal);

        vertices[x] = a;
        vertices[y] = b;
        vertices[z] = c;
    }


    auto vertex = vertices.begin();
    std::vector<glm::vec3>::iterator normal;

    for(; vertex < vertices.end(); vertex++)
    {
        glm::vec3 vec_normal = glm::vec3(0.0f, 0.0f, 0.0f);

        for(normal = vertex->face_normals.begin(); normal < vertex->face_normals.end(); normal++)
            vec_normal = vec_normal + *normal;

        vertex->normal = glm::normalize(vec_normal);
    }
}
