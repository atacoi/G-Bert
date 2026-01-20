#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "game.h"
#include "g_bert.h"
#include "resource_manager.h"
#include "rectangular_prism.h"
#include "snake.h"

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
    freeGameObjects();
    glDeleteVertexArrays(1, &QUAD_VAO);
}

/* ********************************************** */
/*                GETTERS                         */
/* ********************************************** */

int Game::getScreenWidth() { return screenWidth; }

int Game::getScreenHeight() { return screenHeight; }

std::string &Game::getTitle() { return screenTitle; }

GAME_STATES Game::getCurrState() { return currState; }

bool Game::getKey(int key) const { 
    if(key < 0 || key >= MAX_KEYS) {
        return false;
    }
    return keys[key]; 
}

bool Game::getProcessed(int key) { 
    if(key < 0 || key >= MAX_KEYS) {
        return false;
    }
    return keysProcessed[key]; 
}

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

void Game::setKey(int key, bool val) { 
    if(key < 0 || key >= MAX_KEYS) {
        return;
    }
    keys[key] = val; 
}

void Game::setProcessed(int key, bool val) { 
    if(key < 0 || key >= MAX_KEYS) {
        return;
    }
    keysProcessed[key] = val; 
}

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

void Game::update() {
    for (auto &gameObject : gameObjectMap) {
        GameObject *go = gameObject.second;
        Entity *e = nullptr;
        if((e = dynamic_cast<Entity*>(go))) {
            e->update(keys, player);
        }
    }
}

void Game::fireAnimations(float delta) {
    AnimationManager::fire(delta);
}

void Game::checkCollisions() {
    glm::vec2 playerPos = player->getOrigin();
    Entity *e = nullptr;
    for(auto &go : gameObjectMap) {
        if(go.second != player && (e = dynamic_cast<Entity*>(go.second))) {
            glm::vec2 enemyPos = e->getOrigin();
            if(playerPos.x < enemyPos.x + e->getWidth() &&
                playerPos.x + player->getWidth() > enemyPos.x &&
                playerPos.y < enemyPos.y + e->getHeight() && 
                playerPos.y + player->getHeight() > enemyPos.y) {
                    AnimationManager::removeAll(player->getID());
                    std::cout << "collided" << std::endl;
                    break;
                }
        }   
    }
}

void Game::render(GLFWwindow *window) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(QUAD_VAO);

    std::map<GLuint, GameObject*>::iterator it;

    std::vector<Platform*> platforms;
    std::vector<Entity*> entitiesLeft;
    for (auto &gameObject : gameObjectMap) {
        Entity *e;
        Platform *p;
        if((e = dynamic_cast<Entity*>(gameObject.second))) {
            if(e->getRenderBehindPlatforms()) {
                e->render(screenWidth, screenHeight);
            } else {
                entitiesLeft.push_back(e);
            }
        } else if((p = dynamic_cast<Platform*>(gameObject.second))) {
            platforms.push_back(p);
        } else {
            std::cerr << "unrecognized" << std::endl;
        }
       //gameObject.second->render(screenWidth, screenHeight);
    }
    for (Platform *p : platforms) {
        p->render(screenWidth, screenHeight);
    }

    for (Entity *e : entitiesLeft) {
        e->render(screenWidth, screenHeight);
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
    ResourceManager::createTexture("snake.png", "snake");
}

void Game::initializeBoard(glm::vec2 origin) {
    glm::vec3 rectPrismSize = glm::vec3(50, 50, 55);

    int levels = 7;

    Shader *shader = ResourceManager::getShader("default");
    RectangularPrism *startingPrism = generatePlatforms(origin, shader, rectPrismSize, levels);

    glm::vec2 o = glm::vec2(0.0f, 0.0f);

    player = new GBert (o, 
                        ResourceManager::getShader("sprite"), 
                        ResourceManager::getTexture("g-bert")
                    );

    Snake *s = new Snake (o, 
                        ResourceManager::getShader("sprite"), 
                        ResourceManager::getTexture("snake")
                    );
    addGameObject(player);
    addGameObject(s);
    Platform *bottomRight = startingPrism;
    while(bottomRight && bottomRight->getSouthEast()) {
        bottomRight = bottomRight->getSouthEast();
    }
    s->setCurrentPlatform(bottomRight);
    player->setCurrentPlatform(startingPrism);
}

RectangularPrism *Game::generatePlatforms(glm::vec2 origin, Shader *shader, glm::vec3 rectangularPrismSize, int levels) {
    std::vector<GameObject*> prevLevel;
    std::vector<GameObject*> currLevel;

    int sideWidth  = rectangularPrismSize.x;
    int sideLength = rectangularPrismSize.y;
    int sideHeight = rectangularPrismSize.z;

    glm::vec2 scaledTopBasis   = (float) sideHeight  * RectangularPrism::topBasis;
    glm::vec2 scaledLeftBasis  = (float) sideWidth   * RectangularPrism::leftBasis;
    glm::vec2 scaledRightBasis = (float) sideLength  * RectangularPrism::rightBasis;

    RectangularPrism *startingPrism = nullptr;

    for(int i = 0; i < levels; i++) {
        if(!prevLevel.size()) {
            // level = 1
            startingPrism = new RectangularPrism(origin, shader, sideWidth, sideLength, sideHeight);
            currLevel.push_back(startingPrism);
            prevLevel = currLevel;
            currLevel = std::vector<GameObject*>();
        } else {
            // level > 1
            for(int j = 0; j <= i-1; j++) {
                RectangularPrism *sndPrevPrism = j > 0 ? dynamic_cast<RectangularPrism*>(prevLevel[j - 1]) : nullptr;
                RectangularPrism *prevPrism = dynamic_cast<RectangularPrism*>(prevLevel[j]);
                glm::vec2 pos = prevPrism->getOrigin();

                RectangularPrism *r = new RectangularPrism(pos + scaledLeftBasis - scaledTopBasis, shader, sideWidth, sideLength, sideHeight);
                r->setNorthEast(prevPrism);
                r->setNorthWest(sndPrevPrism);

                if(sndPrevPrism) {
                    sndPrevPrism->setSouthEast(r);
                }

                prevPrism->setSouthWest(r);

                currLevel.push_back(r);

                if(j == i - 1) {
                    // add an extra prism for last column
                    RectangularPrism *r = new RectangularPrism(pos + scaledRightBasis - scaledTopBasis, shader, sideWidth, sideLength, sideHeight);
                    prevPrism->setSouthEast(r);
                    r->setNorthWest(prevPrism);
                    currLevel.push_back(r);
                }
            }
            prevLevel = currLevel;
            currLevel = std::vector<GameObject*>();
        }
        addGameObjects(prevLevel); // previous level completed so add its objects
    }
    return startingPrism;
}

void Game::freeGameObjects() {
    for (auto &gameObject : gameObjectMap) {
        delete gameObject.second;
    }
    gameObjectMap.clear();
}