#include "g_bert.h"

GBert::GBert (glm::vec2 origin,
              Shader *shader, 
              Texture2D *texture, 
              int width, 
              int height,
              float maxHeight,
              float totalAirTime):
              Entity::Entity(origin, shader, texture, width, height, maxHeight, totalAirTime)
{
    Shader *s = getShader();
    if(s) {
        s->use();
        s->setUniform1i(GBERT_FRAME_INDICES::SOUTHWEST_STANDING, "frameIndex");
        s->setUniform1i(GBERT_FRAME_INDICES::SIZE, "columnCount");
    }
}

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

    Shader *s = getShader();
    if(s) {
        s->setUniform1i(frameIndex, "frameIndex");
        s->setUniform1i(GBERT_FRAME_INDICES::SIZE, "columnCount");
    }

    Entity::jump(dir);
}