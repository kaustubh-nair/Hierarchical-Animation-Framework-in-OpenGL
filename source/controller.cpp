#include "../include/controller.h"
#include<cmath>

Settings settings;


void Controller::run()
{
    view.initializeWindows();


    glfwMakeContextCurrent(view.leftWindow);

    glewExperimental = GL_TRUE; 
    if( GLEW_OK != glewInit())
        print("GLEW initialization failed!");

    projMatrix = glm::perspective(glm::radians(45.0f), WIDTH/HEIGHT, 0.1f, 100.0f);

    /* set initial camera information */
    view.leftCamId = model.firstCameraId;
    view.rightCamId = model.firstCameraId;
    view.leftCamLookAt = model.getCameraLookAt(view.leftCamId);
    view.rightCamLookAt = model.getCameraLookAt(view.rightCamId);

    /* setup shaders */
    Shader shader("source/shaders/shader.vs", "source/shaders/shader.fs");
    Shader lightingShader("source/shaders/lighting_shader.vs", "source/shaders/lighting_shader.fs");

    shader.use();
    shader.setMat4("projection", projMatrix);
    /*
    lightingShader.use();
    lightingShader.setMat4("view", viewMatrix);
    lightingShader.setMat4("projection", projMatrix);
    */

    glfwMakeContextCurrent(NULL);


    /* load buffers */
    setup(view.leftWindow);
    setup(view.rightWindow);

    while((!glfwWindowShouldClose(view.leftWindow)) && (!glfwWindowShouldClose(view.rightWindow)))
    {

        render(view.leftWindow, shader, view.leftCamLookAt);
        render(view.rightWindow, shader, view.rightCamLookAt);

        glfwPollEvents();

    }
    glfwTerminate();
}


void Controller::render(GLFWwindow *window, Shader shader, glm::mat4 viewMatrix)
{
    glfwMakeContextCurrent(window);

    if(view.windowIsActive(window))
    {
        int ret = view.listenToCallbacks(window);
        reactToCallback(ret);
    }

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    shader.setMat4("view", viewMatrix);
    //shader.setVec3("viewPos", view.getViewPos());

    model.render(shader);
    //model.drawLighting(shader, lightingShader);

    glfwSwapBuffers(window);

    glfwMakeContextCurrent(NULL);
}


void Controller::setup(GLFWwindow *window)
{
    glfwMakeContextCurrent(window);

    glEnable(GL_DEPTH_TEST);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    /* generate buffers */
    model.setup();
    glfwMakeContextCurrent(NULL);
}


void Controller::reactToCallback(int ret)
{
    switch(ret)
    {
        case CHANGE_CAMERA:
                changeCamera();
            break;
    }
}


void Controller::changeCamera()
{
    if(view.windowIsActive(view.leftWindow))
    {
        view.leftCamId = model.firstCameraId + ((view.leftCamId + 1) % model.numCameras);
        view.leftCamLookAt = model.getCameraLookAt(view.leftCamId);
    }
    else if(view.windowIsActive(view.rightWindow))
    {
        view.rightCamId = model.firstCameraId + ((view.rightCamId + 1) % model.numCameras);
        view.rightCamLookAt = model.getCameraLookAt(view.rightCamId);
    }
}
