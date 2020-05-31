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
#include "../include/scene_node/target_node.h"


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
    int id = 1;

    /* NOTE: Id order of group nodes should not be changed */

    /* id, parentId */
    SceneNode *lightGroup = new GroupNode(1);
    CameraGroupNode *cameraGroup = new CameraGroupNode(2);
    SceneNode *meshGroup = new GroupNode(3);

    /* NOTE: Camera nodes should be inserted with sequential ids */

    controller.model.addNode(lightGroup, 0);   //lights
    controller.model.addNode(cameraGroup, 0);   //cameras
    controller.model.addNode(meshGroup, 0);   //meshes

    SceneNode *light1 = controller.model.addLightNode(13, 1, ORIGIN + (4.0f*Y) + (3.0f*X), "data/meshes/sphere.ply", UNIT, POINTLIGHT);
    SceneNode *light2 = controller.model.addLightNode(14, 1, ORIGIN + (4.0f*Y) - (3.0f*X), "data/meshes/sphere.ply", UNIT, POINTLIGHT);

    /* main camera */

    SceneNode *grass = new MeshNode(9, "data/meshes/rectangle.ply", "data/textures/grass.jpg", ORIGIN, glm::scale(MAT, 40.0f * UNIT), MAT, MAT);

    SceneNode *personA  = new Person(10, "data/meshes/body.ply", "data/textures/skin.jpg", X + (0.5f*Y), MAT, MAT, MAT);
    SceneNode *headA = new Head(100, "data/meshes/sphere.ply", "data/textures/face.jpg", (0.45f*Y) + (0.04f*Z) + (0.05f*X), MAT, glm::rotate(MAT,glm::radians(-90.0f),Y), glm::scale(MAT, 0.15f*UNIT));

    SceneNode *personB = new Person(12, "data/meshes/body.ply", "data/textures/skin.jpg", -X + (0.5f*Y), MAT, MAT, MAT);
    SceneNode *headB = new Head(101, "data/meshes/sphere.ply", "data/textures/face.jpg", (0.45f*Y)  + (0.04f*Z)+ (0.05f*X), MAT, glm::rotate(MAT,glm::radians(-90.0f),Y), glm::scale(MAT, 0.15f*UNIT));

    SceneNode *personC = new Person(1092, "data/meshes/body.ply", "data/textures/skin.jpg", (-6.0f*X) + (0.5f*Y), MAT, MAT, MAT);
    SceneNode *headC = new Head(102, "data/meshes/sphere.ply", "data/textures/face.jpg", (0.45f*Y) + (0.05f*X) + (0.04f*Z), MAT, glm::rotate(MAT,glm::radians(-90.0f),Y), glm::scale(MAT, 0.15f*UNIT));

    SceneNode *balloon = new Balloon(16, "data/meshes/sphere.ply", "data/textures/purple.jpeg", (3.0f*Y) , MAT, MAT, glm::scale(MAT, 2.0f*UNIT));
    SceneNode *basket = new Basket(17, "data/meshes/cube.ply", "data/textures/skin.jpg", - (2.5f*Y), MAT, MAT, glm::scale(MAT,0.5f*UNIT));
    SceneNode *animal = new Animal(18, "data/meshes/cow.ply", "data/textures/black.jpg", - (2.3f*Y) + (0.1f*X), MAT, MAT, glm::scale(MAT,0.5f*UNIT));

    SceneNode *bird = new Bird(19, "data/meshes/humbird.ply", "data/textures/feather.jpg", 10.0f*(Y + X + Z), glm::scale(MAT, 1.5f*UNIT), MAT, MAT);

    SceneNode *camera = new CameraNode(4, 4, -(5.0f*Z) + Y, -Z + (5.0f*Z) - Y, Y);

    SceneNode *leftHmdA = new CameraNode(5, personA->id,  (0.5f*X) +(1.0f*Y), Z + (1.5f*Y) + (0.5f*X) + (1.0f*Y), Y);
    SceneNode *rightHmdA = new CameraNode(6, personA->id, -(0.5f*X) +(1.0f*Y), Z + (1.5f*Y) - (0.5f*X) + (1.0f*Y), Y);
    SceneNode *leftHmdB = new CameraNode(52, personB->id, (0.5f*X) +(1.0f*Y), Z + (1.5f*Y) + (0.5f*X) + (1.0f*Y), Y);
    SceneNode *rightHmdB = new CameraNode(69, personB->id, -(0.5f*X) +(1.0f*Y), Z + (1.5f*Y) - (0.5f*X) + (1.0f*Y), Y);

    SceneNode *birdCam = new CameraNode(199, bird->id, -X, Z + (0.5f*Y), Y);

    ((Head*) headA)->userControlled = false;
    ((Person*) personC)->userControlled = false;
    ((Head*) headC)->userControlled = false;
    personC->avoidCollisionsWith = personB;
    personB->avoidCollisionsWith = personC;
    bird->avoidCollisionsWith = balloon;
    balloon->avoidCollisionsWith = bird;

    /* NOTE: id = 0 is scene root, which is inserted autoMATicallY. */

    /* id, parentId */

    /* NOTE: Camera nodes should be inserted with sequential ids */

    /* main camera */
    controller.model.addCameraNode(camera, 2);
    controller.model.addCameraNode(leftHmdA, 2);
    controller.model.addCameraNode(rightHmdA, 2);
    controller.model.addCameraNode(leftHmdB, 2);
    controller.model.addCameraNode(rightHmdB, 2);

    controller.model.addNode(grass, 3);
    controller.model.addNode(personA, 3);
    controller.model.addNode(headA, 10);
    controller.model.addNode(personB, 3);
    controller.model.addNode(headB, 12);
    controller.model.addNode(personC, 3);
    controller.model.addNode(headC, 1092);
    controller.model.addNode(balloon, 3);
    controller.model.addNode(basket, 16);
    controller.model.addNode(animal, 16);
    controller.model.addNode(bird, 3);

    controller.model.addConnection(personB, leftHmdB);
    controller.model.addConnection(personB, rightHmdB);
    controller.model.addConnection(personA, leftHmdA);
    controller.model.addConnection(personA, rightHmdA);


    cameraGroup->leftCamIds.push_back(camera->id);
    cameraGroup->rightCamIds.push_back(camera->id);

    cameraGroup->leftCamIds.push_back(leftHmdB->id);
    cameraGroup->rightCamIds.push_back(rightHmdB->id);

    cameraGroup->leftCamIds.push_back(leftHmdB->id);
    cameraGroup->rightCamIds.push_back(camera->id);

    cameraGroup->leftCamIds.push_back(leftHmdA->id);
    cameraGroup->rightCamIds.push_back(rightHmdA->id);

    TargetNode *target1 = new TargetNode(300);
    ((MeshNode*)bird)->target = target1;
    controller.model.addNode(target1, balloon->id);

    TargetNode *target3 = new TargetNode(302);
    ((MeshNode*)personC)->target = target3;
    controller.model.addNode(target3, personB->id);

    TargetNode *target4 = new TargetNode(303);
    ((CameraNode*)leftHmdA)->target = target4;
    ((CameraNode*)rightHmdA)->target = target4;
    controller.model.addNode(target4, headA->id);

    TargetNode *target5 = new TargetNode(304);
    ((CameraNode*)leftHmdB)->target = target5;
    ((CameraNode*)rightHmdB)->target = target5;
    controller.model.addNode(target5, headB->id);




    controller.run();


    return 0;
}


