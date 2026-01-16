#pragma once

#include "game_object.h"

#include <iostream>

#include <glm/glm.hpp>

class GBert : public GameObject {
    public:
        enum DIRECTIONS {
            NORTHEAST,
            NORTHWEST,
            SOUTHWEST,
            SOUTHEAST
        };

        /* ********************************************** */
        /*                CONSTRUCTORS                    */
        /* ********************************************** */

        GBert(Shader *shader, Texture2D *texture, GLint width, GLint height);

        /* ********************************************** */
        /*                  GETTERS                       */
        /* ********************************************** */

        GameObject *getCurrentObject();

        /* ********************************************** */
        /*                 UTILITIES                      */
        /* ********************************************** */

        void render(int screenWidth, int screenHeight) override;

        void jump(GBert::DIRECTIONS direction, float delta, glm::vec2 destination);

    private:
        GameObject *currObject;
        float currAirTime;
        float totalAirTime;
        GLint maxHeight;
        bool isAirBorne;
};