#ifndef VIEW_H
#define VIEW_H

//careful: no multiple declarations for glm allowed
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/gtx/string_cast.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>

#include "../include/definitions.h"
#include "../include/scene_node/camera_node.h"

extern float WIDTH;
extern float HEIGHT;

class View {
  public:
    GLFWwindow* rightWindow = nullptr;
    GLFWwindow* leftWindow = nullptr;

    CameraNode *leftCam;
    CameraNode *rightCam;

    /* temporary helper variable to store look-around direction */
    void initializeWindows();
    void reactToMouseCallbacks(GLFWwindow *window, CameraNode *camera);
    int listenToCallbacks(GLFWwindow *window);
    bool windowIsActive(GLFWwindow *window);
  private:
    GLFWwindow* initialize_window(std::string name, GLFWwindow *window);
};
#endif

