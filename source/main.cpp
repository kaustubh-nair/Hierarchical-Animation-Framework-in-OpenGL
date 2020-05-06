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

    /* id, parentId */
    controller.addSceneNode(0, 0, meshPaths[0], texturePaths[0], initialPos[0]);
    controller.addSceneNode(1, 0, meshPaths[1], texturePaths[1], initialPos[1]);
    controller.addSceneNode(2, 0, meshPaths[2], texturePaths[2], initialPos[2]);

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
