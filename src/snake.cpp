#include "snake.h"
#include "rectangular_prism.h"
#include "animation.h"
#include "animation_manager.h"

Snake::Snake (glm::vec2 origin,
              Shader *shader, 
              Texture2D *texture, 
              int width, 
              int height,
              float maxHeight):
              Entity::Entity(origin, shader, texture, width, height, maxHeight)
{
    setCurrentFrame(SNAKE_FRAME_INDICES::SOUTHWEST_STANDING);
    setFrameCount(SNAKE_FRAME_INDICES::SIZE);
}

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

void Snake::jump(Snake::DIRECTIONS dir) {
    int frameIndex = -1;
    switch(dir) {
        case DIRECTIONS::NORTHEAST:
            frameIndex = SNAKE_FRAME_INDICES::NORTHEAST_STANDING;
            break; 

        case DIRECTIONS::NORTHWEST:
            frameIndex = SNAKE_FRAME_INDICES::NORTHWEST_STANDING;
            break;

        case DIRECTIONS::SOUTHEAST:
            frameIndex = SNAKE_FRAME_INDICES::SOUTHEAST_STANDING;
            break;

        case DIRECTIONS::SOUTHWEST:
            frameIndex = SNAKE_FRAME_INDICES::SOUTHWEST_STANDING;
            break;
    }
    setCurrentFrame(frameIndex);

    initJump(dir);
    struct AnimationCallbacks ac = { .startupDelayCallback = nullptr, 
                                     .runningCallback = [this] (float delta) { jumpRunning(delta); }, 
                                     .cleanupDelayCallback = [this] () { jumpCleanupDelay(); },
                                     .cleanupCallback = [this] () { jumpCleanup(); }};
    struct AnimationTimes at = { .startupDelayTime = 0.0f,
                                 .runningTime = 0.69f * (endPos.y - peakPos.y) / (getMaxJumpHeight() * (endPos.y - startPos.y) / 77.0f + 77.0f),
                                 .cleanupDelayTime = 0.133f };

    AnimationManager::push(this->getID(), &at, &ac);
}

void Snake::update(const bool *keys, const Entity *player) {
    if(isAirBorne()) return;

    glm::vec2 sorigin = getOrigin();
    glm::vec2 porigin = player->getOrigin();

    glm::vec2 dir = porigin - sorigin;

    glm::vec2 basis[] = { RectangularPrism::leftBasis, -RectangularPrism::leftBasis, -RectangularPrism::rightBasis, RectangularPrism::rightBasis};
    DIRECTIONS directs[] = { DIRECTIONS::SOUTHWEST, DIRECTIONS::NORTHEAST, DIRECTIONS::NORTHWEST, DIRECTIONS::SOUTHEAST };

    glm::vec2 *winner = &RectangularPrism::leftBasis;
    DIRECTIONS d = DIRECTIONS::SOUTHWEST;
    float bstDot = glm::dot(dir, *winner);

    for(int i = 1; i < 4; i++) {
        float t = glm::dot(dir, basis[i]);
        if(t >= bstDot) {
            bstDot = t;
            winner = &basis[i];
            d = directs[i];
        }
    }

    jump(d);
}

/* ********************************************** */
/*                 PROTECTED                      */
/* ********************************************** */

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

void Snake::jumpCleanupDelay() {
    int frameIndex;
    switch(currDirection) {
        case Entity::DIRECTIONS::NORTHEAST:
            frameIndex = Snake::SNAKE_FRAME_INDICES::NORTHEAST_SITTING;
            break;

        case Entity::DIRECTIONS::NORTHWEST:
            frameIndex = Snake::SNAKE_FRAME_INDICES::NORTHWEST_SITTING;
            break;

        case Entity::DIRECTIONS::SOUTHEAST:
            frameIndex = Snake::SNAKE_FRAME_INDICES::SOUTHEAST_SITTING;
            break;

        case Entity::DIRECTIONS::SOUTHWEST:
            frameIndex = Snake::SNAKE_FRAME_INDICES::SOUTHWEST_SITTING;
            break;
    }
    setCurrentFrame(frameIndex);
    if(endPos.y == 720.0f) {
        setOrigin(startPos);
    } else {
       setCurrentPlatform(nxtPlatform);
        setOrigin(endPos);
    }
    setRenderBehindPlatforms(false);
}