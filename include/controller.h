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
    Shader shader;

    glm::mat4 projMatrix;

    void run();
    void render(int timer, GLFWwindow *window, CameraNode *activeCam);
    void setup(GLFWwindow *window, Shader shader);
    int reactToCallback(int &event, CameraNode *activeCam);
    void changeCamera();
};


#endif
