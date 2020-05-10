#include "../include/controller.h"
#include<cmath>

Settings settings;


void Controller::run()
{
    glewExperimental = GL_TRUE;
    if( GLEW_OK !=glewInit())
        print("GLEW initialization failed!");


    /* setup shaders */
    Shader shader("source/shaders/shader.vs", "source/shaders/shader.fs");
    Shader lightingShader("source/shaders/lighting_shader.vs", "source/shaders/lighting_shader.fs");

    projMatrix = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    /* set initial ViewMatrix */
    camId = model.firstCameraId;
    changeCamera(camId);

    glEnable(GL_DEPTH_TEST);

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );


    shader.use();
    shader.setMat4("projection", projMatrix);

    lightingShader.use();
    lightingShader.setMat4("projection", projMatrix);

    while(!glfwWindowShouldClose(leftWindow))
    {

        glfwMakeContextCurrent(leftWindow);
        int ret = view.listenToCallbacks(leftWindow);

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

        glfwSwapBuffers(leftWindow);
        glfwPollEvents();
    }
    glfwTerminate();
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
