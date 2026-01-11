#include <iostream>
#include <string.h>
#include "game.h"
#include <stdlib.h>

GLuint STATIC_IDs = 0;

/* ********************************************** */
/*                PUBLIC                          */
/* ********************************************** */

/* ********************************************** */
/*                CONSTRUCTORS                    */
/* ********************************************** */

Game::Game(): screenTitle("G-Bert"), gameObjectMap() {
    screenWidth = 1280;
    screenHeight = 720;
    currState = GAME_STATES::ACTIVE;
}

Game::Game(int width, int height, const std::string &title): screenTitle(title), gameObjectMap()  {
    screenWidth = width;
    screenHeight = height;
    currState = GAME_STATES::ACTIVE;
}

/* ********************************************** */
/*                DESTRUCTORS                     */
/* ********************************************** */

Game::~Game() {
    currState = GAME_STATES::TERMINATED;
    glDeleteVertexArrays(1, &QUAD_VAO);
}

/* ********************************************** */
/*                GETTERS                         */
/* ********************************************** */

int Game::getScreenWidth() { return screenWidth; }

int Game::getScreenHeight() { return screenHeight; }

std::string &Game::getTitle() { return screenTitle; }

GAME_STATES Game::getCurrState() { return currState; }

/* ********************************************** */
/*                Setters                         */
/* ********************************************** */

void Game::setScreenWidth(int width) {
    if(width < 0) {
        std::cerr << "Screen width cannot be negative" << std::endl;
    } else {
        screenWidth = width;
    }
}

void Game::setScreenHeight(int height) {
    if(height < 0) {
        std::cerr << "Screen height cannot be negative" << std::endl;
    } else {
        screenHeight = height;
    }
}

void Game::setCurrState(GAME_STATES state) { currState = state; }

/* ********************************************** */
/*                UTILITY                         */
/* ********************************************** */

bool Game::isRunning() { return this->currState == GAME_STATES::ACTIVE; }

void Game::render(GLFWwindow *window) {
    glClearColor(0.0f, 0.22f, 0.55f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(QUAD_VAO);

    std::map<GLuint, GameObject*>::iterator it;

    for (auto &gameObject : gameObjectMap) {
        gameObject.second->render(screenWidth, screenHeight);
    }

    glfwSwapBuffers(window);
}

void Game::initializeVAO() {
    GLuint VBO;

    glGenVertexArrays(1, &QUAD_VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(QUAD_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD), QUAD, GL_STATIC_DRAW);

    glVertexAttribPointer(0, VERTEX_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glDeleteBuffers(1, &VBO);
}

void Game::addGameObject(GameObject *go) {
    gameObjectMap[go->getID()] = go;
}