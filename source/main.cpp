#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/definitions.h"
#include "../include/controller.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"


// problems
// position in mesh_node needs to be update and kept absolute, even though you're only passing relative positions while creation.
// connection needs to be added between camera and person for move around, but camera and head for lookaround
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
    SceneNode *lightGroup = controller.model.addGroupNode(1, 0);   //lights
    SceneNode *cameraGroup = controller.model.addGroupNode(2, 0);   //cameras
    SceneNode *meshGroup = controller.model.addGroupNode(3, 0);   //meshes

    /* NOTE: Camera nodes should be inserted sequentially */
    SceneNode *camera1 = controller.model.addCameraNode(4, 2, origin + (5.0f*z) + x + y, -z, y);
    SceneNode *camera2 = controller.model.addCameraNode(5, 2, origin - (10.0f*x), x, y);



    SceneNode *grass = controller.model.addMeshNode(9, 3, "data/meshes/rectangle.ply", "data/textures/grass.jpg", CYLINDERICAL_MAPPING,
                                                    origin, glm::scale(mat, 40.0f * unit), mat);


    SceneNode *person = controller.model.addMeshNode(6, 3, "data/meshes/body.ply", "data/textures/skin.jpg", CYLINDERICAL_MAPPING,
                                                     x + (0.5f*y), mat, mat);

    SceneNode *head = controller.model.addMeshNode(10, 6, "data/meshes/sphere.ply", "data/textures/face.jpg", SPHERICAL_MAPPING,
                                                   (1.5f*y), glm::scale(mat, 0.12f*unit), glm::rotate(mat, glm::radians(-90.0f), y));

    SceneNode *balloon = controller.model.addMeshNode(7, 3, "data/meshes/sphere.ply", "data/textures/red.jpg", CYLINDERICAL_MAPPING,
                                                     -z, glm::scale(mat, 4.0f*unit), mat);

    SceneNode *basket = controller.model.addMeshNode(8, 7, "data/meshes/cube.ply", "data/textures/skin.jpg", CYLINDERICAL_MAPPING,
                                                     -(1.7f*y), mat, mat);

    SceneNode *animal = controller.model.addMeshNode(11, 7, "data/meshes/cow.ply", "data/textures/black.jpg", CYLINDERICAL_MAPPING,
                                                     -(1.7f*y) + (0.3f*x), mat, mat);
    

    SceneNode *bird = controller.model.addMeshNode(12, 3, "data/meshes/humbird.ply", "data/textures/feather.jpg", CYLINDERICAL_MAPPING,
                                                   -x, glm::scale(mat, 0.5f*unit), mat);

    /*
    controller.model.addMeshNode(10, 3, "data/meshes/beethoven.ply", "data/checkerboard.jpg",
                                 glm::translate(mat, z));

    controller.model.addMeshNode(11, 3, "data/meshes/beethoven.ply", "data/checkerboard.jpg",
                                 glm::translate(mat, -z));

    controller.model.addMeshNode(12, 3, "data/meshes/beethoven.ply", "data/fur.jpg",
                                 glm::translate(mat, origin));
                                 */
    SceneNode *light1 = controller.model.addLightNode(13, 1, origin + (4.0f*y) + x);
    SceneNode *light2 = controller.model.addLightNode(14, 1, origin + (4.0f*y) - x);

    // Connections are traversed during update only.
    controller.model.addConnection(person, camera1);


    controller.run();
    return 0;
}
