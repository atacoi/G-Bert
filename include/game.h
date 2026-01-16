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
        void init();
        void update(float delta);
        void render(GLFWwindow *window);

        void addGameObject(GameObject *go);
        void addGameObjects(const std::vector<GameObject*> &gos);

    private:
        int screenWidth;
        int screenHeight;
        std::string screenTitle;
        GAME_STATES currState;
        std::map<GLuint, GameObject*> gameObjectMap;
        GameObject *player;
        GLuint QUAD_VAO;

        /* ********************************************** */
        /*                UTILITY                         */
        /* ********************************************** */

        void initializeVAO();
        void initializeShaders();
        void initializeTextures();
        void initializeBoard(glm::vec2 origin);

        void generatePlatforms(glm::vec2 origin, Shader *shader, glm::vec3 rectangularPrismSize, int levels);
};