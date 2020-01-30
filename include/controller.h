#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/glew.h>
#include <iostream>

#include "../include/view.h"


class Controller {
  public:
    View *view = nullptr;
    GLFWwindow* mainWindow = nullptr;

    Controller()
    {
      this->view = new View();
      this->mainWindow = this->view->initialize_window();
    };
    ~Controller()
    {
      delete this->view;
    };
    void mainLoop();

  private:
    void processInput(GLFWwindow* window);
};


#endif
