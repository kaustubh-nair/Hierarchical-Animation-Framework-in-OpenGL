#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/definitions.h"
#include "../include/controller.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"


int main()
{

    Controller controller;

    /* id, parentId */
    controller.model.addMeshNode(0, 0, "data/teapot.ply", "data/awesomeface.png", glm::vec3(1.0f, 0.0f, -1.0f));
    controller.model.addMeshNode(1, 0, "data/cylinder.ply", "data/fur.jpg", glm::vec3(0.0f, 1.0f, -1.0f));
    controller.model.addMeshNode(2, 0, "data/octahedron.ply", "data/checkerboard.jpg", glm::vec3(0.0f, 0.0f, -1.0f));
    controller.model.addMeshNode(3, 0, "data/octahedron.ply", "data/checkerboard.jpg", glm::vec3(1.0f, 1.0f, -1.0f));

    //controller.model.addCameraNode(3, 0, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    controller.mainLoop();

    return 0;
}
