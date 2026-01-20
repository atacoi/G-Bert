#include "entity.h"
#include "rectangular_prism.h"
#include "animation.h"
#include "animation_manager.h"

#include <limits>

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
                float maxHeight):
                GameObject::GameObject(origin, shader, texture, width, height)
{
    this->airBorne      = false;
    this->maxJumpHeight = maxHeight;
    this->nxtPlatform   = nullptr;
    this->currFrame     = 0;
    this->renderBehindPlatforms = false;
}

/* ********************************************** */
/*                  GETTERS                       */
/* ********************************************** */

Platform *Entity::getCurrentPlatform() { return currPlatform; }

bool   Entity::isAirBorne()        { return airBorne;    }
float  Entity::getMaxJumpHeight()  { return maxJumpHeight; }

int Entity::getFrameCount()   { return frameCount; }
int Entity::getCurrentFrame() { return currFrame;  }

bool Entity::getRenderBehindPlatforms() { return renderBehindPlatforms; }

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

void Entity::setFrameCount(int frameCount) { this->frameCount = std::max(frameCount, 0); }
void Entity::setCurrentFrame(int frame)    { this->currFrame  = std::max(frame, 0);      }

void Entity::setRenderBehindPlatforms(bool rbp) { renderBehindPlatforms = rbp; }

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

void Entity::update(const bool *keys, const Entity *player) {
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
                                 .runningTime = 0.42f * (endPos.y - peakPos.y) / (maxJumpHeight * (endPos.y - startPos.y) / 77.0f + 77.0f),
                                 .cleanupDelayTime = 0.133f };

    AnimationManager::push(this->getID(), &at, &ac);
}

void Entity::render(int screenWidth, int screenHeight) {
    Shader *s = getShader();
    if(s) {
        s->use();
        s->setUniform1i(currFrame, "frameIndex");
        s->setUniform1i(frameCount, "columnCount");
    }
    GameObject::render(screenWidth, screenHeight);
}

/* ********************************************** */
/*                PROTECTED                       */
/* ********************************************** */

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

void Entity::initJump(DIRECTIONS dir) {
    if (!currPlatform || airBorne) return;

    glm::vec2 P0, P1, P2;

    P0 = getOrigin();

    switch(dir) {
        case Entity::DIRECTIONS::NORTHEAST:
            nxtPlatform = currPlatform->getNorthEast();
            currDirection = Entity::DIRECTIONS::NORTHEAST;
            break;

        case Entity::DIRECTIONS::NORTHWEST:
            nxtPlatform = currPlatform->getNorthWest();
            currDirection = Entity::DIRECTIONS::NORTHWEST;
            break;

        case Entity::DIRECTIONS::SOUTHEAST:
            nxtPlatform = currPlatform->getSouthEast();
            currDirection = Entity::DIRECTIONS::SOUTHEAST;
            break;

        case Entity::DIRECTIONS::SOUTHWEST:
            nxtPlatform = currPlatform->getSouthWest();
            currDirection = Entity::DIRECTIONS::SOUTHWEST;
            break;
    }


    if(nxtPlatform) {
        P2 = glm::vec2(nxtPlatform->getCenter().x - 0.5f * getWidth(), nxtPlatform->getCenter().y - getHeight());

        glm::vec2 *tmp = &P2;
        // we want the peak to be closer to P0 in this case not P2
        if(dir == Entity::DIRECTIONS::SOUTHEAST || dir == Entity::DIRECTIONS::SOUTHWEST) {
            tmp = &P0;
        }

        P1 = glm::vec2(tmp->x, tmp->y - maxJumpHeight); // maxJumpHeight is misleading at this time but works
    }

    // falling off the edge
    else {
        RectangularPrism *r = nullptr; 
        
        // only for rectangular prisms disks need to be delt with 
        if((r = dynamic_cast<RectangularPrism*>(currPlatform))) { 
            glm::vec2 basis = glm::vec2(0.0f, 0.0f); 
            int dist = 0; 
            int blocks = 3; // 4 blocks 

            if(dir == Entity::DIRECTIONS::NORTHEAST) { 
                basis = -RectangularPrism::leftBasis; 
                dist = r->getSideWidth(); 
            } else if(dir == Entity::DIRECTIONS::NORTHWEST) { 
                basis = -RectangularPrism::rightBasis; 
                dist = r->getSideLength(); 
            } else if(dir == Entity::DIRECTIONS::SOUTHEAST) { 
                basis = RectangularPrism::rightBasis; 
                dist = r->getSideLength(); 
                blocks = 2;
            } else { 
                basis = RectangularPrism::leftBasis; 
                dist = r->getSideWidth();   
                blocks = 2;
            } 
            int top = r->getSideHeight();
            float ydist = 720.0f - P0.y;
            P2 = glm::vec2(P0.x + blocks * dist * basis.x, 720.0f);
            P1 = glm::vec2(P0.x, P0.y - maxJumpHeight * ydist / 77.0f);
        } else { P2 = P0 + glm::vec2(0.0f, 0.0f); } 
    }

    startPos = P0;
    peakPos  = P1;
    endPos   = P2;
    airBorne = true;
}

void Entity::jumpRunning(float t) {
    if(endPos.y == 720.0f && t >= 0.5f && currDirection != DIRECTIONS::SOUTHEAST && currDirection != DIRECTIONS::SOUTHWEST) {
        setRenderBehindPlatforms(true);
    } else {
        setRenderBehindPlatforms(false);
    }

    glm::vec2 nxtPos;

    nxtPos = (1.0f - t) * (1.0f - t) * startPos + 2.0f * t * (1.0f - t) * peakPos + t * t * endPos;
    
    setOrigin(nxtPos);
}

void Entity::jumpCleanupDelay() {
    if(endPos.y == 720.0f) {
        setOrigin(startPos);
    } else {
        currPlatform = nxtPlatform;
        setOrigin(endPos);
    }
    setRenderBehindPlatforms(false);
    if(nxtPlatform)
        nxtPlatform->step();
}

void Entity::jumpCleanup() {
    airBorne = false;
}

/* ********************************************** */
/*                  PRIVATE                       */
/* ********************************************** */

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

bool Entity::playerHasMoved(const bool *keys) { return keys[GLFW_KEY_W] || keys[GLFW_KEY_A] || keys[GLFW_KEY_S] || keys[GLFW_KEY_D]; }