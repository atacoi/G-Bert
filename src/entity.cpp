#include "entity.h"
#include "rectangular_prism.h"

 /* ********************************************** */
/*                CONSTRUCTORS                    */
/* ********************************************** */

Entity::Entity (glm::vec2 origin,
                Shader *shader, 
                Texture2D *texture, 
                int width, 
                int height,
                float maxHeight,
                float totalAirTime):
                GameObject::GameObject(origin, shader, texture, width, height)
{
    this->airBorne      = false;
    this->maxJumpHeight = maxHeight;
    this->currAirTime   = 0;
    this->totalAirTime  = totalAirTime;
    this->currDirection = Entity::DIRECTIONS::NONE;
}

/* ********************************************** */
/*                  GETTERS                       */
/* ********************************************** */

Platform *Entity::getCurrentPlatform() { return currPlatform; }

bool   Entity::isAirBorne()        { return airBorne;    }
float  Entity::getMaxJumpHeight()  { return maxJumpHeight; }
float Entity::getCurrentAirTime() { return currAirTime;   }
float Entity::getTotalAirTime()   { return totalAirTime;  }

int Entity::getFrameCount() { return frameCount; }

/* ********************************************** */
/*                  SETTERS                       */
/* ********************************************** */

void Entity::setCurrentPlatform(Platform *p) { 
    currPlatform = p; 
    if(p) {
        glm::vec2 c = p->getCenter();
        setOrigin(glm::vec2(c.x - getWidth() * 0.5f, c.y - getHeight()));
    }
}

void Entity::setIsAirBorne     (bool isAirBorne)     { airBorne = isAirBorne;                                             }
void Entity::setMaxJumpHeight  (float maxJumpHeight) { this->maxJumpHeight = maxJumpHeight < 0.0f ? 0.0f : maxJumpHeight; }
void Entity::setCurrentAirTime (float totalAirTime)  { this->totalAirTime  = totalAirTime  < 0.0  ? 0.0  : totalAirTime;  }

void Entity::setFrameCount(int frameCount) { this->frameCount = std::max(frameCount, 0); }

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

void Entity::jump(Entity::DIRECTIONS dir, double delta) {
    if (!currPlatform || totalAirTime <= 0.0f) return;

    Platform *nxtPlatform = nullptr;

    if(currDirection != Entity::DIRECTIONS::NONE) dir = currDirection;

    switch(dir) {
        case Entity::DIRECTIONS::NORTHEAST:
            nxtPlatform = currPlatform->getNorthEast();
            break;

        case Entity::DIRECTIONS::NORTHWEST:
            nxtPlatform = currPlatform->getNorthWest();
            break;

        case Entity::DIRECTIONS::SOUTHEAST:
            nxtPlatform = currPlatform->getSouthEast();
            break;

        case Entity::DIRECTIONS::SOUTHWEST:
            nxtPlatform = currPlatform->getSouthWest();
            break;

        case Entity::DIRECTIONS::NONE:
            std::cout << "dealing with none" << std::endl;
            break;
    }

    if(!airBorne) {
        glm::vec2 P0 = getOrigin();
        glm::vec2 P2;

        if(nxtPlatform) {
            P2 = glm::vec2(nxtPlatform->getCenter().x - 0.5f * getWidth(), nxtPlatform->getCenter().y - getHeight());
        } else {
            P2 = glm::vec2(0.0f, 0.0f);
        }

        // peak will occur halfway 
        float t = 0.50f;

        glm::vec2 P0toP2 = P2 - P0;

        glm::vec2 per;

        if(dir == Entity::DIRECTIONS::NORTHEAST || dir == Entity::DIRECTIONS::SOUTHEAST)
            per = glm::normalize(glm::vec2(P0toP2.y, -P0toP2.x));
        else 
            per = glm::normalize(glm::vec2(-P0toP2.y, P0toP2.x));

        glm::vec2 Q = P0 + t * P0toP2 + maxJumpHeight * per;

        // solve for P1 using quadratic bezier formula
        glm::vec2 P1 = (Q - (1.0f - t) * (1.0f - t) * P0 - t * t * P2) / (2.0f * (1.0f - t) * t);

        startPos = P0;
        peakPos  = P1;
        endPos   = P2;
        airBorne = true;
        currDirection = dir;
    } else {
        currAirTime += (float)delta;
    }

    glm::vec2 nxtPos;
    float t = currAirTime / totalAirTime;

    if(t >= 1) {
        airBorne    = false;
        currAirTime = 0.0f;
        nxtPos = endPos;
        currPlatform = nxtPlatform;
        if(nxtPlatform)
            nxtPlatform->step();
        currDirection = Entity::DIRECTIONS::NONE;
    } else {
        nxtPos = (1.0f - t) * (1.0f - t) * startPos + 2.0f * t * (1.0f - t) * peakPos + t * t * endPos;
    }

    setOrigin(nxtPos);
}