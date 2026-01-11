#pragma once

#include "game_object.h"

#include <glad/glad.h>
#include <map>
#include <GLFW/glfw3.h>

enum GAME_STATES {
    ACTIVE,
    TERMINATED,
    len
};

extern GLuint STATIC_IDs;

static const float QUAD[] = {
    0.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
};

const GLint VERTEX_SIZE = 3;

class Game {
    public:
        /* ********************************************** */
        /*                CONSTRUCTORS                    */
        /* ********************************************** */

        Game();
        Game(int width, int height, const std::string &);

        /* ********************************************** */
        /*                DESTRUCTORS                     */
        /* ********************************************** */

        ~Game();

        /* ********************************************** */
        /*                GETTERS                         */
        /* ********************************************** */

        int getScreenWidth();
        int getScreenHeight();
        std::string &getTitle();
        GAME_STATES getCurrState();

        /* ********************************************** */
        /*                SETTERS                         */
        /* ********************************************** */

        void setScreenWidth(int width);
        void setScreenHeight(int height);
        void setCurrState(GAME_STATES state);

        /* ********************************************** */
        /*                UTILITY                         */
        /* ********************************************** */

        bool isRunning();
        void render(GLFWwindow *window);

        void initializeVAO();

        void addGameObject(GameObject *go);

    private:
        int screenWidth;
        int screenHeight;
        std::string screenTitle;
        GAME_STATES currState;
        std::map<GLuint, GameObject*> gameObjectMap;
        GLuint QUAD_VAO;

};