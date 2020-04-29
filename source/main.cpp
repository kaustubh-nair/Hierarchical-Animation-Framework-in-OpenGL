#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/definitions.h"
#include "../include/controller.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

void setupMeshes(std::vector<std::string> &filepaths,
                 std::vector<glm::vec3> &meshPos,
                 std::string &texturePath);

int main()
{

    Controller controller;

    std::vector<std::string> filepaths;
    std::vector<glm::vec3> meshPos;
    std::string texturePath;

    setupMeshes(filepaths, meshPos, texturePath);
    controller.setupScene(filepaths, meshPos, texturePath);

    controller.mainLoop();

    return 0;
}


void setupMeshes(std::vector<std::string> &filepaths,
                 std::vector<glm::vec3> &meshPos,
                 std::string &texturePath)
{

    texturePath = "data/checkerboard.jpg";
    filepaths.clear();
    meshPos.clear();
    filepaths.push_back("data/bun_zipper.ply");
    filepaths.push_back("data/teapot.ply");
    filepaths.push_back("data/cylinder.ply");
    filepaths.push_back("data/octahedron.ply");

    meshPos.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
    meshPos.push_back(glm::vec3(1.0f, 0.0f, -1.0f));
    meshPos.push_back(glm::vec3(0.0f, 1.0f, -1.0f));
    meshPos.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
}
