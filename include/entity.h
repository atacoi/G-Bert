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
                float maxHeight    = 65.0f,
                float totalAirTime = 0.44f);

        /* ********************************************** */
        /*                  GETTERS                       */
        /* ********************************************** */

        Platform *getCurrentPlatform();

        bool isAirBorne();
        float getMaxJumpHeight();
        float getTotalAirTime();

        int getFrameCount();

        /* ********************************************** */
        /*                  SETTERS                       */
        /* ********************************************** */

        void setCurrentPlatform(Platform *p);

        void setIsAirBorne(bool isAirBorne);
        void setMaxJumpHeight(float maxJumpHeight);
        void setCurrentAirTime(float totalAirTime);

        void setFrameCount(int frameCount);

        /* ********************************************** */
        /*                  UTILITY                       */
        /* ********************************************** */

        virtual void update(const bool *keys);

        virtual void jump(DIRECTIONS dir); 

    private:
        Platform *currPlatform; // object the entity is standing on
        Platform *nxtPlatform; // set when jumping

        bool airBorne;
        float maxJumpHeight; 
        float totalAirTime;

        int frameCount; // number of animation frames

        glm::vec2 startPos; // before the jump
        glm::vec2 peakPos;  // the highest spot
        glm::vec2 endPos;   // after the jump

        /* ********************************************** */
        /*                  UTILITY                       */
        /* ********************************************** */

        void initJump(DIRECTIONS dir);

        void jumpRunning(float delta);
        void jumpCleanupDelay();
        void jumpCleanup();

        bool playerHasMoved(const bool *keys);
};