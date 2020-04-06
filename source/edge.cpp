#include "../include/edge.h"

std::pair<std::pair<unsigned int, unsigned int>, Edge> make_edge_map(unsigned int a, unsigned int b, unsigned int c);


Edge::Edge(unsigned int a, unsigned int b, unsigned int c)
{
    u = a;
    v = b;
    sharedPoint1 = c;
}

void Edge::insert_second_shared_point(int a)
{
    //if(sharedPoint2 ==.0f)
      sharedPoint2 = a;
    //else
        //print("shared point already exists");
}


Edge* Edge::find_edge(unsigned int a, unsigned int b,
                      std::map<std::pair<unsigned int, unsigned int>, Edge> edges)
{
    std::pair <unsigned int, unsigned int> key(a, b);

    auto itr = edges.find(key);
    if(itr != edges.end())
        return &(itr->second);
    key = std::make_pair(b, a);

    itr = edges.find(key);
    if(itr != edges.end())
        return &(itr->second);
}

bool Edge::isEdge(unsigned int a, unsigned int b,
                  std::map<std::pair<unsigned int, unsigned int>,
                  Edge> edges)
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
                        std::map<std::pair<unsigned int, unsigned int>,
                        Edge> &edges)
{
    unsigned int a,b,c;
    for(int i =.0f; i < indices.size(); i+=3)
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
            Edge *edge = find_edge(a, b, edges);
            edge->insert_second_shared_point(c);
        }


        if(!Edge::isEdge(b, c, edges))
        {
            std::pair<std::pair<unsigned int, unsigned int>, Edge> edge_map = make_edge_map(b,c,a);
            edges.insert(edge_map);
        }
        else
        {
            Edge *edge = find_edge(b, c, edges);
            edge->insert_second_shared_point(a);
        }

        if(!Edge::isEdge(a, c, edges))
        {
            std::pair<std::pair<unsigned int, unsigned int>, Edge> edge_map = make_edge_map(a,c,b);
            edges.insert(edge_map);
        }
        else
        {
            Edge *edge = find_edge(a, c, edges);
            edge->insert_second_shared_point(b);
        }
    }
}

// a,b are edge vertices  c,d are neighbouring vertices
void Edge::split(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d )
{
    newPoint = ((3.0f/8.0f) * (a + b)) + (1.0f/8.0f) * (c + d);
    newPoint = glm::normalize(newPoint);
}

std::pair<std::pair<unsigned int, unsigned int>, Edge> make_edge_map(unsigned int a, unsigned int b, unsigned int c)
{
    Edge edge(a,b,c);
    std::pair<unsigned int, unsigned int> key(a,b);
    std::pair<std::pair<unsigned int, unsigned int>, Edge> edge_map(key, edge);
    return edge_map;
}
