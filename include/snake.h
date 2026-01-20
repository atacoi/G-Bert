#pragma once

#include "entity.h"

#include <iostream>

#include <glm/glm.hpp>

class Snake : public Entity {
    public:
        /* ********************************************** */
        /*                    ENUMS                       */
        /* ********************************************** */
        
        enum SNAKE_FRAME_INDICES {
            NORTHEAST_SITTING,
            NORTHEAST_STANDING,
            NORTHWEST_SITTING,
            NORTHWEST_STANDING,
            SOUTHEAST_SITTING,
            SOUTHEAST_STANDING,
            SOUTHWEST_SITTING,
            SOUTHWEST_STANDING,
            SIZE
        };

        /* ********************************************** */
        /*                CONSTRUCTORS                    */
        /* ********************************************** */

        Snake (glm::vec2 origin   = glm::vec2(0.0f, 0.0f),
               Shader *shader     = nullptr, 
               Texture2D *texture = nullptr, 
               int width          = 50, 
               int height         = 100,
               float maxHeight    = 40.0f);

        /* ********************************************** */
        /*                  UTILITY                       */
        /* ********************************************** */

        void jump(Snake::DIRECTIONS dir) override;

        void update(const bool *keys, const Entity *player) override;

    protected:
        /* ********************************************** */
        /*                  UTILITY                       */
        /* ********************************************** */

        void jumpCleanupDelay() override;
};