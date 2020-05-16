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

    projMatrix = glm::perspective(glm::radians(45.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);

    /* set initial camera information */
    view.leftCam = model.getCamera(model.firstCameraId);
    view.rightCam = model.getCamera(model.firstCameraId);

    /* setup shaders */
    shader = Shader("source/shaders/shader.vs", "source/shaders/shader.fs");

    shader.use();
    shader.setMat4("projection", projMatrix);
    shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

    glfwMakeContextCurrent(NULL);


    /* load buffers */
    setup(view.leftWindow, shader);
    setup(view.rightWindow, shader);

    int timer = 0;
    while((!glfwWindowShouldClose(view.leftWindow)) && (!glfwWindowShouldClose(view.rightWindow)))
    {

        timer++;
        render(timer, view.leftWindow, view.leftCam);
        render(timer, view.rightWindow, view.rightCam);

        glfwPollEvents();
    }
    glfwTerminate();
}


void Controller::render(int timer, GLFWwindow *window, CameraNode *activeCam)
{
    glfwMakeContextCurrent(window);

    if(view.windowIsActive(window))
    {
        view.reactToMouseCallbacks(window, activeCam);
        int event = view.listenToCallbacks(window);
        int target = reactToCallback(event, activeCam);
        model.update(timer, event, target);
    }

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    shader.setMat4("view", activeCam->lookAt);
    //shader.setVec3("viewPos", view.getViewPos());

    model.render(shader);
    //model.drawLighting(shader, lightingShader);

    glfwSwapBuffers(window);

    glfwMakeContextCurrent(NULL);
}


void Controller::setup(GLFWwindow *window, Shader shader)
{
    glfwMakeContextCurrent(window);

    glEnable(GL_DEPTH_TEST);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    /* generate buffers */
    model.setup(shader);
    glfwMakeContextCurrent(NULL);
}


/* returns the target object's id that needs to be passed to the update methods */
int Controller::reactToCallback(int event, CameraNode *activeCam)
{
    if(event == CHANGE_CAMERA)
    {
        changeCamera();
        return activeCam->id;
    }
    else if(event == LOOK_AROUND)
        return activeCam->id;

    return -1;
}


void Controller::changeCamera()
{
    if(view.windowIsActive(view.leftWindow))
    {
        // increate camId by 1
        /* NOTE: Camera nodes should be inserted sequentially */
        int camId = model.firstCameraId + ((view.leftCam->id + 1) % model.numCameras);
        view.leftCam = model.getCamera(camId);
    }
    else if(view.windowIsActive(view.rightWindow))
    {
        int camId = model.firstCameraId + ((view.rightCam->id + 1) % model.numCameras);
        view.rightCam = model.getCamera(camId);
    }
}
