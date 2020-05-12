#include "../include/view.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


float WIDTH = 1360.0f;
float HEIGHT = 768.0f;
bool firstMouse;    //first mouse click


void View::initializeWindows()
{
    leftWindow = initialize_window("left", NULL);
    rightWindow = initialize_window("right", leftWindow);
}


GLFWwindow* View::initialize_window(std::string name, GLFWwindow *sharedWindow)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, name.c_str(), NULL, sharedWindow);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(0);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glViewport(0,0, WIDTH, HEIGHT);
    glfwMakeContextCurrent(NULL);

    return window;
}

bool View::windowIsActive(GLFWwindow *window)
{
    return glfwGetWindowAttrib(window, GLFW_FOCUSED);
}

int View::listenToCallbacks(GLFWwindow *window)
{

    // todo change moving to press only
    std::map<int,int> key_mappings = {
        {GLFW_KEY_ESCAPE, UNSELECT_OBJECT},
        {GLFW_KEY_0, SELECT_OBJECT_1},
        {GLFW_KEY_9, SELECT_OBJECT_2},
        {GLFW_KEY_8, SELECT_OBJECT_3},
        {GLFW_KEY_7, SELECT_OBJECT_4},
        {GLFW_KEY_MINUS, SCALE_OBJECT_DOWN},
        {GLFW_KEY_W, MOVE_FORWARD},
        {GLFW_KEY_A, MOVE_LEFT},
        {GLFW_KEY_S, MOVE_BACKWARD},
        {GLFW_KEY_D, MOVE_RIGHT},
        {GLFW_KEY_UP, CHANGE_CAMERA},
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
        glViewport(0,0,WIDTH,HEIGHT);
}
