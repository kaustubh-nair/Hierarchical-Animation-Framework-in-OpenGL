#include "../include/view.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

CameraNode camera(glm::vec3(0.0f, 0.0f, 3.0f),
                  glm::vec3(0.0f, 0.0f, -1.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f));

float WIDTH = 3000.0f;
float HEIGHT = 2250.0f;
bool firstMouse;    //first mouse click

GLFWwindow* View::initialize_window()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(0);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glewExperimental = GL_TRUE; 
    if ( GLEW_OK != glewInit() )
    {
        std::cout << "Glew failed" << std::endl;
        glfwTerminate();
        exit(0);
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    return window;
}

glm::mat4 View::getViewMatrix()
{
    return camera.getViewMatrix();
}

glm::vec3 View::getViewPos()
{
    return camera.getPosition();
}

int View::listenToCallbacks(GLFWwindow *window)
{

    std::map<int,int> key_mappings = {
        {GLFW_KEY_ESCAPE, UNSELECT_OBJECT},
        {GLFW_KEY_0, SELECT_OBJECT_1},
        {GLFW_KEY_9, SELECT_OBJECT_2},
        {GLFW_KEY_8, SELECT_OBJECT_3},
        {GLFW_KEY_7, SELECT_OBJECT_4},
        {GLFW_KEY_MINUS, SCALE_OBJECT_DOWN},
        {GLFW_KEY_W, TOGGLE_WIREFRAME},
        {GLFW_KEY_N, TOGGLE_NORMAL_COLORING},
    };

    static std::vector<int> oldStates(key_mappings.size(), GLFW_RELEASE);
    int newState;

    int i = 0;
    std::map<int, int>::iterator itr;
    for (itr = key_mappings.begin(); itr != key_mappings.end(); itr++) 
    {
        newState = glfwGetKey(window, itr->first);
        if( oldStates.at(i) == GLFW_PRESS && newState == GLFW_RELEASE)
        {
            oldStates.at(i) = newState;
            return itr->second;
        }
        oldStates.at(i) = newState;
        i++;
    }

    /* scaling up */
    static int oldState12 = GLFW_RELEASE;
    newState = glfwGetKey(window, GLFW_KEY_EQUAL);
    if(oldState12 == GLFW_PRESS && newState == GLFW_RELEASE &&    glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
          oldState12 = newState;
          return SCALE_OBJECT_UP;
    }
    oldState12 = newState;
    
    /* translation and rotation callbacks */
    int leftState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int rightState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    static double oldX, oldY;

    if(leftState == GLFW_RELEASE && rightState == GLFW_RELEASE)
        glfwGetCursorPos(window, &oldX, &oldY);

    if(leftState == GLFW_PRESS || rightState == GLFW_PRESS)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        if(firstMouse)
        {
            oldX = x;
            oldY = y;
            firstMouse = false;
        }

        this->direction = glm::vec2(x - oldX, oldY - y);
        oldX = x;
        oldY = y;
    }

    if(leftState == GLFW_PRESS)
        return TRANSLATE_OBJECT;

    if(rightState == GLFW_PRESS)
        return ROTATE_OBJECT;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
        glViewport(0,0,width,height);
}
