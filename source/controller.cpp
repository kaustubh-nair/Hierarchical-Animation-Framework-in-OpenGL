#include "../include/controller.h"
#include<cmath>

Settings settings;


void Controller::run()
{
    leftWindow = view.initialize_window("left", NULL);
    rightWindow = view.initialize_window("right", leftWindow);


    glfwMakeContextCurrent(leftWindow);

    glewExperimental = GL_TRUE; 
    if( GLEW_OK != glewInit())
        print("GLEW initialization failed!");

    projMatrix = glm::perspective(glm::radians(45.0f), WIDTH/HEIGHT, 0.1f, 100.0f);

    /* set initial ViewMatrix */
    camId = model.firstCameraId;
    changeCamera(camId);

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
    setup(leftWindow);
    setup(rightWindow);

    while((!glfwWindowShouldClose(leftWindow)) && (!glfwWindowShouldClose(rightWindow)))
    {

        render(leftWindow, shader, leftViewMatrix);
        render(rightWindow, shader, rightViewMatrix);

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
            // Might require changes later
            camId = model.firstCameraId + ((camId + 1) % model.numCameras);
            changeCamera(camId);
            break;
    }
}


void Controller::changeCamera(int id)
{
    if(view.windowIsActive(leftWindow))
        leftViewMatrix = model.getCameraLookAt(id);
    else if(view.windowIsActive(rightWindow))
        rightViewMatrix = model.getCameraLookAt(id);
}
