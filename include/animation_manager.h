#pragma once

#include "animation.h"

#include <iostream>
#include <list>
#include <functional>

class AnimationManager {
    public:
        /* ********************************************** */
        /*                CONSTRUCTORS                    */
        /* ********************************************** */

        AnimationManager();
        
        /* ********************************************** */
        /*                  UTILITY                       */
        /* ********************************************** */

        Animation *pop();

        void push(struct AnimationTimes *at, AnimationCallbacks *ac);

        void fire(float delta);

    private:
        std::list<Animation*> animationList; // a doubly-linked list
};