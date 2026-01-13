#pragma once

#include "game_object.h"

#include <iostream>

class GBert : public GameObject {
    public:
        /* ********************************************** */
        /*                CONSTRUCTORS                    */
        /* ********************************************** */

        GBert(Shader *shader, Texture2D *texture, GLint width, GLint height);
};