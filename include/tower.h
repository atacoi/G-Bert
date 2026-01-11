#pragma once

#include "game_object.h"

class Tower : public GameObject {
    public:
        /* ********************************************** */
        /*                Utility                         */
        /* ********************************************** */

        void render(int screenWidth, int screenHeight) override;
};