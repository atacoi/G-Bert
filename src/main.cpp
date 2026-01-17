#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "game.h"
#include "shader.h"
#include "resource_manager.h"
#include "cube.h"
#include "g_bert.h"
#include "texture2d.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
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

    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    glfwSetWindowCloseCallback(window, windowCloseCallback);

    game.init();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_MULTISAMPLE);

    const double SPF = 1.0 / 60.0;

    double prevTime = glfwGetTime();
    double pauseTime = 1.0;

    while (!glfwWindowShouldClose(window)) {
        double currTime = glfwGetTime();
        double delta = currTime - prevTime;
        prevTime = currTime;

        if (pauseTime > 0.0) {
            pauseTime -= delta;
        } else {
            game.update(delta);
        }

        game.render(window);
        glfwPollEvents();

        double frameTime = glfwGetTime() - currTime;
        if (frameTime < SPF) {
            glfwWaitEventsTimeout(SPF - frameTime);
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (action == GLFW_PRESS) {
        game.setKey(key, true);
    } else if (action == GLFW_RELEASE) {
        game.setKey(key, false);
        game.setProcessed(key, false);
    }
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