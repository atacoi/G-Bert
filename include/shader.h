#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

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
        /*                UTILITIES                       */
        /* ********************************************** */

        void use();

        void setUniformMatrix4f(glm::mat4 matrix, const std::string& uniformName);
        void setUniform3f      (glm::vec3 vec, const std::string& uniformName);
        void setUniform1i      (int i, const std::string& uniformName);

    private:
        unsigned int programID;

        /* ********************************************** */
        /*                UTILITIES                       */
        /* ********************************************** */

        unsigned int createShader(const std::string &shaderSource, GLenum type, bool *failed);

        unsigned int createShaderProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID, bool *failed);

        std::string readFileContents(const std::string &shaderFile);
};