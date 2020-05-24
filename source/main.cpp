#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/definitions.h"
#include "../include/controller.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"


int main()
{
    glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 x = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 y = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 z = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 unit = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::mat4 mat = glm::mat4(1.0f);

    Controller controller;

    /* NOTE: id = 0 is scene root, which is inserted automatically. */
    /* NOTE: Order of group nodes should not be changed */
    /* NOTE: Camera heirarchy in scene graph can only be one level deep */

    /* id, parentId */
    controller.model.addGroupNode(1, 0);   //lights
    controller.model.addGroupNode(2, 0);   //cameras
    controller.model.addGroupNode(3, 0);   //meshes

    /* NOTE: Camera nodes should be inserted sequentially */
    controller.model.addCameraNode(4, 2, origin + (5.0f*z) + x, -z, y);
    controller.model.addCameraNode(5, 2, origin - (10.0f*x), x, y);





    controller.model.addMeshNode(6, 3, "data/meshes/cylinder.ply", "data/textures/black.png",
                                 mat, glm::scale(mat, x+y+(4.0f*z)),
                                 mat);


    controller.model.addMeshNode(7, 3, "data/meshes/octahedron.ply", "data/textures/checkerboard.jpg",
                                 glm::translate(mat, -z), mat, mat);

    controller.model.addMeshNode(8, 3, "data/meshes/teapot.ply", "data/textures/rainbow.png",
                                 glm::translate(mat, z), mat, mat);
    
    controller.model.addMeshNode(9, 3, "data/meshes/rectangle.ply", "data/textures/grass.jpg",
                                 glm::translate(mat, -2.0f*y), glm::scale(mat, 60.0f * unit), mat);

    /*
    controller.model.addMeshNode(10, 3, "data/meshes/beethoven.ply", "data/checkerboard.jpg",
                                 glm::translate(mat, z));

    controller.model.addMeshNode(11, 3, "data/meshes/beethoven.ply", "data/checkerboard.jpg",
                                 glm::translate(mat, -z));

    controller.model.addMeshNode(12, 3, "data/meshes/beethoven.ply", "data/fur.jpg",
                                 glm::translate(mat, origin));
                                 */
    controller.model.addLightNode(13, 1, origin + (4.0f*y) + x);
    controller.model.addLightNode(14, 1, origin + (4.0f*y) - x);


    controller.run();
    return 0;
}
