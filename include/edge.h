#ifndef EDGE_H
#define EDGE_H

/*
//careful: no multiple declarations for glm allowed
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
*/

#include <vector>
#include <cmath>
#include <set>
#include <iostream>
#include "../include/definitions.h"

class Edge
{
    public:
        unsigned int u;
        unsigned int v;
        unsigned int newPoint;   //midpoint to split edge

        Edge(unsigned int a, unsigned int b);
        bool isEdge(unsigned int a, unsigned int b);
        static void computeEdges(std::vector<unsigned int> indices, std::vector<Edge> &edges);
        static void split(std::vector<unsigned int> &edges)
};

#endif
