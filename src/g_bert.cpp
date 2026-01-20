#include "g_bert.h"

GBert::GBert (glm::vec2 origin,
              Shader *shader, 
              Texture2D *texture, 
              int width, 
              int height,
              float maxHeight):
              Entity::Entity(origin, shader, texture, width, height, maxHeight)
{
    setCurrentFrame(GBERT_FRAME_INDICES::SOUTHWEST_STANDING);
    setFrameCount(GBERT_FRAME_INDICES::SIZE);
}

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

void GBert::jump(GBert::DIRECTIONS dir) {
    int frameIndex = -1;
    switch(dir) {
        case DIRECTIONS::NORTHEAST:
            frameIndex = GBERT_FRAME_INDICES::NORTHEAST_STANDING;
            break; 

        case DIRECTIONS::NORTHWEST:
            frameIndex = GBERT_FRAME_INDICES::NORTHWEST_STANDING;
            break;

        case DIRECTIONS::SOUTHEAST:
            frameIndex = GBERT_FRAME_INDICES::SOUTHEAST_STANDING;
            break;

        case DIRECTIONS::SOUTHWEST:
            frameIndex = GBERT_FRAME_INDICES::SOUTHWEST_STANDING;
            break;
    }
    setCurrentFrame(frameIndex);
    Entity::jump(dir);
}

/* ********************************************** */
/*                 PROTECTED                      */
/* ********************************************** */

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

void GBert::jumpCleanupDelay() {
    int frameIndex;
    switch(currDirection) {
        case Entity::DIRECTIONS::NORTHEAST:
            frameIndex = GBert::GBERT_FRAME_INDICES::NORTHEAST_SITTING;
            break;

        case Entity::DIRECTIONS::NORTHWEST:
            frameIndex = GBert::GBERT_FRAME_INDICES::NORTHWEST_SITTING;
            break;

        case Entity::DIRECTIONS::SOUTHEAST:
            frameIndex = GBert::GBERT_FRAME_INDICES::SOUTHEAST_SITTING;
            break;

        case Entity::DIRECTIONS::SOUTHWEST:
            frameIndex = GBert::GBERT_FRAME_INDICES::SOUTHWEST_SITTING;
            break;
    }
    setCurrentFrame(frameIndex);
    Entity::jumpCleanupDelay();
}