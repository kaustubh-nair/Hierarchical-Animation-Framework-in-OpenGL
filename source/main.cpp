#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/definitions.h"
#include "../include/controller.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

void setupMeshes(std::vector<std::string> &filepaths,
                 std::vector<glm::vec3> &meshPos,
                 std::string &texturePath, int scene);

int main()
{

    Controller controller;

    std::vector<std::string> filepaths;
    std::vector<glm::vec3> meshPos;
    std::string texturePath;

    /* meshes for three parts in different model instances (model == scene)*/
    /* TODO: multi thread?? */
    setupMeshes(filepaths, meshPos, texturePath, SCENE_1);
    controller.setupScene(filepaths, meshPos, texturePath);

    setupMeshes(filepaths, meshPos, texturePath, SCENE_2);
    controller.setupScene(filepaths, meshPos, texturePath);

    setupMeshes(filepaths, meshPos, texturePath, SCENE_3);
    controller.setupScene(filepaths, meshPos, texturePath);

    controller.mainLoop();

    return 0;
}


void setupMeshes(std::vector<std::string> &filepaths,
                 std::vector<glm::vec3> &meshPos,
                 std::string &texturePath, int scene)
{


    texturePath = "data/checkerboard.jpg";
    filepaths.clear();
    meshPos.clear();
    switch(scene)
    {
        case SCENE_1:
            {
                // loading 9 spheres
                float dist = 1.2f;
                for(int i = -1; i < 2; i++)
                {
                    for(int j = -1; j < 2; j++)
                    {
                        filepaths.push_back("data/sphere.ply");
                        meshPos.push_back(glm::vec3(dist * i, dist * j, -5.0f));
                    }
                }
                break;
            }

        case SCENE_2:
            {
                filepaths.push_back("data/bun_zipper.ply");
                filepaths.push_back("data/teapot.ply");
                filepaths.push_back("data/cylinder.ply");
                filepaths.push_back("data/octahedron.ply");

                meshPos.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
                meshPos.push_back(glm::vec3(1.0f, 0.0f, -1.0f));
                meshPos.push_back(glm::vec3(0.0f, 1.0f, -1.0f));
                meshPos.push_back(glm::vec3(0.0f, 0.0f, -1.0f));

                break;
            }

        case SCENE_3:
            {
                filepaths.push_back("data/octahedron.ply");
                filepaths.push_back("data/tetrahedron.ply");

                meshPos.push_back(glm::vec3(1.0f, 0.0f, -6.0f));
                meshPos.push_back(glm::vec3(1.0f, 1.0f, -6.0f));
                break;
            }
                
    }

}
