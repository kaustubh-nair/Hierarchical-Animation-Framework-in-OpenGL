#include "../include/controller.h"
#include<cmath>

int textureRenderingStyle = CYLINDER_NORMAL_FROM_OBJECT;

/* load and save meshes for the three scenes */
void Controller::setup()
{
    /* load ply files into model */
    std::vector<std::string> filepaths;
    std::vector<glm::vec3> meshPos;
    std::vector<std::string> texturePaths;

    loadPlyFiles(filepaths, meshPos, texturePaths, SCENE_1);
    model.setup(filepaths, meshPos, texturePaths, textureRenderingStyle, SCENE_1);

    loadPlyFiles(filepaths, meshPos, texturePaths, SCENE_2);
    model.setup(filepaths, meshPos, texturePaths, textureRenderingStyle, SCENE_2);

    loadPlyFiles(filepaths, meshPos, texturePaths, SCENE_3);
    model.setup(filepaths, meshPos, texturePaths, textureRenderingStyle, SCENE_3);
}


void Controller::mainLoop()
{
    glewExperimental = GL_TRUE;
    if( GLEW_OK !=glewInit())
        print("GLEW initialization failed!");


    GLFWwindow* window = this->mainWindow;

    setup();

    /* setup shaders */
    Shader shader("source/shaders/shader.vs", "source/shaders/shader.fs");
    Shader lightingShader("source/shaders/lighting_shader.vs", "source/shaders/lighting_shader.fs");
    Shader normalColoringShader("source/shaders/normal_coloring_shader.vs", "source/shaders/normal_coloring_shader.fs");

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glm::mat4 viewMatrix = view.getViewMatrix();

    glEnable(GL_DEPTH_TEST);

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    while(!glfwWindowShouldClose(window))
    {

        int ret = view.listenToCallbacks(window);

        reactToCallback(ret);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        viewMatrix = view.getViewMatrix();

        if(this->normalColoring)
            normalColoringShader.use();
        else
            shader.use();

        shader.setMat4("projection", proj);
        shader.setMat4("view", viewMatrix);
        shader.setVec3("viewPos", view.getViewPos());
        shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        glm::vec3 lightPos = glm::vec3(3.2f, 3.2f, -4.0f);
        shader.setVec3("lightPos",lightPos.x, lightPos.y, lightPos.z);

        model.draw(shader, lightingShader, lightPos);

        lightingShader.use();
        lightingShader.setMat4("projection", proj);
        lightingShader.setMat4("view", viewMatrix);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}


void Controller::reactToCallback(int ret)
{
    switch(ret)
    {
        case UNSELECT_OBJECT:
            model.unselect();
            break;
        case SELECT_OBJECT_1:
                model.select(1);
                break;
        case SELECT_OBJECT_2:
                model.select(2);
                break;
        case SELECT_OBJECT_3:
                model.select(3);
                break;
        case SELECT_OBJECT_4:
                model.select(4);
                break;
        case SCALE_OBJECT_DOWN:
                model.scale(DOWN);
                break;
        case SCALE_OBJECT_UP:
                model.scale(UP);
                break;
        case TOGGLE_SPLATS:
                model.renderSplats = !model.renderSplats;
                model.refresh(textureRenderingStyle);
                break;
        case TOGGLE_WIREFRAME:
                this->toggleWireframe();
                break;
        case INCREASE_SPLAT_RADIUS:
                model.changeSplatRadius(UP);
                break;
        case DECREASE_SPLAT_RADIUS:
                model.changeSplatRadius(DOWN);
                break;
        case TOGGLE_NORMAL_COLORING:
                this->normalColoring = !this->normalColoring;
                break;
        case TRANSLATE_OBJECT:
                model.translate(view.direction);
                break;
        case ROTATE_OBJECT:
                model.rotate(view.direction);
                break;
        case SUBDIVIDE:
                model.subdivide();
                model.refresh(textureRenderingStyle);
                break;
        case SCENE_1:
                model.currentScene = SCENE_1;
                break;
        case SCENE_2:
                model.currentScene = SCENE_2;
                break;
        case SCENE_3:
                model.currentScene = SCENE_3;
                break;
    }
}

void Controller::toggleWireframe()
{
    GLint polygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, polygonMode);
    if ( polygonMode[0] == GL_LINE )
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    else
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}

void Controller::loadPlyFiles(std::vector<std::string> &filepaths,
                              std::vector<glm::vec3> &meshPos,
                              std::vector<std::string> &texturePaths,
                              int scene)
{
    filepaths.clear();
    meshPos.clear();
    texturePaths.clear();
    switch(scene)
    {
        case SCENE_1:
            {
                // loading 9 spheres
                float dist = 1.2f;
                for(int i = -1; i < 2; i++)
                {
                    for(int j = -1; j < 2; j++)
                    {
                        filepaths.push_back("data/sphere.ply");
                        texturePaths.push_back("data/rainbow.png");
                        meshPos.push_back(glm::vec3(dist * i, dist * j, -5.0f));
                    }
                }
                break;
            }

        case SCENE_2:
            {
                filepaths.push_back("data/bun_zipper.ply");
                filepaths.push_back("data/teapot.ply");
                filepaths.push_back("data/cylinder.ply");
                filepaths.push_back("data/sphere.ply");

                texturePaths.push_back("data/rainbow.png");
                texturePaths.push_back("data/rainbow.png");
                texturePaths.push_back("data/rainbow.png");
                texturePaths.push_back("data/rainbow.png");

                meshPos.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
                meshPos.push_back(glm::vec3(1.0f, 0.0f, -1.0f));
                meshPos.push_back(glm::vec3(0.0f, 1.0f, -1.0f));
                meshPos.push_back(glm::vec3(0.0f, 0.0f, -1.0f));

                break;
            }

        case SCENE_3:
            {
                filepaths.push_back("data/octahedron.ply");
                filepaths.push_back("data/tetrahedron.ply");
                filepaths.push_back("data/sphere.ply");

                texturePaths.push_back("data/rainbow.png");
                texturePaths.push_back("data/rainbow.png");
                texturePaths.push_back("data/rainbow.png");

                meshPos.push_back(glm::vec3(1.0f, 0.0f, -1.0f));
                meshPos.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
                meshPos.push_back(glm::vec3(0.0f, 1.0f, -1.0f));
                break;
            }
                
    }

}
