#include "entity.h"
#include "rectangular_prism.h"
#include "animation.h"
#include "animation_manager.h"

/* ********************************************** */
/*                   PUBLIC                       */
/* ********************************************** */

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
    this->totalAirTime  = totalAirTime;
    this->nxtPlatform   = nullptr;
}

/* ********************************************** */
/*                  GETTERS                       */
/* ********************************************** */

Platform *Entity::getCurrentPlatform() { return currPlatform; }

bool   Entity::isAirBorne()        { return airBorne;    }
float  Entity::getMaxJumpHeight()  { return maxJumpHeight; }
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

void Entity::update(const bool *keys) {
    if(!isAirBorne() && playerHasMoved(keys)) { 
        Entity::DIRECTIONS direction = Entity::DIRECTIONS::NORTHEAST;
        if(keys[GLFW_KEY_W]) {
            direction = Entity::DIRECTIONS::NORTHEAST;
        } else if(keys[GLFW_KEY_A]) {
            direction = Entity::DIRECTIONS::NORTHWEST;
        } else if(keys[GLFW_KEY_D]) {
            direction = Entity::DIRECTIONS::SOUTHEAST;
        } else {
            direction = Entity::DIRECTIONS::SOUTHWEST;
        } 
        
        jump(direction);
    }
}

void Entity::jump(Entity::DIRECTIONS dir) {
    initJump(dir);
    struct AnimationCallbacks ac = { .startupDelayCallback = nullptr, 
                                     .runningCallback = [this] (float delta) { jumpRunning(delta); }, 
                                     .cleanupDelayCallback = [this] () { jumpCleanupDelay(); },
                                     .cleanupCallback = [this] () { jumpCleanup(); }};
    struct AnimationTimes at = { .startupDelayTime = 0.0f,
                                 .runningTime = 0.42f,
                                 .cleanupDelayTime = 0.133f };

    AnimationManager::push(&at, &ac);
}

/* ********************************************** */
/*                  PRIVATE                       */
/* ********************************************** */

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

void Entity::initJump(DIRECTIONS dir) {
    if (!currPlatform || airBorne) return;

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
    }

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
}

void Entity::jumpRunning(float t) {
    glm::vec2 nxtPos;

    nxtPos = (1.0f - t) * (1.0f - t) * startPos + 2.0f * t * (1.0f - t) * peakPos + t * t * endPos;

    setOrigin(nxtPos);
}

void Entity::jumpCleanupDelay() {
    currPlatform = nxtPlatform;
    setOrigin(endPos);
    if(nxtPlatform)
        nxtPlatform->step();
}

void Entity::jumpCleanup() {
    airBorne = false;
}

bool Entity::playerHasMoved(const bool *keys) { return keys[GLFW_KEY_W] || keys[GLFW_KEY_A] || keys[GLFW_KEY_S] || keys[GLFW_KEY_D]; }