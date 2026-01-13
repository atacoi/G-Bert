#pragma once

#include "shader.h"
#include "texture2d.h"

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
        GameObject(Shader *shader, Texture2D *texture, GLint width, GLint height);
        GameObject(Shader *shader, glm::vec2 position, GLint width, GLint height);

        /* ********************************************** */
        /*                DESTRUCTORS                     */
        /* ********************************************** */

        ~GameObject();

        /* ********************************************** */
        /*                  GETTERS                       */
        /* ********************************************** */

        GLuint getID() const;
        Shader *getShader() const;
        glm::vec2 getPosition() const;
        GLint getWidth() const;
        GLint getHeight() const;

        /* ********************************************** */
        /*                  SETTERS                       */
        /* ********************************************** */

        void setPosition(glm::vec2 position);

        /* ********************************************** */
        /*                  Utility                       */
        /* ********************************************** */
    
        virtual void render(int screenWidth, int screenHeight);
        virtual void translate(glm::vec2 position);
        void rotate(float degree); // in degrees

    private:
        Shader *shader;
        Texture2D *texture;
        glm::vec2 position; 
        GLfloat rotationAngle;
        GLint width; 
        GLint height; 
        GLuint ID;
        GLint modelUniformLocation;
};