#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "../include/mesh.h"

class Scene
{
    public:
        std::vector<Mesh> meshes;
        void add_mesh(Mesh mesh);
};

#endif
