#pragma once

#include <glad/glad.h>

#include <iostream>

class Texture2D {
    public:
        /* ********************************************** */
        /*                CONSTRUCTORS                    */
        /* ********************************************** */

        Texture2D(std::string imageFile);

        /* ********************************************** */
        /*                  UTILITY                       */
        /* ********************************************** */

        void use();

    private:
        GLuint textureID; 
};