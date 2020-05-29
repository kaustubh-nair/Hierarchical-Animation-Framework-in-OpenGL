#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/definitions.h"
#include "../include/controller.h"


#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#include "../include/scene_node/bird.h"
#include "../include/scene_node/balloon.h"
#include "../include/scene_node/animal.h"
#include "../include/scene_node/basket.h"
#include "../include/scene_node/person.h"
#include "../include/scene_node/movable_person.h"

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

    /* NOTE: Id order of group nodes should not be changed */

    /* id, parentId */
    SceneNode *lightGroup = new GroupNode(1);
    SceneNode *cameraGroup = new GroupNode(2);
    SceneNode *meshGroup = new GroupNode(3);

    /* NOTE: Camera nodes should be inserted with sequential ids */

    /* main camera */
    SceneNode *camera = new CameraNode(4, origin + (5.0f*z) + x + y, -z - origin = (5.0f*z) - x - y, y);
    SceneNode *grass = new MeshNode(9, "data/meshes/rectangle.ply", "data/textures/grass.jpg",
                                  origin, glm::scale(mat, 40.0f * unit), mat);


    SceneNode *personA  = new Person(10, "data/meshes/body.ply",
                                     "data/textures/skin.jpg",
                              x + (0.5f*y), mat, mat);

    SceneNode *leftHmdA = new CameraNode(5, x +(2.0f*y), z, y);
    SceneNode *rightHmdA = new CameraNode(6, x +(2.0f*y), z, y);


    SceneNode *personB = new Person(12, "data/meshes/body.ply", "data/textures/skin.jpg",
                                                     x + (0.5f*y), mat, mat);

    SceneNode *leftHmdB = new CameraNode(7, origin - (10.0f*x), x, y);
    SceneNode *rightHmdB = new CameraNode(8, origin - (10.0f*x), x, y);


    SceneNode *personC = new MovablePerson(14, "data/meshes/body.ply", "data/textures/skin.jpg",
                                                     x + (0.5f*y), mat, mat);

    SceneNode *balloon = new Balloon(16, "data/meshes/sphere.ply", "data/textures/red.jpg",
                                                     -z, glm::scale(mat, 4.0f*unit), mat);
    SceneNode *basket = new Basket(17, "data/meshes/cube.ply", "data/textures/skin.jpg",
                                                     -(1.7f*y), mat, mat);
    SceneNode *animal = new Animal(18, "data/meshes/cow.ply", "data/textures/black.jpg",
                                                     -(1.7f*y) + (0.3f*x), mat, mat);

    SceneNode *bird = new Bird(19, "data/meshes/humbird.ply", "data/textures/feather.jpg",
                                                   -x, glm::scale(mat, 0.5f*unit), mat);


    /* NOTE: id = 0 is scene root, which is inserted automatically. */

    /* id, parentId */
    controller.model.addNode(lightGroup, 0);   //lights
    controller.model.addNode(cameraGroup, 0);   //cameras
    controller.model.addNode(meshGroup, 0);   //meshes

    /* NOTE: Camera nodes should be inserted with sequential ids */

    /* main camera */
    controller.model.addCameraNode(camera, 2);
    controller.model.addNode(grass, 3);


    controller.model.addNode(personA, 3);


    controller.model.addCameraNode(leftHmdA, 2);
    controller.model.addCameraNode(rightHmdA, 2);
    controller.model.addConnection(personA, leftHmdA);
    controller.model.addConnection(personA, rightHmdA);


    controller.model.addNode(personB, 3);

    controller.model.addCameraNode(leftHmdB, 2);
    controller.model.addCameraNode(rightHmdB, 2);
    controller.model.addConnection(personB, leftHmdB);
    controller.model.addConnection(personB, rightHmdB);



    controller.model.addNode(personC, 3);
    controller.model.addNode(balloon, 3);
    controller.model.addNode(basket, 16);
    controller.model.addNode(animal, 16);
    controller.model.addNode(bird, 3);

    SceneNode *light1 = controller.model.addLightNode(13, 1, origin + (4.0f*y) + x);
    SceneNode *light2 = controller.model.addLightNode(14, 1, origin + (4.0f*y) - x);


    controller.run();
    return 0;
}

void Person::update(int timer, int event, int eventTargetId, Shader shader, bool isConnection)
{
    if((id == eventTargetId) || isConnection)
    {
        float sensitivity = 0.5f;

        if(event == MOVE_FORWARD)
        {
            position -= sensitivity * glm::normalize(position - front);
            translationMat = glm::translate(glm::mat4(1.0f), position);
        }

        else if(event == MOVE_BACKWARD)
        {
            position += sensitivity * glm::normalize(position - front);
            translationMat = glm::translate(glm::mat4(1.0f), position);
        }

        else if(event == MOVE_RIGHT)
        {
            position -= sensitivity * glm::normalize(glm::cross((position - front), up));
            translationMat = glm::translate(glm::mat4(1.0f), position);
        }

        else if(event == MOVE_LEFT)
        {
            position += sensitivity * glm::normalize(glm::cross((position - front), up));
            translationMat = glm::translate(glm::mat4(1.0f), position);
        }


        for(auto itr = connections.begin(); itr != connections.end(); itr++)
            (*itr)->update(timer, event, eventTargetId, shader, true);
    }

    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->update(timer, event, eventTargetId, shader, false);

}

void MovablePerson::update(int timer, int event, int eventTargetId, Shader shader, bool isConnection) {};
void Bird::update(int timer, int event, int eventTargetId, Shader shader, bool isConnection) {};
void Animal::update(int timer, int event, int eventTargetId, Shader shader, bool isConnection) {};
void Basket::update(int timer, int event, int eventTargetId, Shader shader, bool isConnection) {};
void Balloon::update(int timer, int event, int eventTargetId, Shader shader, bool isConnection) {};