int time(int seconds)
{
    return 60 * seconds;  //assume 60fps
}


void Person::update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data, GLFWwindow *activeWindow)
{
    if(userControlled && active && (id == eventTargetNodeId))
    {
        float sensitivity = 0.5f;

        if(event == MOVE_FORWARD)
        {
            position += sensitivity * glm::normalize(front - position);
            translationMat = glm::translate(MAT, position);
        }

        else if(event == MOVE_BACKWARD)
        {
            position -= sensitivity * glm::normalize(front - position);
            translationMat = glm::translate(MAT, position);
        }

        else if(event == MOVE_RIGHT)
        {
            position -= sensitivity * glm::normalize(glm::cross((position - front), up));
            translationMat = glm::translate(MAT, position);
        }

        else if(event == MOVE_LEFT)
        {
            position += sensitivity * glm::normalize(glm::cross((position - front), up));
            translationMat = glm::translate(MAT, position);
        }

        for(auto itr = connections.begin(); itr != connections.end(); itr++)
            (*itr)->update(timer, event, eventTargetNodeId, shader, true, position, activeWindow);
    }
    else
    {
        if(target != nullptr)
        {
            static int timeAway = 500;
            if(minimumSeperation(avoidCollisionsWith) > 0.5f && (timeAway == 500 || timeAway == 0))
            {
                glm::vec3 dir = glm::normalize(target->data - position);
                position = position + (0.008f*dir);
                translationMat = glm::translate(MAT, position);
                timeAway = 500;
            }
            else
            {
                timeAway--;
                glm::vec3 dir = glm::normalize(target->data - position);
                position = position - (0.008f*dir);
                translationMat = glm::translate(MAT, position);

            }
        }
    }
    // TODO: add else here?
    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->update(timer, event, eventTargetNodeId, shader, false, position, activeWindow);

}
void Bird::update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data, GLFWwindow *activeWindow)
{
    if(target != nullptr)
    {
        static int timeAway = 500;
        if(minimumSeperation(avoidCollisionsWith) > 0.5f && (timeAway == 500 || timeAway == 0))
        {
            glm::vec3 dir = glm::normalize(target->data - position);
            position = position + (0.05f*dir);
            translationMat = glm::translate(MAT, position);
            timeAway = 500;
        }
        else
        {
            timeAway--;
            glm::vec3 dir = glm::normalize(target->data - position);
            position = position - (0.05f*dir);
            translationMat = glm::translate(MAT, position);

        }
    }
    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->update(timer, event, eventTargetNodeId, shader, false, position, activeWindow);
}


