#include "../include/edge.h"

Edge::Edge(unsigned int a, unsigned int b)
{
    u = a;
    v = b;
}

bool Edge::isEdge(unsigned int a, unsigned int b)
{
    return (a == v and b == u) or (b == v and a == u);
}

void Edge::computeEdges(std::vector<unsigned int> indices, std::vector<Edge> &edges)
{
    unsigned int a,b,c;
    for(int i = 0; i < indices.size(); i+=3)
    {
        a = indices[i];
        b = indices[i+1];
        c = indices[i+2];

        edges.push_back(Edge(a,b));
        edges.push_back(Edge(b,c));
        edges.push_back(Edge(a,c));
    }
}

void Edge::split(std::vector<unsigned int> &edges)
{

}
