#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/glew.h>
#include <iostream>

#include "../include/view.h"
#include "../include/shader.h"
#include "../include/model.h"
#include "../include/camera.h"
#include "../include/mesh.h"
#include "../include/ply_parser.h"

extern struct Settings settings;


class Controller {
  public:
    View view;
    std::vector<Model> models;  //multiple scenes each containing multiple meshes
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
    void loadPlyFiles(std::vector<std::string> &filepaths, std::vector<glm::vec3> &meshPos, std::vector<std::string> &texturePaths, int scene);
    void setupScene(std::vector<std::string> &filepaths,
                              std::vector<glm::vec3> &meshPos,
                              std::string &texturePath);

    /* helpers */
    void toggleTextures(Shader *shader);
    void setShader(Shader *shader, Shader *subdivisionShader, Shader *normalColoringShader);
};


#endif
