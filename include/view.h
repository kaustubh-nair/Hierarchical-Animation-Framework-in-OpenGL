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
#include "../include/camera_node.h"

extern float WIDTH;
extern float HEIGHT;

class View {
  public:
    GLFWwindow* rightWindow = nullptr;
    GLFWwindow* leftWindow = nullptr;

    glm::mat4 leftCamLookAt;
    glm::mat4 rightCamLookAt;
    int leftCamId;
    int rightCamtId;

    glm::vec3 objPosition;      //temporary variable to store selected object position
    glm::vec2 direction;      //helper variable to store translation direction
    void initializeWindows();
    int listenToCallbacks(GLFWwindow *window);
    bool windowIsActive(GLFWwindow *window);
  private:
    GLFWwindow* initialize_window(std::string name, GLFWwindow *window);
};
#endif

