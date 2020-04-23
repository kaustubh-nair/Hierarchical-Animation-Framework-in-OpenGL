#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Triangle
{
    public:
        unsigned int vertices[3];
        //TODO fix
        Triangle(unsigned int a, unsigned int b, unsigned int c)
        {
            vertices[0] = a;
            vertices[1] = b;
            vertices[2] = c;
        };
        Triangle() {};
};


#endif
