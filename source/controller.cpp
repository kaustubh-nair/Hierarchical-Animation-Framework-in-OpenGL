#include "../include/controller.h"
#include<cmath>

Settings settings;


void Controller::run()
{
    rightWindow = view.initialize_window("right", NULL);
    leftWindow = view.initialize_window("left", rightWindow);

    projMatrix = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    /* set initial ViewMatrix */
    camId = model.firstCameraId;
    changeCamera(camId);

    setup(rightWindow);
    setup(leftWindow);

    while((!glfwWindowShouldClose(leftWindow)) && (!glfwWindowShouldClose(rightWindow)))
    {
        mainLoop(rightWindow);
        mainLoop(leftWindow);
    }
    glfwTerminate();
}


void Controller::mainLoop(GLFWwindow *window)
{
    glfwMakeContextCurrent(window);
    int ret = view.listenToCallbacks(window);

    reactToCallback(ret);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    shader.setMat4("view", viewMatrix);
    //shader.setVec3("viewPos", view.getViewPos());

    model.render(shader);
    model.drawLighting(shader, lightingShader);

    lightingShader.use();
    lightingShader.setMat4("view", viewMatrix);

    glfwSwapBuffers(window);
    glfwPollEvents();
    glfwMakeContextCurrent(NULL);
}


void Controller::setup(GLFWwindow *window)
{
    glfwMakeContextCurrent(window);

    /* setup shaders */
    Shader shader1("source/shaders/shader.vs", "source/shaders/shader.fs");
    Shader shader2("source/shaders/lighting_shader.vs", "source/shaders/lighting_shader.fs");

    shader = shader1;
    lightingShader = shader2;

    glEnable(GL_DEPTH_TEST);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    /* generate buffers */
    model.setup();

    shader.use();
    shader.setMat4("projection", projMatrix);

    lightingShader.use();
    lightingShader.setMat4("projection", projMatrix);
    glfwMakeContextCurrent(NULL);
}


void Controller::reactToCallback(int ret)
{
    switch(ret)
    {
        case CHANGE_CAMERA:
            // Might require changes later
            camId = model.firstCameraId + ((camId + 1) % model.numCameras);
            changeCamera(camId);
            break;
    }
}


void Controller::changeCamera(int id)
{
    viewMatrix = model.getCameraLookAt(id);
}
