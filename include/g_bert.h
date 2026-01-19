#pragma once

#include "entity.h"

#include <iostream>

#include <glm/glm.hpp>

class GBert : public Entity {
    public:
        /* ********************************************** */
        /*                    ENUMS                       */
        /* ********************************************** */
        
        enum GBERT_FRAME_INDICES {
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

        GBert (glm::vec2 origin   = glm::vec2(0.0f, 0.0f),
               Shader *shader     = nullptr, 
               Texture2D *texture = nullptr, 
               int width          = 50, 
               int height         = 55,
               float maxHeight    = 40.0f,
               float totalAirTime = 0.46f);

        void jump(GBert::DIRECTIONS dir) override;
};