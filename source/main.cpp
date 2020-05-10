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

    /* NOTE: id = 0 is scene root, which is inserted automatically. */
    /* NOTE: Order of group nodes should not be changed */
    /* id, parentId */
    controller.model.addGroupNode(1, 0);   //lights
    controller.model.addGroupNode(2, 0);   //cameras
    controller.model.addGroupNode(3, 0);   //meshes

    controller.model.addMeshNode(0, 3, "data/teapot.ply", "data/awesomeface.png", glm::vec3(1.0f, 0.0f, -1.0f));
    controller.model.addMeshNode(1, 3, "data/cylinder.ply", "data/fur.jpg", glm::vec3(0.0f, 1.0f, -1.0f));
    controller.model.addMeshNode(2, 3, "data/octahedron.ply", "data/checkerboard.jpg", glm::vec3(0.0f, 0.0f, -1.0f));
    controller.model.addMeshNode(3, 3, "data/octahedron.ply", "data/checkerboard.jpg", glm::vec3(1.0f, 1.0f, -1.0f));

    //controller.model.addCameraNode(3, 0, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    controller.mainLoop();

    return 0;
}
