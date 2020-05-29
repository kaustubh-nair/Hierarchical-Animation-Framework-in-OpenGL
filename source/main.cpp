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
#include "../include/scene_node/head.h"
#include "../include/scene_node/movable_person.h"


// constants 
glm::vec3 ORIGIN = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 X = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 Y = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 Z = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 UNIT = glm::vec3(1.0f, 1.0f, 1.0f);
glm::mat4 MAT = glm::mat4(1.0f);

// problems
// position in mesh_node needs to be update and kept absolute, even though You're onlY passing relative positions while creation.
// connection needs to be added between camera and personA for move around, but camera and head for lookaround
int main()
{

    Controller controller;

    /* NOTE: Id order of group nodes should not be changed */

    /* id, parentId */
    SceneNode *lightGroup = new GroupNode(1);
    SceneNode *cameraGroup = new GroupNode(2);
    SceneNode *meshGroup = new GroupNode(3);

    /* NOTE: Camera nodes should be inserted with sequential ids */

    /* main camera */
    SceneNode *camera = new CameraNode(4, ORIGIN + (5.0f*Z) + Y, -Z - ORIGIN - (5.0f*Z) - X - Y, Y);
    SceneNode *grass = new MeshNode(9, "data/meshes/rectangle.ply", "data/textures/grass.jpg",
                                  ORIGIN, glm::scale(MAT, 40.0f * UNIT), MAT, MAT);


    SceneNode *personA  = new Person(10, "data/meshes/body.ply",
                                     "data/textures/skin.jpg",
                              X + (0.5f*Y), MAT, MAT, MAT);

    SceneNode *leftHmdA = new CameraNode(5, (0.5f*Y)+ (0.2f*X), Z, Y);
    SceneNode *rightHmdA = new CameraNode(6, (0.5f*Y)- (0.2f*X), Z, Y);
    SceneNode *headA = new Head(100, "data/meshes/sphere.ply", "data/textures/face.jpg",
                                  (0.5f*Y), MAT, MAT, glm::scale(MAT, 0.2f*UNIT));


    SceneNode *personB = new Person(12, "data/meshes/body.ply", "data/textures/skin.jpg",
                                                     -X + (0.5f*Y), MAT, MAT, MAT);

    SceneNode *leftHmdB = new CameraNode(7, (0.5f*Y)+ (0.2f*X), Z, Y);
    SceneNode *rightHmdB = new CameraNode(8, (0.5f*Y)- (0.2f*X), Z, Y);
    SceneNode *headB = new Head(100, "data/meshes/sphere.ply", "data/textures/face.jpg",
                                  (0.5f*Y), MAT, MAT, glm::scale(MAT, 0.2f*UNIT));


    SceneNode *personC = new MovablePerson(14, "data/meshes/body.ply", "data/textures/skin.jpg",
                                                     (0.5f*Y), MAT, MAT, MAT);
    SceneNode *headC = new Head(100, "data/meshes/sphere.ply", "data/textures/face.jpg",
                                  (0.5f*Y), MAT, MAT, glm::scale(MAT, 0.2f*UNIT));

    SceneNode *balloon = new Balloon(16, "data/meshes/balloon.ply", "data/textures/purple.jpeg",
                                         ORIGIN + Y, MAT, MAT, glm::scale(MAT, 3.0f*UNIT));
    SceneNode *basket = new Basket(17, "data/meshes/sphere.ply", "data/textures/skin.jpg",
                                         ORIGIN, MAT, MAT, MAT);
    SceneNode *animal = new Animal(18, "data/meshes/cow.ply", "data/textures/black.jpg",
                                         ORIGIN, MAT, MAT, MAT);

    SceneNode *bird = new Bird(19, "data/meshes/humbird.ply", "data/textures/feather.jpg",
                                        -X, glm::scale(MAT, 0.5f*UNIT), MAT, MAT);


    /* NOTE: id = 0 is scene root, which is inserted autoMATicallY. */

    /* id, parentId */
    controller.model.addNode(lightGroup, 0);   //lights
    controller.model.addNode(cameraGroup, 0);   //cameras
    controller.model.addNode(meshGroup, 0);   //meshes

    /* NOTE: Camera nodes should be inserted with sequential ids */

    /* main camera */
    controller.model.addCameraNode(camera, 2);
    controller.model.addNode(grass, 3);


    controller.model.addNode(personA, 3);
    controller.model.addNode(headA, 10);


    controller.model.addCameraNode(leftHmdA, 2);
    controller.model.addCameraNode(rightHmdA, 2);
    controller.model.addConnection(personA, leftHmdA);
    controller.model.addConnection(personA, rightHmdA);


    controller.model.addNode(personB, 3);
    controller.model.addNode(headB, 12);

    controller.model.addCameraNode(leftHmdB, 2);
    controller.model.addCameraNode(rightHmdB, 2);
    controller.model.addConnection(personB, leftHmdB);
    controller.model.addConnection(personB, rightHmdB);



    controller.model.addNode(personC, 3);
    controller.model.addNode(headC, 14);
    controller.model.addNode(balloon, 3);
    controller.model.addNode(basket, 16);
    controller.model.addNode(animal, 16);
    controller.model.addNode(bird, 3);

    SceneNode *light1 = controller.model.addLightNode(13, 1, ORIGIN + (4.0f*Y) + (3.0f*X), "data/meshes/sphere.ply");
    SceneNode *light2 = controller.model.addLightNode(14, 1, ORIGIN + (4.0f*Y) - (3.0f*X), "data/meshes/sphere.ply");


    controller.run();
    return 0;
}

