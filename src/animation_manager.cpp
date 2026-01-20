#include "animation_manager.h"

/* ********************************************** */
/*                Static Fields                   */
/* ********************************************** */

std::map<unsigned int, Animation*> AnimationManager::_animationMap;

/* ********************************************** */
/*               Static Functions                 */
/* ********************************************** */

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

Animation *AnimationManager::remove(unsigned int gameObjectID) {
    if(_animationMap.empty()) return nullptr;
    
    auto it = _animationMap.find(gameObjectID);
    if(it == _animationMap.end()) {
        return nullptr;
    }
    _animationMap.erase(it);
    return it->second;
}

void AnimationManager::removeAll(unsigned int gameObjectID) {
    auto it = _animationMap.begin();
    while(it != _animationMap.end()) {
        it = _animationMap.erase(it);
    }
}


void AnimationManager::push(unsigned int gameObjectID, struct AnimationTimes *at, AnimationCallbacks *ac) {
    _animationMap.insert({ gameObjectID, new Animation(at, ac)});
}


void AnimationManager::fire(float delta) {
    for(auto it = _animationMap.begin(); it != _animationMap.end(); ) {
        Animation *a = it->second;
        a->fire(delta);
        if(a->hasFinished()) {
            delete a;
            it = _animationMap.erase(it);
        } else {
            ++it;
        }
    }
}