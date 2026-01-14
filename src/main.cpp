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
#include "board.h"
#include "g_bert.h"
#include "texture2d.h"

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

    Shader _default("default.vertex", "default.fragment");

    Shader _sprite("sprite.vertex", "sprite.fragment");
    Texture2D _tex2D("q_bert.png");

    game.initializeVAO();

    // Cube g(&s);

    // game.addGameObject(&g);

    Board board(&_default, 7, glm::vec2(game.getScreenWidth() / 2.0f, 200.0f));

    GBert gbert(&_sprite, &_tex2D, 100, 100);

    board.addGameObjectsToGame(&game);
    game.addGameObject(&gbert);

    double prevTime = glfwGetTime();
    double delta = 1.0;

    int direction = 1; // down    
    GameObject *curr = board.getGameObject(0);
    Cube *cube = dynamic_cast<Cube*>(curr);
    gbert.setPosition(cube->getTopCenter() - glm::vec2(gbert.getWidth() * 0.5f, gbert.getHeight()));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_MULTISAMPLE);

    while(!glfwWindowShouldClose(window)) {
        game.render(window);

        if(glfwGetTime() - prevTime >= delta) {
            GameObject *nxt = direction == 1 ? board.getChildGameObject(curr, TREE_DIRECTION_TYPE::LEFT) 
                                             : board.getParentGameObject(curr, TREE_DIRECTION_TYPE::RIGHT);
            if(nxt) {
                Cube *cube = nullptr;
                if((cube = dynamic_cast<Cube*>(nxt))) {
                    gbert.setPosition(cube->getTopCenter() - glm::vec2(gbert.getWidth() * 0.5f, gbert.getHeight()));
                    cube->step();
                }
                curr = nxt;
                prevTime = glfwGetTime();
            } else {
                direction *= -1;
            }
        }

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