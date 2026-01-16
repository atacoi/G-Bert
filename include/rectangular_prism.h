#pragma once

#include "platform.h"

#include <glm/glm.hpp>

class RectangularPrism : public Platform {
    public:
        /* ********************************************** */
        /*             STATIC VARIABLES                   */
        /* ********************************************** */

        /* ********************************************** */
        /*                DIRECTIONS                      */
        /* ********************************************** */

        static glm::vec2 topBasis;   // j hat pointing upwards
        static glm::vec2 leftBasis;  // pointing to the bottom leftmost cube
        static glm::vec2 rightBasis; // pointing to the bottom rightmost cube

        /* ********************************************** */
        /*                 MATRICES                       */
        /* ********************************************** */

        static glm::mat4 topMatrix;   // for drawing the top of the cube
        static glm::mat4 leftMatrix;  // for drawing the leftmost side of the cube
        static glm::mat4 rightMatrix; // for drawing the rightmost side of the cube

        /* ********************************************** */
        /*                CONSTRUCTORS                    */
        /* ********************************************** */

        // actual width and height of object will be dynamically calculated 
        RectangularPrism(glm::vec2 origin,
                         Shader *shader, 
                         int sideWidth, 
                         int sideLength, 
                         int sideHeight);

        /* ********************************************** */
        /*                GETTERS                         */
        /* ********************************************** */

        const std::vector<glm::vec3> &getTopColors()   const;
        const std::vector<glm::vec3> &getLeftColors()  const;
        const std::vector<glm::vec3> &getRightColors() const;

        int getCompletionCount() const;
        int getCurrentCount()    const;

        int getSideWidth()  const;
        int getSideLength() const;
        int getSideHeight() const;

        virtual glm::vec2 getTopCenter()   const;
        virtual glm::vec2 getLeftCenter()  const;
        virtual glm::vec2 getRightCenter() const;

        int getWidth()        const override;
        int getHeight()       const override;
        glm::vec2 getCenter() const override;

        /* ********************************************** */
        /*                SETTERS                         */
        /* ********************************************** */

        void setTopColors(std::vector<glm::vec3> topColors);
        void setLeftColors(std::vector<glm::vec3> leftColors);
        void setRightColors(std::vector<glm::vec3> rightColors);

        void setCompletionCount(int complecnt);
        void setCurrentCount   (int currcnt);

        void setSideWidth  (int sw);
        void setSideLength (int sl);
        void setSideHeight (int sh);

        /* ********************************************** */
        /*                UTILITY                         */
        /* ********************************************** */

        void render(int screenWidth, int screenHeight) override;
        
        virtual void step(); // Called when G-Bert steps on a block

    private: 
        std::vector<glm::vec3> topColors; // a color for each step onto the block
        std::vector<glm::vec3> leftColors; // could allow for alternative side colors
        std::vector<glm::vec3> rightColors;

        int completionCount; // number of times one has to change the top color to "complete" the space
        int currentCount;    // the number of times steped 

        int sideWidth;
        int sideLength;
        int sideHeight;

        /* ********************************************** */
        /*                UTILITY                         */
        /* ********************************************** */

        bool lenMatchesCompletionCount(std::vector<glm::vec3> colors);
};