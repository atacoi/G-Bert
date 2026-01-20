#include "platform.h"

/* ********************************************** */
/*                CONSTRUCTORS                    */
/* ********************************************** */

Platform::Platform(glm::vec2 origin,
                   Shader *shader, 
                   Texture2D *texture, 
                   int width, 
                   int height):
                   GameObject::GameObject(origin, shader, texture, width, height) 
{ 
  northEast = northWest = southEast = southWest = nullptr;
}

/* ********************************************** */
/*                  GETTERS                       */
/* ********************************************** */

Platform *Platform::getNorthEast() { return northEast; }

Platform *Platform::getNorthWest() { return northWest; }

Platform *Platform::getSouthWest() { return southWest; }

Platform *Platform::getSouthEast() { return southEast; }

/* ********************************************** */
/*                  SETTERS                       */
/* ********************************************** */

void Platform::setNorthEast(Platform *ne) { this->northEast = ne; }

void Platform::setNorthWest(Platform *nw) { this->northWest = nw; }

void Platform::setSouthWest(Platform *sw) { this->southWest = sw; }

void Platform::setSouthEast(Platform *se) { this->southEast = se; }

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

void Platform::step() {}