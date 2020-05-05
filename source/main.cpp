#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/definitions.h"
#include "../include/controller.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

void setupMeshes(std::vector<std::string> &meshPaths,
                 std::vector<std::string> &texturePaths,
                 std::vector<glm::vec3> &initialPos);

int main()
{

    Controller controller;

    std::vector<std::string> meshPaths;
    std::vector<std::string> texturePaths;
    std::vector<glm::vec3> initialPos;

    setupMeshes(meshPaths, texturePaths, initialPos);

    //for(int i = 0; i < meshPaths.size(); i++)
    for(int i = 0; i < 1; i++)
        controller.addSceneNode(i, meshPaths[i], texturePaths[i], initialPos[i]);

    controller.mainLoop();

    return 0;
}


void setupMeshes(std::vector<std::string> &meshPaths,
                 std::vector<std::string> &texturePaths,
                 std::vector<glm::vec3> &initialPos)
{

    meshPaths.clear();
    initialPos.clear();
    texturePaths.clear();

    meshPaths.push_back("data/teapot.ply");
    texturePaths.push_back("data/checkerboard.jpg");
    initialPos.push_back(glm::vec3(1.0f, 0.0f, -1.0f));

    meshPaths.push_back("data/bun_zipper.ply");
    texturePaths.push_back("data/checkerboard.jpg");
    initialPos.push_back(glm::vec3(1.0f, 1.0f, -1.0f));

    meshPaths.push_back("data/cylinder.ply");
    texturePaths.push_back("data/checkerboard.jpg");
    initialPos.push_back(glm::vec3(0.0f, 1.0f, -1.0f));

    meshPaths.push_back("data/octahedron.ply");
    texturePaths.push_back("data/checkerboard.jpg");
    initialPos.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
}
