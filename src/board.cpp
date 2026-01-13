#include "board.h"

/* ********************************************** */
/*                CONSTRUCTORS                    */
/* ********************************************** */

Board::Board(Shader *shader, GLint levels, glm::vec2 startingPosition): board() {
    GLint sideLen = 50;

    std::vector<GameObject*> *prevLevel = nullptr;
    std::vector<GameObject*> *currLevel = new std::vector<GameObject*>{};

    glm::vec2 scaledTopBasis   = glm::vec2(sideLen * Cube::topBasis.x, sideLen * Cube::topBasis.y);
    glm::vec2 scaledLeftBasis  = glm::vec2(sideLen * Cube::leftBasis.x, sideLen * Cube::leftBasis.y);
    glm::vec2 scaledRightBasis = glm::vec2(sideLen * Cube::rightBasis.x, sideLen * Cube::rightBasis.y);

    for(int i = 0; i < levels; i++) {
        if(!prevLevel) {
            currLevel->push_back(new Cube(shader, startingPosition, sideLen));
            prevLevel = currLevel;
            currLevel = new std::vector<GameObject*>{};
        } else {
            for(int j = 0; j <= i-1; j++) {
                GameObject *prevGO = (*prevLevel)[j];
                glm::vec2 pos = prevGO->getPosition();

                if (!dynamic_cast<Cube*>(prevGO)) { std::cout << "Not a cube...\n"; return; }

                if(j == i - 1) {
                    currLevel->push_back(new Cube(shader, pos + scaledLeftBasis - scaledTopBasis, sideLen));
                    currLevel->push_back(new Cube(shader, pos + scaledRightBasis - scaledTopBasis, sideLen));
                } else {
                    currLevel->push_back(new Cube(shader, pos + scaledLeftBasis - scaledTopBasis, sideLen));
                }
            }
            delete prevLevel;
            prevLevel = currLevel;
            if(i != levels-1)
                currLevel = new std::vector<GameObject*>{};
        }
        board.push_back(*prevLevel);
    }
}

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

void Board::addGameObjectsToBoard(Game *game) {
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[i].size(); j++) {
            game->addGameObject(board[i][j]);
        }
    }
}