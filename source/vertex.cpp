#include "../include/vertex.h"

float PI = 3.14159265;



void Vertex::updateNeighbours(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
{
    int n = indices.size();

    for(int i = 0; i < vertices.size(); i++)
        vertices[i].neighbours.clear();

    for(int i = 0; i < n; i+=3)
    {
        int x = indices[i]; int y = indices[i+1]; int z = indices[i+2];

        Vertex a = vertices[x];
        Vertex b = vertices[y];
        Vertex c = vertices[z];

        a.neighbours.insert(y);
        a.neighbours.insert(z);

        b.neighbours.insert(x);
        b.neighbours.insert(z);

        c.neighbours.insert(y);
        c.neighbours.insert(x);

        vertices[x] = a;
        vertices[y] = b;
        vertices[z] = c;
    }
}

void Vertex::subdivide(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::unordered_map<std::pair<unsigned int, unsigned int>, Edge, hash_pair> edges)
{
    std::unordered_map<std::pair<unsigned int, unsigned int>, Edge, hash_pair>::iterator itr;
    for(itr = edges.begin(); itr != edges.end(); itr++)
    {
        Edge edge = itr->second;
        edge.split(vertices[edge.u].position,
                   vertices[edge.v].position,
                   vertices[edge.sharedPoint1].position,
                   vertices[edge.sharedPoint2].position);
    }

    int n = indices.size();

    // insert new vertices
    /*
    for(int i = 0; i < n; i+=3)
    {
        Vertex a = vertices[indices[i]];
        Vertex b = vertices[indices[i+1]];
        Vertex c = vertices[indices[i+2]];
        // add new vertices

    }
    */

    // move old vertices
    n = vertices.size();
    int degree, k;
    float u;
    glm::vec3 neighboursPos;
    std::set <unsigned int>neighbours;
    for(int i = 0; i < n; i++)
    {
        neighboursPos = glm::vec3(0.0f, 0.0f, 0.0f);
        neighbours = vertices[i].neighbours;
        degree = neighbours.size();
        if(degree == 3)
            u = 3.0f/16;
        else
            u = 3.0f/(8*degree);

        std::set<unsigned int>::iterator neighbour;

        for(neighbour = neighbours.begin(); neighbour != neighbours.end(); neighbour++)
        {
            neighboursPos += vertices[*neighbour].position;
        }
        neighboursPos = glm::normalize(neighboursPos);
        vertices[i].newPosition = ((1-(degree*u))*vertices[i].position) + (u*neighboursPos);
    }

    for(int i = 0; i < n; i++)
    {
        vertices[i].position = vertices[i].newPosition;
    }
}

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
