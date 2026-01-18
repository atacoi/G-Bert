#include "animation.h"
#include "global_constants.h"

#include <math.h>
#include <iostream>

/* ********************************************** */
/*                   PUBLIC                       */
/* ********************************************** */

/* ********************************************** */
/*                CONSTRUCTORS                    */
/* ********************************************** */

// pause for 8 frames
Animation::Animation(struct AnimationTimes *at, struct AnimationCallbacks *callbacks) {

    if(at) {
        this->startDelayTime   = at->startupDelayTime;
        this->runningTime      = at->runningTime;     
        this->cleanupDelayTime = at->cleanupDelayTime;
    }

    this->state = ANIMATION_CALLBACK_TYPES::NONE;

    if(callbacks) {
        setCallback(callbacks->startupDelayCallback, ANIMATION_CALLBACK_TYPES::STARTUPDELAY);
        setCallback(callbacks->runningCallback, ANIMATION_CALLBACK_TYPES::RUNNING);
        setCallback(callbacks->cleanupDelayCallback, ANIMATION_CALLBACK_TYPES::CLEANUPDELAY);
        setCallback(callbacks->cleanupCallback, ANIMATION_CALLBACK_TYPES::CLEANUP);
    }
}

/* ********************************************** */
/*                  GETTERS                       */
/* ********************************************** */

bool Animation::hasFinished() const { return state == ANIMATION_CALLBACK_TYPES::CLEANUP; }

Animation::ANIMATION_CALLBACK_TYPES Animation::getState() const { return state; }

/* ********************************************** */
/*                  SETTERS                       */
/* ********************************************** */

void Animation::setCallback(std::function<void()> callback, Animation::ANIMATION_CALLBACK_TYPES callBackType) {
    switch(callBackType) {
        case ANIMATION_CALLBACK_TYPES::STARTUPDELAY:
            startupDelayCallback = callback;
            break;

        case ANIMATION_CALLBACK_TYPES::RUNNING:
            std::cerr << "Callback must be of type std::function<void()>" << std::endl;
            break;

        case ANIMATION_CALLBACK_TYPES::CLEANUPDELAY:
            cleanupDelayCallback = callback;
            break;

        case ANIMATION_CALLBACK_TYPES::CLEANUP:
            cleanupCallback = callback;
            break;

        default: 
            break;
    }
}

void Animation::setCallback(std::function<void(float)> callback, Animation::ANIMATION_CALLBACK_TYPES callBackType) {
    switch(callBackType) {
        case ANIMATION_CALLBACK_TYPES::RUNNING:
            runningCallback = callback;
            break;

        default:
            std::cerr << "Callback must be of type std::function<void(float)>" << std::endl;
            break;
    }
}

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

void Animation::fire(float delta) {
    ANIMATION_CALLBACK_TYPES prevState = state;

    switch(state) {
        case ANIMATION_CALLBACK_TYPES::NONE:
            if(startupDelayCallback) {
                state = ANIMATION_CALLBACK_TYPES::STARTUPDELAY;
                break;
            }

        case ANIMATION_CALLBACK_TYPES::STARTUPDELAY:
            if(runningCallback) {
                if(stateTime >= startDelayTime) {
                    state = ANIMATION_CALLBACK_TYPES::RUNNING;
                }
                break;
            }

        case ANIMATION_CALLBACK_TYPES::RUNNING:
            if(cleanupDelayCallback) {
                if(stateTime >= runningTime) {
                    state = ANIMATION_CALLBACK_TYPES::CLEANUPDELAY;
                }
                break;
            }

        case ANIMATION_CALLBACK_TYPES::CLEANUPDELAY:
            if(cleanupCallback) {
                if(stateTime >= cleanupDelayTime) {
                    state = ANIMATION_CALLBACK_TYPES::CLEANUP;
                }
                break;
            }
        
        default:
            break;
    }

    // execute only once
    if(state != prevState) {
        stateTime = 0.0f;

        switch(state) {
            case ANIMATION_CALLBACK_TYPES::STARTUPDELAY:
                startupDelayCallback();
                break;

            case ANIMATION_CALLBACK_TYPES::CLEANUPDELAY:
                cleanupDelayCallback();
                break;

            case ANIMATION_CALLBACK_TYPES::CLEANUP:
                cleanupCallback();
                break;

            default: 
                break;
        }
    }

    if(state == ANIMATION_CALLBACK_TYPES::RUNNING) {
        runningCallback(stateTime / runningTime);
    }

    stateTime += delta;
}

/* ********************************************** */
/*                  PRIVATE                       */
/* ********************************************** */

/* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

void Animation::startupDelay() {
    if(startupDelayCallback)
        startupDelayCallback();
    else
        std::cerr << "startup delay not bounded" << std::endl;
}

void Animation::run(float t) {
    if(runningCallback)
        runningCallback(std::min(t, 1.0f));
    else
        std::cerr << "callback not bounded" << std::endl;
}

void Animation::cleanupDelay() {
    std::cout << "f" << std::endl;
    if(cleanupDelayCallback)
        cleanupDelayCallback();
    else
        std::cerr << "cleanup delay not bounded" << std::endl;
}

void Animation::cleanup() {
    if(cleanupCallback)
        cleanupCallback();
    else
        std::cerr << "cleanup not bounded" << std::endl;
}