#include <iostream>
#include <string.h>
#include "game.h"
#include <stdlib.h>

/* ********************************************** */
/*                CONSTRUCTORS                    */
/* ********************************************** */

Game::Game() {
    screenWidth = 1280;
    screenHeight = 720;
    char buffer[] = {'G', '-', 'B', 'e', 'r', 't', '\0'};
    screenTitle = NULL;
    this->setTitle(buffer);
    currState = GAME_STATES::ACTIVE;
}

Game::Game(int width, int height, char *title) {
    screenWidth = width;
    screenHeight = height;
    screenTitle = NULL;
    this->setTitle(title);
    currState = GAME_STATES::ACTIVE;
}

/* ********************************************** */
/*                DESTRUCTORS                     */
/* ********************************************** */

Game::~Game() {
    free(screenTitle);
    currState = GAME_STATES::TERMINATED;
}

/* ********************************************** */
/*                GETTERS                         */
/* ********************************************** */

int Game::getScreenWidth() { return screenWidth; }

int Game::getScreenHeight() { return screenHeight; }

char *Game::getTitle() { return screenTitle; }

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

void Game::setTitle(char *title) {
    free(screenTitle); // ok since constructor sets to NULL pointer initially 
    screenTitle = (char*)malloc(strlen(title) + 1);
    strcpy(screenTitle, title);
}

void Game::setCurrState(GAME_STATES state) { currState = state; }

/* ********************************************** */
/*                UTILITY                         */
/* ********************************************** */

bool Game::isRunning() { return this->currState == GAME_STATES::ACTIVE; }