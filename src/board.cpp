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
    numObjects = (levels) * (levels + 1) / 2; // natural summation 
}

/* ********************************************** */
/*                  GETTERS                       */
/* ********************************************** */

GameObject *Board::getGameObject(GLuint index) {
    if(index >= numObjects) {
        std::cerr << "index:" << index << "is out of range" << std::endl;
        return nullptr; 
    }

    GLuint row = std::floor(std::sqrt(2.0f * index + 1.0f / 4.0f) - 1.0f / 2.0f);
    GLuint prevLevel = row;
    GLuint col = index - (prevLevel) * (prevLevel + 1) / 2.0f;

    return board[row][col];
}

GameObject *Board::getChildGameObject(GameObject *currObject, TREE_DIRECTION_TYPE tdt) {
    if(numObjects == 0) return nullptr;

    GLuint index = currObject->getID() - board[0][0]->getID();

    if(index >= numObjects) {
        std::cerr << "index:" << index << "is out of range" << std::endl;
        return nullptr; 
    }

    if(tdt != TREE_DIRECTION_TYPE::LEFT && tdt != TREE_DIRECTION_TYPE::RIGHT) {
        std::cerr << "Child type:" << tdt << "not recognized" << std::endl;
        return nullptr;
    }

    GLuint level = std::floor(std::sqrt(2.0f * index + 1.0f / 4.0f) - 1.0f / 2.0f) + 1;
    GLuint prevLevel = level - 1;
    GLuint nextLevel = level + 1; // 1 indexed 
    GLuint col = index - (prevLevel) * (prevLevel + 1) / 2.0f;

    // out of bounds
    if(nextLevel * (nextLevel + 1) / 2 > numObjects) return nullptr;

    // always one extra cube on the next level preventing index out of bounds
    return tdt == TREE_DIRECTION_TYPE::LEFT ? board[nextLevel - 1][col] : board[nextLevel - 1][col+1]; 
}

GameObject *Board::getParentGameObject(GameObject *currObject, TREE_DIRECTION_TYPE tdt) {
    if(numObjects == 0) return nullptr;

    GLuint index = currObject->getID() - board[0][0]->getID();

    if(index >= numObjects) {
        std::cerr << "index:" << index << "is out of range" << std::endl;
        return nullptr; 
    }

    if(tdt != TREE_DIRECTION_TYPE::LEFT && tdt != TREE_DIRECTION_TYPE::RIGHT) {
        std::cerr << "Parent type:" << tdt << "not recognized" << std::endl;
        return nullptr;
    }

    GLuint level = std::floor(std::sqrt(2.0f * index + 1.0f / 4.0f) - 1.0f / 2.0f) + 1;
    GLuint prevLevel = level - 1;
    GLuint col = index - (prevLevel) * (prevLevel + 1) / 2.0f;

    if(prevLevel == 0 || 
       (tdt == TREE_DIRECTION_TYPE::LEFT && col == 0) ||
       (tdt == TREE_DIRECTION_TYPE::RIGHT && col == level - 1)) return nullptr;

    return tdt == TREE_DIRECTION_TYPE::LEFT ? board[prevLevel - 1][col - 1] : board[prevLevel - 1][col]; 
}

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

void Board::addGameObjectsToGame(Game *game) {
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[i].size(); j++) {
            game->addGameObject(board[i][j]);
        }
    }
}