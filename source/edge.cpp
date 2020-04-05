#include "../include/edge.h"

std::pair<std::pair<unsigned int, unsigned int>, Edge> make_edge_map(unsigned int a, unsigned int b, unsigned int c);


Edge::Edge(unsigned int a, unsigned int b, unsigned int c)
{
    u = a;
    v = b;
    sharedPoint1 = c;
}
void insert_second_shared_point(std::unordered_map<std::pair<unsigned int, unsigned int>, Edge, hash_pair> &edges, 
                                      std::unordered_map<std::pair<unsigned int, unsigned int>, Edge, hash_pair>::iterator itr,
                                      int a)
{
    if((itr->second).sharedPoint2 == 0)
    {
      (itr->second).sharedPoint2 = a;
    }
}


std::unordered_map<std::pair<unsigned int, unsigned int>, Edge, hash_pair>::iterator find_key(unsigned int a, unsigned int b,
                                                     std::unordered_map<std::pair<unsigned int, unsigned int>, Edge, hash_pair> edges)
{
    std::pair <unsigned int, unsigned int> key(a, b);

    auto itr = edges.find(key);
    if(itr != edges.end())
        return itr;
    key = std::make_pair(b, a);

    itr = edges.find(key);
    if(itr != edges.end())
        return itr;
}

bool Edge::isEdge(unsigned int a, unsigned int b,
                  std::unordered_map<std::pair<unsigned int, unsigned int>,
                  Edge, hash_pair> edges)
{
    std::pair <unsigned int, unsigned int> key(a, b);

    if(edges.find(key) != edges.end())
        return true;
    key = std::make_pair(b, a);

    if(edges.find(key) != edges.end())
        return true;
    return false;
}

void Edge::computeEdges(std::vector<unsigned int> indices,
                        std::unordered_map<std::pair<unsigned int, unsigned int>,
                        Edge, hash_pair> &edges)
{
    unsigned int a,b,c;
    for(int i = 0; i < indices.size(); i+=3)
    {
        a = indices[i];
        b = indices[i+1];
        c = indices[i+2];

        if(!Edge::isEdge(a, b, edges))
        {
            std::pair<std::pair<unsigned int, unsigned int>, Edge> edge_map = make_edge_map(a,b,c);
            edges.insert(edge_map);
        }
        else
        {
            insert_second_shared_point(edges, find_key(a, b, edges), c);
        }


        if(!Edge::isEdge(b, c, edges))
        {
            std::pair<std::pair<unsigned int, unsigned int>, Edge> edge_map = make_edge_map(b,c,a);
            edges.insert(edge_map);
        }
        else
        {
            insert_second_shared_point(edges, find_key(b, c, edges), a);
        }

        if(!Edge::isEdge(a, c, edges))
        {
            std::pair<std::pair<unsigned int, unsigned int>, Edge> edge_map = make_edge_map(a,c,b);
            edges.insert(edge_map);
        }
        else
        {
            insert_second_shared_point(edges, find_key(a, c, edges), b);
        }
    }
}

void Edge::split()
{

}

std::pair<std::pair<unsigned int, unsigned int>, Edge> make_edge_map(unsigned int a, unsigned int b, unsigned int c)
{
    Edge edge(a,b,c);
    std::pair<unsigned int, unsigned int> key(a,b);
    std::pair<std::pair<unsigned int, unsigned int>, Edge> edge_map(key, edge);
    return edge_map;
}
