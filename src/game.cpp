#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "game.h"
#include "g_bert.h"
#include "resource_manager.h"
#include "rectangular_prism.h"

unsigned int STATIC_IDs = 0;

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

void Game::init() {
    initializeVAO();
    initializeShaders();
    initializeTextures();
    initializeBoard(glm::vec2(screenWidth / 2.0f - 25.0f, screenHeight * 0.25));
}

void Game::update(float delta) {
    // GBert *g = nullptr;
    // GameObject *go = g->getCurrentObject();
    // Cube *co = nullptr;
    // if((g = dynamic_cast<GBert*>(player)) && (co = dynamic_cast<Cube*>(go))) {
    //     Cube *nxt = dynamic_cast<Cube*>(board->getChildGameObject(co, TREE_DIRECTION_TYPE::LEFT));
    //     g->jump(GBert::DIRECTIONS::NORTHWEST, delta, glm::vec2(co->getTopCenter().x - 0.5f * g->getWidth(), co->getTopCenter().y - g->getHeight()));
    // }
}

void Game::render(GLFWwindow *window) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(QUAD_VAO);

    std::map<GLuint, GameObject*>::iterator it;

    for (auto &gameObject : gameObjectMap) {
        gameObject.second->render(screenWidth, screenHeight);
    }

    glfwSwapBuffers(window);
}

void Game::addGameObject(GameObject *go) {
    gameObjectMap[go->getID()] = go;
}

void Game::addGameObjects(const std::vector<GameObject*> &gos) {
    for(int i = 0; i < gos.size(); i++) {
        gameObjectMap[gos[i]->getID()] = gos[i];
    }
}

/* ********************************************** */
/*                PRIVATE                         */
/* ********************************************** */

/* ********************************************** */
/*                UTILITY                         */
/* ********************************************** */

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

void Game::initializeShaders() {
    ResourceManager::createShader("default.vertex", "default.fragment", "default");
    ResourceManager::createShader("sprite.vertex", "sprite.fragment", "sprite");
}

void Game::initializeTextures() {
    ResourceManager::createTexture("q_bert.png", "g-bert");
}

void Game::initializeBoard(glm::vec2 origin) {
    glm::vec3 rectPrismSize = glm::vec3(50, 50, 50);

    int levels = 7;

    Shader *shader = ResourceManager::getShader("default");
    generatePlatforms(origin, shader, rectPrismSize, levels);
}

void Game::generatePlatforms(glm::vec2 origin, Shader *shader, glm::vec3 rectangularPrismSize, int levels) {
    std::vector<GameObject*> prevLevel;
    std::vector<GameObject*> currLevel;

    int sideWidth  = rectangularPrismSize.x;
    int sideLength = rectangularPrismSize.y;
    int sideHeight = rectangularPrismSize.z;

    glm::vec2 scaledTopBasis   = (float) sideHeight  * RectangularPrism::topBasis;
    glm::vec2 scaledLeftBasis  = (float) sideWidth   * RectangularPrism::leftBasis;
    glm::vec2 scaledRightBasis = (float) sideLength  * RectangularPrism::rightBasis;

    for(int i = 0; i < levels; i++) {
        if(!prevLevel.size()) {
            // level = 1
            currLevel.push_back(new RectangularPrism(origin, shader, sideWidth, sideLength, sideHeight));
            prevLevel = currLevel;
            currLevel = std::vector<GameObject*>();
        } else {
            // level > 1
            for(int j = 0; j <= i-1; j++) {
                GameObject *prevPrism = prevLevel[j];
                glm::vec2 pos = prevPrism->getOrigin();

                if(j == i - 1) {
                    // add an extra prism for last column
                    currLevel.push_back(new RectangularPrism(pos + scaledLeftBasis - scaledTopBasis, shader, sideWidth, sideLength, sideHeight));
                    currLevel.push_back(new RectangularPrism(pos + scaledRightBasis - scaledTopBasis, shader, sideWidth, sideLength, sideHeight));
                } else {
                    currLevel.push_back(new RectangularPrism(pos + scaledLeftBasis - scaledTopBasis, shader, sideWidth, sideLength, sideHeight));
                }
            }
            prevLevel = currLevel;
            currLevel = std::vector<GameObject*>();
        }
        addGameObjects(prevLevel); // previous level completed so add its objects
    }
}