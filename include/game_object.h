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

        GameObject(glm::vec2 origin   = glm::vec2(0.0f, 0.0f),
                   Shader *shader     = nullptr, 
                   Texture2D *texture = nullptr, 
                   int width          = 10, 
                   int height         = 10);

        /* ********************************************** */
        /*                DESTRUCTORS                     */
        /* ********************************************** */

        ~GameObject();

        /* ********************************************** */
        /*                  GETTERS                       */
        /* ********************************************** */

        unsigned int getID() const;

        glm::vec2 getOrigin() const;

        Shader    *getShader()  const;
        Texture2D *getTexture() const;

        virtual int getWidth()  const;
        virtual int getHeight() const;

        virtual glm::vec2 getCenter() const;

        /* ********************************************** */
        /*                  SETTERS                       */
        /* ********************************************** */

        void setOrigin(glm::vec2 origin);
        void setShader(Shader *shader);
        void setTexture(Texture2D *texture);
        void setWidth(int width);
        void setHeight(int height);

        /* ********************************************** */
        /*                  Utility                       */
        /* ********************************************** */
    
        virtual void render(int screenWidth, int screenHeight);
        virtual void translate(glm::vec2 position);

    private:
        unsigned int ID;

        glm::vec2 origin; // top-left corner

        Shader    *shader;
        Texture2D *texture;

        int width; 
        int height; 
};