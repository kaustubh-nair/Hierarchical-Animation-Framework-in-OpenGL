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
#include "../include/hash_pair.h"
#include <unordered_map>

class Edge
{
    public:
        unsigned int u;
        unsigned int v;
        unsigned int newPoint;   //midpoint to split edge
        unsigned int sharedPoint1;   //third point of first triangle in the edge
        unsigned int sharedPoint2 = 0;   //third point of second triangle in the edge

        Edge(unsigned int a, unsigned int b, unsigned int c);
        static bool isEdge(unsigned int a, unsigned int b, std::unordered_map<std::pair<unsigned int, unsigned int>, Edge, hash_pair> edges);
        static void computeEdges(std::vector<unsigned int> indices, std::unordered_map<std::pair<unsigned int, unsigned int>, Edge, hash_pair> &edges);

        void split();
};

#endif
