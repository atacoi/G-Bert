#include "cube.h"
#include "shader.h"
#include "game.h"

#include <iostream>

#include <glm/glm.hpp>

#include <glad/glad.h>

class Board {
    public:
        /* ********************************************** */
        /*                CONSTRUCTORS                    */
        /* ********************************************** */

        Board(Shader *shader, GLint levels, glm::vec2 startingPosition);

        /* ********************************************** */
        /*                  UTILITY                       */
        /* ********************************************** */

        void addGameObjectsToBoard(Game *game);

    private:
        std::vector<std::vector<GameObject*>> board; 
};