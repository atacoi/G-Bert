#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "game.h"
#include "shader.h"
#include "resource_manager.h"
#include "game_object.h"

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
                                          game.getTitle().c_str(), 
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

    glViewport(0, 0, game.getScreenWidth(), game.getScreenHeight());

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    glfwSetWindowCloseCallback(window, windowCloseCallback);

    //ResourceManager::createShader("sprite.vertex", "sprite.fragment", "default");

    Shader s("sprite.vertex", "sprite.fragment");

    game.initializeVAO();

    GameObject g(&s, glm::vec2(1.0f, 1.0f), 100, 100);

    game.addGameObject(&g);

    while(!glfwWindowShouldClose(window)) {
        game.render(window);

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