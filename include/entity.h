#pragma once

#include "game_object.h"

#include "platform.h"

#include <functional>

class Entity : public GameObject {
    public:
        enum DIRECTIONS {
            NORTHEAST,
            NORTHWEST,
            SOUTHWEST,
            SOUTHEAST,
            NONE
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

        // returns a callback and cleanup
        virtual void initJump(DIRECTIONS dir);

        virtual void jumpRunning(float delta);
        virtual void jumpCleanupDelay();
        virtual void jumpCleanup();

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
};