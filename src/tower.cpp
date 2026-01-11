#include "tower.h"

void Tower::render(int screenWidth, int screenHeight) {
    this->rotate(45);
    GameObject::render(screenWidth, screenHeight);

}