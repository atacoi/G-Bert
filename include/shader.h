#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string.h>

class Shader {
    public:
        /* ********************************************** */
        /*                CONSTRUCTORS                    */
        /* ********************************************** */

        Shader(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName);

        /* ********************************************** */
        /*                DESTRUCTORS                     */
        /* ********************************************** */

        ~Shader();

        /* ********************************************** */
        /*                GETTERS                         */
        /* ********************************************** */

        GLuint getProgramID();

        /* ********************************************** */
        /*                UTILITY                         */
        /* ********************************************** */

        void use();

    private:
        GLuint programID;

        /* ********************************************** */
        /*                UTILITY                         */
        /* ********************************************** */

        GLuint createShader(const std::string &shaderSource, GLenum type, bool *failed);

        GLuint createShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID, bool *failed);

        std::string readFileContents(const std::string &shaderFile);
};