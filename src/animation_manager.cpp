#include "animation_manager.h"

/* ********************************************** */
/*                CONSTRUCTORS                    */
/* ********************************************** */

AnimationManager::AnimationManager(): animationList() {}

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

Animation *AnimationManager::pop() {
    if(animationList.empty()) return nullptr;
    
    Animation *top = animationList.front();
    animationList.pop_front();
    return top;
}

void AnimationManager::push(struct AnimationTimes *at, AnimationCallbacks *ac) {
    animationList.push_back(new Animation(at, ac));
}


void AnimationManager::fire(float delta) {
    for(std::list<Animation*>::iterator it = animationList.begin(); it != animationList.end(); ) {
        Animation *a = *it;
        a->fire(delta);
        if(a->hasFinished()) {
            delete a;
            it = animationList.erase(it);
        } else {
            ++it;
        }
    }
}