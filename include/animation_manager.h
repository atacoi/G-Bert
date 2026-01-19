#pragma once

#include "animation.h"

#include <iostream>
#include <list>
#include <functional>

class AnimationManager {
    public:
        /* ********************************************** */
        /*                Static Fields                   */
        /* ********************************************** */

        static std::list<Animation*> _animationList; // a doubly-linked list

        /* ********************************************** */
        /*               Static Functions                 */
        /* ********************************************** */
        
        /* ********************************************** */
        /*                  UTILITY                       */
        /* ********************************************** */

        static Animation *pop();

        static void push(struct AnimationTimes *at, AnimationCallbacks *ac);

        static void fire(float delta);
};