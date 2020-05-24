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





    controller.model.addMeshNode(6, 3, "data/meshes/beethoven.ply", "data/textures/black.png",
                                 glm::translate(mat, -z), mat);


    controller.model.addMeshNode(7, 6, "data/meshes/octahedron.ply", "data/textures/checkerboard.jpg",
                                 glm::translate(mat, -z), mat);

    controller.model.addMeshNode(8, 7, "data/meshes/teapot.ply", "data/textures/rainbow.png",
                                 glm::translate(mat, -z), mat);
    
    controller.model.addMeshNode(9, 8, "data/meshes/rectangle.ply", "data/textures/grass.jpg",
                                 glm::translate(mat, -x), glm::scale(mat, 30.0f * unit));

    /*

    controller.model.addMeshNode(10, 3, "data/meshes/beethoven.ply", "data/checkerboard.jpg",
                                 glm::translate(mat, z));

    controller.model.addMeshNode(11, 3, "data/meshes/beethoven.ply", "data/checkerboard.jpg",
                                 glm::translate(mat, -z));

    controller.model.addMeshNode(12, 3, "data/meshes/beethoven.ply", "data/fur.jpg",
                                 glm::translate(mat, origin));
                                 */
    controller.model.addLightNode(13, 1, origin + z);
    controller.model.addLightNode(14, 1, origin+(3.0f*x));
    controller.model.addLightNode(15, 1, origin+(2.0f*y)-z);
    controller.model.addLightNode(16, 1, origin-(2.0f*x));


    controller.run();
    return 0;
}
