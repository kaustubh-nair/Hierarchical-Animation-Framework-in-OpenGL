#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/glew.h>
#include <iostream>

#include "../include/view.h"
#include "../include/shader.h"
#include "../include/model.h"
#include "../include/mesh.h"
#include "../include/ply_parser.h"

extern struct Settings settings;


class Controller {
  public:
    View view;
    Model model;
    Shader shader, lightingShader;

    GLFWwindow* rightWindow = nullptr;
    GLFWwindow* leftWindow = nullptr;

    glm::mat4 projMatrix;
    glm::mat4 viewMatrix;
    int camId = 0;  //current active camera

    void run();
    void mainLoop(GLFWwindow *window);
    void setup(GLFWwindow *window);
    void reactToCallback(int ret);
    void changeCamera(int id);
};


#endif
