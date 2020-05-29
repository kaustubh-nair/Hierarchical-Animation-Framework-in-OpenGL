#include "../include/view.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


float WIDTH = 1360.0f;
float HEIGHT = 768.0f;


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

    // TODO change moving to press only
    std::map<int,int> key_mappings = {
        {GLFW_KEY_W, MOVE_FORWARD},
        {GLFW_KEY_A, MOVE_LEFT},
        {GLFW_KEY_S, MOVE_BACKWARD},
        {GLFW_KEY_D, MOVE_RIGHT},
        {GLFW_KEY_UP, CHANGE_CAMERA},
        {GLFW_KEY_1, TOGGLE_LIGHT_0},
        {GLFW_KEY_2, TOGGLE_LIGHT_1},
        {GLFW_KEY_3, TOGGLE_LIGHT_2},
        {GLFW_KEY_4, TOGGLE_LIGHT_3},
        {GLFW_KEY_5, TOGGLE_LIGHT_4},
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
    return NONE;

}

void View::reactToMouseCallbacks(GLFWwindow *window, CameraNode *camera)
{
    static double oldX = 0.0, oldY = 0.0;

    double x, y;
    glfwGetCursorPos(window, &x, &y);

    float xoffset = x - oldX;
    float yoffset = y - oldY;
    oldX = x;
    oldY = y;

    float sensitivity = 0.2;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera->yaw   += xoffset;
    camera->pitch += yoffset;

    if(camera->pitch > 89.0f)
        camera->pitch = 89.0f;
    if(camera->pitch < -89.0f)
        camera->pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
    direction.y = -sin(glm::radians(camera->pitch));
    direction.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));

    camera->front = glm::normalize(direction);

    glm::vec3 right = glm::normalize(glm::cross(camera->front, glm::vec3(0.0f, 1.0f, 0.0f)));
    camera->up = glm::normalize(glm::cross(right, camera->front));
    camera->updateLookAt();
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
        glViewport(0,0,WIDTH,HEIGHT);
}
