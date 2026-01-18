#pragma once

#include "entity.h"

#include <iostream>

#include <glm/glm.hpp>

class GBert : public Entity {
    public:
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
};