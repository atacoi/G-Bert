#pragma once

#include "game_object.h"
#include "rectangular_prism.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube : public RectangularPrism {
    public:
        /* ********************************************** */
        /*                CONSTRUCTORS                    */
        /* ********************************************** */

        Cube(glm::vec2 origin = glm::vec2(0.0f, 0.0f),
             Shader *shader   = nullptr,
             int sideLen      = 50);
};