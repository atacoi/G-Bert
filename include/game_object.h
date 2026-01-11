#pragma once

#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <iostream>

class GameObject {
    public:
        /* ********************************************** */
        /*                CONSTRUCTORS                    */
        /* ********************************************** */

        GameObject();
        GameObject(Shader *shader);
        GameObject(Shader *shader, glm::vec2 position, GLint width, GLint height);

        /* ********************************************** */
        /*                DESTRUCTORS                     */
        /* ********************************************** */

        ~GameObject();

        /* ********************************************** */
        /*                  GETTERS                       */
        /* ********************************************** */

        GLuint getID() const;

        /* ********************************************** */
        /*                  Utility                       */
        /* ********************************************** */
    
        void render(int screenWidth, int screenHeight) const;
        void translate(glm::vec2 position);

    private:
        Shader *shader;
        glm::vec2 position; 
        GLfloat rotationAngle;
        GLint width; 
        GLint height; 
        GLuint ID;
        GLint modelUniformLocation;
};