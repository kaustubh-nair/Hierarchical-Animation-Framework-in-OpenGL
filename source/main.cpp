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
    /* NOTE: Camera heirarchy in scene graph can only be one level deep */

    /* id, parentId */
    controller.model.addGroupNode(1, 0);   //lights
    controller.model.addGroupNode(2, 0);   //cameras
    controller.model.addGroupNode(3, 0);   //meshes

    controller.model.addCameraNode(4, 2, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    controller.model.addCameraNode(5, 2, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    controller.model.addMeshNode(6, 3, "data/teapot.ply", "data/awesomeface.png", glm::vec3(1.0f, 0.0f, -1.0f));
    controller.model.addMeshNode(7, 3, "data/cylinder.ply", "data/fur.jpg", glm::vec3(0.0f, 1.0f, -1.0f));
    controller.model.addMeshNode(8, 3, "data/octahedron.ply", "data/checkerboard.jpg", glm::vec3(0.0f, 0.0f, -1.0f));
    controller.model.addMeshNode(9, 3, "data/octahedron.ply", "data/checkerboard.jpg", glm::vec3(1.0f, 1.0f, -1.0f));


    controller.run();

    return 0;
}
