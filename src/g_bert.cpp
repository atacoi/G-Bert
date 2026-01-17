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
}