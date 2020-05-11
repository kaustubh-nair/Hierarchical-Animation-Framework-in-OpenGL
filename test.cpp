#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include "include/shader.h"

GLFWwindow* setupWindow(std::string name, GLFWwindow *sharedWindow);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void render(GLFWwindow *window, Shader shader, unsigned int VAO);
void setup(GLFWwindow *window, unsigned int *VBO, unsigned int *VAO, unsigned int *EBO);

float vertices[] = {
0.5, 0, 0 ,
0, -0.5, 0 ,
-0.5, 0, 0 ,
0, 0.5, 0 ,
0, 0, 0.5 ,
0, 0, -0.5 
};
unsigned int indices[] = {  
 4,0,1 ,
 4,1,2 ,
 4,2,3 ,
 4,3,0 ,
 5,1,0 ,
 5,2,1 ,
 5,3,2 ,
 5,0,3 
};

int main()
{

    GLFWwindow *leftWindow = setupWindow("left", NULL);
    GLFWwindow *rightWindow = setupWindow("right", leftWindow);

    glfwMakeContextCurrent(leftWindow);
    glewInit();

    unsigned int VAO1, VBO1, EBO1;
    unsigned int VAO2, VBO2, EBO2;

    setup(leftWindow, &VBO1, &VAO1, &EBO1);
    setup(rightWindow, &VBO2, &VAO2, &EBO2);

    Shader shader("./source/shaders/minimal_shader.vs", "./source/shaders/minimal_shader.fs");

    
    while (!glfwWindowShouldClose(leftWindow))
    {
        render(rightWindow,shader,VAO2);
        render(leftWindow,shader,VAO2);
        glfwPollEvents();
    }

    /*
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader.ID);
    */
    
    glfwTerminate();

    return 0;
}

void render(GLFWwindow *window, Shader shader, unsigned int VAO)
{
        glfwMakeContextCurrent(window); glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shader.use();
        glBindVertexArray(VAO); 
        
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glBindVertexArray(0); 
        

}
void setup(GLFWwindow *window, unsigned int *VBO, unsigned int *VAO, unsigned int *EBO)
{
    glfwMakeContextCurrent(window);
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

GLFWwindow* setupWindow(std::string name, GLFWwindow *sharedWindow)
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, name.c_str(), NULL, sharedWindow);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(NULL);

    return window;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    
    
    glViewport(0, 0, width, height);
}
