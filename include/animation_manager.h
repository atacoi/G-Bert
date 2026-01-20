#pragma once

#include "animation.h"
#include "game_object.h"

#include <iostream>
#include <map>
#include <functional>

class AnimationManager {
    public:
        /* ********************************************** */
        /*                Static Fields                   */
        /* ********************************************** */

        static std::map<unsigned int, Animation*> _animationMap; // gameobject ID to the animation that is binded to it

        /* ********************************************** */
        /*               Static Functions                 */
        /* ********************************************** */
        
        /* ********************************************** */
        /*                  UTILITY                       */
        /* ********************************************** */

        static Animation *remove(unsigned int gameObjectID);
        static void removeAll(unsigned int gameObjectID);

        static void push(unsigned int gameObjectID, struct AnimationTimes *at, AnimationCallbacks *ac);

        static void fire(float delta);
};