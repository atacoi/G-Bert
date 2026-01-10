#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game.h"

void frameBufferSizeCallback(GLFWwindow *window, int width, int height); 
void windowCloseCallback(GLFWwindow *window);

static Game game;

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(game.getScreenWidth(), 
                                          game.getScreenHeight(), 
                                          game.getTitle(), 
                                          NULL, 
                                          NULL);

    if(!window) {
        std::cerr << "GLFW could not create a window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    glfwSetWindowCloseCallback(window, windowCloseCallback);

    glClearColor(0.0f, 0.22f, 0.55f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
    game.setScreenWidth(width);
    game.setScreenHeight(height);
    glViewport(0, 0, width, height);
}

void windowCloseCallback(GLFWwindow *window) {
    game.setCurrState(GAME_STATES::TERMINATED);
    glfwSetWindowShouldClose(window, GL_TRUE);
}