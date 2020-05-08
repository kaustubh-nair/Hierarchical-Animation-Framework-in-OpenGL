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
    GLFWwindow* window = nullptr;
    bool normalColoring;

    Controller()
    {
      window = view.initialize_window();
      normalColoring = false;
    };

    ~Controller()
    {
    };

    void mainLoop();
    void reactToCallback(int ret);
    void toggleWireframe();

    /* helpers */
    void toggleTextures(Shader *shader);
    void setShader(Shader *shader, Shader *normalColoringShader);
};


#endif
