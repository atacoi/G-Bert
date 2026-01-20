#include "snake.h"
#include "rectangular_prism.h"

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
    Entity::jump(dir);
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
    Entity::jumpCleanupDelay();
}