int time(int seconds)
{
    return 60 * seconds;  //assume 60fps
}

void Person::update(int timer, int event, int eventTargetId, Shader shader, bool isConnection, GLFWwindow *activeWindow)
{
    if((id == eventTargetId) || isConnection)
    {
        float sensitivitY = 0.5f;

        if(event == MOVE_FORWARD)
        {
            position -= sensitivitY * glm::normalize(position - front);
            translationMat = glm::translate(glm::mat4(1.0f), position);
        }

        else if(event == MOVE_BACKWARD)
        {
            position += sensitivitY * glm::normalize(position - front);
            translationMat = glm::translate(glm::mat4(1.0f), position);
        }

        else if(event == MOVE_RIGHT)
        {
            position -= sensitivitY * glm::normalize(glm::cross((position - front), up));
            translationMat = glm::translate(glm::mat4(1.0f), position);
        }

        else if(event == MOVE_LEFT)
        {
            position += sensitivitY * glm::normalize(glm::cross((position - front), up));
            translationMat = glm::translate(glm::mat4(1.0f), position);
        }


        for(auto itr = connections.begin(); itr != connections.end(); itr++)
            (*itr)->update(timer, event, eventTargetId, shader, true, activeWindow);
    }
    // TODO: add else here?
    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->update(timer, event, eventTargetId, shader, false, activeWindow);
}

void MovablePerson::update(int timer, int event, int eventTargetId, Shader shader, bool isConnection, GLFWwindow *activeWindow) {};
void Bird::update(int timer, int event, int eventTargetId, Shader shader, bool isConnection, GLFWwindow *activeWindow) {};
void Animal::update(int timer, int event, int eventTargetId, Shader shader, bool isConnection, GLFWwindow *activeWindow) {};
void Basket::update(int timer, int event, int eventTargetId, Shader shader, bool isConnection, GLFWwindow *activeWindow) {};

void Head::update(int timer, int event, int eventTargetId, Shader shader, bool isConnection, GLFWwindow *activeWindow)
{
    // look around

    static double oldX = 0.0, oldY = 0.0;

    double x, y;
    glfwGetCursorPos(activeWindow, &x, &y);

    float xoffset = x - oldX;
    float yoffset = y - oldY;
    oldX = x;
    oldY = y;

    float sensitivity = 0.2;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = -sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(direction);

    glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));

    rotationMat = glm::rotate(MAT, glm::radians(45.0f), front);

    for(auto itr = connections.begin(); itr != connections.end(); itr++)
        (*itr)->update(timer, event, eventTargetId, shader, true, activeWindow);
}


void Balloon::update(int timer, int event, int eventTargetId, Shader shader, bool isConnection, GLFWwindow *activeWindow)
{
    if(timer > time(4))
    {
        translationMat = glm::translate(translationMat, glm::vec3(0.003f, 0.006f, 0.0f));
        size += 0.005f;
        selfScalingMat = glm::scale(MAT, size);
    }

    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->update(timer, event, eventTargetId, shader, false, activeWindow);
}
