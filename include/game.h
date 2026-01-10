#pragma once

enum GAME_STATES {
    ACTIVE,
    TERMINATED,
    len
};

class Game {
    public:
        /* ********************************************** */
        /*                CONSTRUCTORS                    */
        /* ********************************************** */

        Game();
        Game(int width, int height, char *title);

        /* ********************************************** */
        /*                DESTRUCTORS                     */
        /* ********************************************** */

        ~Game();

        /* ********************************************** */
        /*                GETTERS                         */
        /* ********************************************** */

        int getScreenWidth();
        int getScreenHeight();
        char *getTitle();
        GAME_STATES getCurrState();

        /* ********************************************** */
        /*                SETTERS                         */
        /* ********************************************** */

        void setScreenWidth(int width);
        void setScreenHeight(int height);
        void setTitle(char *title);
        void setCurrState(GAME_STATES state);

        /* ********************************************** */
        /*                UTILITY                         */
        /* ********************************************** */

        bool isRunning();

    private:
        int screenWidth;
        int screenHeight;
        char *screenTitle;
        GAME_STATES currState;
};