#include "cube.h"
#include "shader.h"
#include "game.h"

#include <iostream>

#include <glm/glm.hpp>

#include <glad/glad.h>

// indicates if we want the left or right element 
// of either the parent or child cube. 
// not technically a tree (actually a DAG) but close enough 
enum TREE_DIRECTION_TYPE {
    LEFT,
    RIGHT,
};

class Board {
    public:
        /* ********************************************** */
        /*                CONSTRUCTORS                    */
        /* ********************************************** */

        Board(Shader *shader, GLint levels, glm::vec2 startingPosition);

        /* ********************************************** */
        /*                  GETTERS                       */
        /* ********************************************** */

        // index from left to right starting from top
        GameObject *getGameObject(GLuint index); 

        GameObject *getChildGameObject(GameObject *currObject, TREE_DIRECTION_TYPE tdt);

        GameObject *getParentGameObject(GameObject *currObject, TREE_DIRECTION_TYPE tdt);

        /* ********************************************** */
        /*                  UTILITY                       */
        /* ********************************************** */

        void addGameObjectsToGame(Game *game);

    private:
        std::vector<std::vector<GameObject*>> board; 
        GLuint numObjects;
};