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

    glm::mat4 projMatrix;
    int camId = 0;  //current active camera

    void run();
    void render(GLFWwindow *window, Shader shader, glm::mat4 viewMatrix);
    void setup(GLFWwindow *window);
    void reactToCallback(int ret);
    void changeCamera(int id);
};


#endif
