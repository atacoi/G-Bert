#pragma once

#include "game_object.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube : public GameObject {
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

        Cube();
        Cube(Shader *shader);
        Cube(Shader *shader, glm::vec2 position, GLint sideLen);

        /* ********************************************** */
        /*                Utility                         */
        /* ********************************************** */

        void render(int screenWidth, int screenHeight) override;
        void step(); // Called when G-Bert steps on a block
        glm::vec2 getTopCenter();
        glm::vec2 getLeftCenter();
        glm::vec2 getRightCenter();

    private:
        std::vector<glm::vec3> topColors; // a color for each step onto the block
        glm::vec3 leftColor;
        glm::vec3 rightColor;

        GLuint completionCount; // number of times one has to change the top color to "complete" the space
        GLuint currentCount;    // the number of times steped 

        GLint sideLen;
};