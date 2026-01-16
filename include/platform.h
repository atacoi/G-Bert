#pragma once

#include "game_object.h"

#include <glm/glm.hpp>

class Platform : public GameObject {
    public:
        /* ********************************************** */
        /*                CONSTRUCTORS                    */
        /* ********************************************** */

        Platform(glm::vec2 origin   = glm::vec2(0.0f, 0.0f),
                 Shader *shader     = nullptr, 
                 Texture2D *texture = nullptr, 
                 int width          = 10, 
                 int height         = 10);

        /* ********************************************** */
        /*                  GETTERS                       */
        /* ********************************************** */

        Platform *getNorthEast();
        Platform *getNorthWest();
        Platform *getSouthWest();
        Platform *getSouthEast();

        /* ********************************************** */
        /*                  SETTERS                       */
        /* ********************************************** */

        void setNorthEast(Platform *ne);
        void setNorthWest(Platform *nw);
        void setSouthWest(Platform *sw);
        void setSouthEast(Platform *se);

    private:
        Platform *northEast;
        Platform *northWest;
        Platform *southWest;
        Platform *southEast;
};