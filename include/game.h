#pragma once

#include "game_object.h"
#include "entity.h"
#include "rectangular_prism.h"
#include "global_constants.h"
#include "animation_manager.h"

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
        bool getKey(int key);
        bool getProcessed(int key);

        /* ********************************************** */
        /*                SETTERS                         */
        /* ********************************************** */

        void setScreenWidth(int width);
        void setScreenHeight(int height);
        void setCurrState(GAME_STATES state);
        void setKey(int key, bool val);
        void setProcessed(int key, bool val);

        /* ********************************************** */
        /*                UTILITY                         */
        /* ********************************************** */

        bool isRunning();
        void init();
        void update();
        void fireAnimations(float delta);
        void render(GLFWwindow *window);

        void addGameObject(GameObject *go);
        void addGameObjects(const std::vector<GameObject*> &gos);

    private:
        int screenWidth;
        int screenHeight;
        std::string screenTitle;
        GAME_STATES currState;
        std::map<GLuint, GameObject*> gameObjectMap;
        Entity *player;
        GLuint QUAD_VAO;
        bool keys[MAX_KEYS];
        bool keysProcessed[MAX_KEYS];

        /* ********************************************** */
        /*                UTILITY                         */
        /* ********************************************** */

        void initializeVAO();
        void initializeShaders();
        void initializeTextures();
        void initializeBoard(glm::vec2 origin);

        // returns a pointer to the starting prism
        RectangularPrism *generatePlatforms(glm::vec2 origin, Shader *shader, glm::vec3 rectangularPrismSize, int levels);

        void freeGameObjects();
};