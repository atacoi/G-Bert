#include "animation_manager.h"

/* ********************************************** */
/*                Static Fields                   */
/* ********************************************** */

std::list<Animation*> AnimationManager::_animationList; 

/* ********************************************** */
/*               Static Functions                 */
/* ********************************************** */

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

Animation *AnimationManager::pop() {
    if(_animationList.empty()) return nullptr;
    
    Animation *top = _animationList.front();
    _animationList.pop_front();
    return top;
}

void AnimationManager::push(struct AnimationTimes *at, AnimationCallbacks *ac) {
    _animationList.push_back(new Animation(at, ac));
}


void AnimationManager::fire(float delta) {
    for(std::list<Animation*>::iterator it = _animationList.begin(); it != _animationList.end(); ) {
        Animation *a = *it;
        a->fire(delta);
        if(a->hasFinished()) {
            delete a;
            it = _animationList.erase(it);
        } else {
            ++it;
        }
    }
}