void Animal::update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data, GLFWwindow *activeWindow)
{

    static float angle = 0.0f;
    if(settings.destroyedBalloon)
    {
        if(position.y > 2.5f)
        {
            auto diff = glm::vec3(0.0f, -0.009f, 0.0f);
            position += diff;
            translationMat = glm::translate(translationMat, diff);
            rotationMat = glm::rotate(MAT, glm::radians(angle), X);
            angle+=2.0f;
        }
    }
    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->update(timer, event, eventTargetNodeId, shader, false, position, activeWindow);
}


void Basket::update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data, GLFWwindow *activeWindow)
{

    if(settings.destroyedBalloon)
    {
        if(position.y > 3.0f)
        {
            auto diff = glm::vec3(0.003f, -0.009f, 0.0f);
            position += diff;
            translationMat = glm::translate(translationMat, diff);
        }

    }
    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->update(timer, event, eventTargetNodeId, shader, false, position, activeWindow);

}


void Head::update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data, GLFWwindow *activeWindow)
{
    if(userControlled)
    {
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
        float yaw_radians = glm::radians(yaw);
        float pitch_radians = glm::radians(pitch);

        direction.x = cos(yaw_radians) * cos(pitch_radians);
        direction.y = -sin(pitch_radians);
        direction.z = sin(yaw_radians) * cos(pitch_radians);

        front = glm::normalize(direction);

        glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
        up = glm::normalize(glm::cross(right, front));

        rotationMat = glm::rotate(MAT, glm::radians(180.0f), up);
    }
    else
    {

    }
    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->update(timer, event, eventTargetNodeId, shader, false, front, activeWindow);
}


void Balloon::update(int timer, int event, int eventTargetNodeId, Shader shader, bool isConnection, glm::vec3 data, GLFWwindow *activeWindow)
{
    if(timer > time(4))
    {
        if(size.x < 4.0f)  // WARNING: hard-coded for now
        {
            glm::vec3 diff(0.003f, 0.006f, 0.0f);
            position += diff;

            translationMat = glm::translate(translationMat, diff);
            size += 0.0014f;
            selfScalingMat = glm::scale(MAT, size);
        }
        else
        {
            settings.destroyBalloon = true;
        }
    }

    for(auto itr = children.begin(); itr != children.end(); itr++)
        (*itr)->update(timer, event, eventTargetNodeId, shader, false, position, activeWindow);
}
