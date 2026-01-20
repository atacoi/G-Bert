#pragma once

#include "game_object.h"
#include "platform.h"

#include <functional>
#include <GLFW/glfw3.h>

class Entity : public GameObject {
    public:
        enum DIRECTIONS {
            NORTHEAST,
            NORTHWEST,
            SOUTHWEST,
            SOUTHEAST,
        };

        /* ********************************************** */
        /*                CONSTRUCTORS                    */
        /* ********************************************** */
        Entity (glm::vec2 origin   = glm::vec2(0.0f, 0.0f),
                Shader *shader     = nullptr, 
                Texture2D *texture = nullptr, 
                int width          = 10, 
                int height         = 10,
                float maxHeight    = 65.0f);

        /* ********************************************** */
        /*                  GETTERS                       */
        /* ********************************************** */

        Platform *getCurrentPlatform();

        bool isAirBorne();
        float getMaxJumpHeight();

        int getFrameCount();
        int getCurrentFrame();

        bool getRenderBehindPlatforms();

        /* ********************************************** */
        /*                  SETTERS                       */
        /* ********************************************** */

        void setCurrentPlatform(Platform *p);

        void setIsAirBorne(bool isAirBorne);
        void setMaxJumpHeight(float maxJumpHeight);

        void setFrameCount(int frameCount);
        void setCurrentFrame(int frame);

        void setRenderBehindPlatforms(bool rbp);

        /* ********************************************** */
        /*                  UTILITY                       */
        /* ********************************************** */

        virtual void update(const bool *keys, const Entity *player);

        virtual void jump(DIRECTIONS dir); 

        void render(int screenWidth, int screenHeight) override; 

    protected:
        Entity::DIRECTIONS currDirection;

        /* ********************************************** */
        /*                  UTILITY                       */
        /* ********************************************** */

        virtual void initJump(DIRECTIONS dir);

        virtual void jumpRunning(float delta);
        virtual void jumpCleanupDelay();
        virtual void jumpCleanup();

    private:
        Platform *currPlatform; // object the entity is standing on
        Platform *nxtPlatform; // set when jumping

        bool airBorne;
        float maxJumpHeight; 

        int frameCount; // number of animation frames
        int currFrame;

        glm::vec2 startPos; // before the jump
        glm::vec2 peakPos;  // the highest spot
        glm::vec2 endPos;   // after the jump

        bool playerHasMoved(const bool *keys);

        bool renderBehindPlatforms; // if true, the entity is rendered behind the platforms 
};