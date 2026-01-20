#pragma once

#include <functional>
#include <any>

struct AnimationCallbacks {
    std::function<void()>      startupDelayCallback;
    std::function<void(float)> runningCallback;
    std::function<void()>      cleanupDelayCallback;
    std::function<void()>      cleanupCallback;
};

struct AnimationTimes {
    float startupDelayTime;
    float runningTime;
    float cleanupDelayTime;
};

class Animation {
    public:
        enum ANIMATION_CALLBACK_TYPES {
            STARTUPDELAY,
            RUNNING,
            CLEANUPDELAY,
            CLEANUP,
            NONE
        };

        /* ********************************************** */
        /*                CONSTRUCTORS                    */
        /* ********************************************** */

        Animation(struct AnimationTimes *at = nullptr, struct AnimationCallbacks *callbacks = nullptr);

        /* ********************************************** */
        /*                  GETTERS                       */
        /* ********************************************** */

        bool hasFinished() const;
        ANIMATION_CALLBACK_TYPES getState() const;

        /* ********************************************** */
        /*                  SETTERS                       */
        /* ********************************************** */

        void setCallback(std::function<void()> callback, ANIMATION_CALLBACK_TYPES callBackType);
        void setCallback(std::function<void(float)> callback, ANIMATION_CALLBACK_TYPES callBackType);

        /* ********************************************** */
        /*                  UTILITY                       */
        /* ********************************************** */

        void fire(float delta);

    private:
        std::function<void()> startupDelayCallback;
        std::function<void(float)> runningCallback; // given float is in [0, 1]
        std::function<void()> cleanupDelayCallback;
        std::function<void()> cleanupCallback;

        float stateTime;   // how much time has passed for a given state

        float startDelayTime;   // how much time the animation should wait for before running
        float runningTime;      // how much time the actual animation runs for
        float cleanupDelayTime; // how much time the animation should wait for before cleanup

        ANIMATION_CALLBACK_TYPES state;

        /* ********************************************** */
        /*                  UTILITY                       */
        /* ********************************************** */

        void startupDelay();
        void run(float t);   // t is in [0, 1]
        void cleanupDelay();
        void cleanup();
};