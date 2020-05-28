#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/definitions.h"
#include "../include/controller.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"


// problems
// position in mesh_node needs to be update and kept absolute, even though you're only passing relative positions while creation.
// connection needs to be added between camera and personA for move around, but camera and head for lookaround
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

    /* NOTE: Camera nodes should be inserted with sequential ids */

    /* main camera */
    SceneNode *camera = controller.model.addCameraNode(4, 2, origin + (5.0f*z) + x + y, -z, y);
    SceneNode *grass = controller.model.addMeshNode(9, 3, "data/meshes/rectangle.ply", "data/textures/grass.jpg",
                                                    origin, glm::scale(mat, 40.0f * unit), mat);



    SceneNode *personA = controller.model.addMeshNode(10, 3, "data/meshes/body.ply", "data/textures/skin.jpg",
                                                      x + (0.5f*y), mat, mat);

    SceneNode *leftHmdA = controller.model.addCameraNode(5, 2, x +(2.0f*y), z, y);
    SceneNode *rightHmdA = controller.model.addCameraNode(6, 2, x +(2.0f*y), z, y);
    controller.model.addConnection(personA, leftHmdA);
    controller.model.addConnection(personA, rightHmdA);



    SceneNode *personB = controller.model.addMeshNode(12, 3, "data/meshes/body.ply", "data/textures/skin.jpg",
                                                     x + (0.5f*y), mat, mat);

    SceneNode *leftHmdB = controller.model.addCameraNode(7, 2, origin - (10.0f*x), x, y);
    SceneNode *rightHmdB = controller.model.addCameraNode(8, 2, origin - (10.0f*x), x, y);
    controller.model.addConnection(personB, leftHmdB);
    controller.model.addConnection(personB, rightHmdB);



    SceneNode *personC = controller.model.addMeshNode(14, 3, "data/meshes/body.ply", "data/textures/skin.jpg",
                                                     x + (0.5f*y), mat, mat);


    SceneNode *balloon = controller.model.addMeshNode(16, 3, "data/meshes/sphere.ply", "data/textures/red.jpg",
                                                     -z, glm::scale(mat, 4.0f*unit), mat);

    SceneNode *basket = controller.model.addMeshNode(17, 16, "data/meshes/cube.ply", "data/textures/skin.jpg",
                                                     -(1.7f*y), mat, mat);

    SceneNode *animal = controller.model.addMeshNode(18, 16, "data/meshes/cow.ply", "data/textures/black.jpg",
                                                     -(1.7f*y) + (0.3f*x), mat, mat);
    

    SceneNode *bird = controller.model.addMeshNode(19, 3, "data/meshes/humbird.ply", "data/textures/feather.jpg",
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

    controller.run();
    return 0;
}
