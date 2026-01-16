#include "game_object.h"
#include "game.h"
#include "global_constants.h"
#include <math.h>

/* ********************************************** */
/*                CONSTRUCTORS                    */
/* ********************************************** */

GameObject::GameObject(glm::vec2 origin, 
                       Shader *shader, 
                       Texture2D *texture, 
                       int width, 
                       int height):
                       origin(origin),
                       shader(shader),
                       texture(texture),
                       width(width),
                       height(height)
{
    ID = STATIC_IDs++;
}

/* ********************************************** */
/*                DESTRUCTORS                     */
/* ********************************************** */

GameObject::~GameObject() { }

/* ********************************************** */
/*                  GETTERS                       */
/* ********************************************** */

unsigned int GameObject::getID() const { return ID; }

Shader *GameObject::getShader() const { return shader; }

Texture2D *GameObject::getTexture() const { return texture; }

glm::vec2 GameObject::getOrigin() const { return origin; }

int GameObject::getWidth() const { return width; }

int GameObject::getHeight() const { return height; }

glm::vec2 GameObject::getCenter() const { return origin + glm::vec2(width * 0.5f, height * 0.5f); }

/* ********************************************** */
/*                  SETTERS                       */
/* ********************************************** */

void GameObject::setOrigin(glm::vec2 origin) { this->origin = origin; }

void GameObject::setShader(Shader *shader) { this->shader = shader; }

void GameObject::setTexture(Texture2D *texture) { this->texture = texture; }

void GameObject::setWidth(int width) { 
    if(width < 0) {
        std::cerr << "Game Object width must be a non-negative integer" << std::endl;
        return;
    }

    this->width = width; 
}

void GameObject::setHeight(int height) { 
    if(height < 0) {
        std::cerr << "Game Object height must be a non-negative integer" << std::endl;
        return;
    }

    this->height = height; 
}

/* ********************************************** */
/*                  Utility                       */
/* ********************************************** */

void GameObject::render(int screenWidth, int screenHeight) {
    if(!texture) {
        texture->use();
    }

    if(!shader) {
        std::cerr << "Shader is not defined for game object with ID" << ID << std::endl;
        return;
    }

    shader->use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(origin, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * width, 0.5f * height, 0.0f));
    model = glm::translate(model, glm::vec3(-0.5f * width, -0.5f * height, 0.0f));
    model = glm::scale(model, glm::vec3(width, height, 1.0f));

    shader->setUniformMatrix4f(model, "model");

    glm::mat4 projection = glm::ortho(
        0.0f,
        (float)screenWidth,
        (float)screenHeight,
        0.0f,
        -1.0f,
        1.0f
    );

    shader->setUniformMatrix4f(projection, "projection");

    glDrawArrays(GL_TRIANGLES, 0, 6); // assumes that the VAO is bound before each object is rendered 
}

void GameObject::translate(glm::vec2 position) { setOrigin(position); }