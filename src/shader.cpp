#include "shader.h"
#include "game.h"
#include "global_constants.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

/* ********************************************** */
/*                PUBLIC                          */
/* ********************************************** */

/* ********************************************** */
/*                CONSTRUCTORS                    */
/* ********************************************** */

Shader::Shader(const std::string &vertexShaderFileName, const std::string &fragmenetShaderFileName) {
    std::string vertexSource   = this->readFileContents(vertexShaderFileName);
    std::string fragmentSource = this->readFileContents(fragmenetShaderFileName);

    bool failed(false);

    unsigned int vertexShaderID    = this->createShader(vertexSource,   GL_VERTEX_SHADER,   &failed);
    if(failed) return;

    unsigned int fragmenetShaderID = this->createShader(fragmentSource, GL_FRAGMENT_SHADER, &failed);
    if(failed) return;

    programID = this->createShaderProgram(vertexShaderID, fragmenetShaderID, &failed);
    if(failed) return;

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmenetShaderID);
}

/* ********************************************** */
/*                DESTRUCTORS                     */
/* ********************************************** */

Shader::~Shader() { glDeleteProgram(programID); }

/* ********************************************** */
/*                GETTERS                         */
/* ********************************************** */

GLuint Shader::getProgramID() { return programID; }

/* ********************************************** */
/*                UTILITIES                       */
/* ********************************************** */

void Shader::use() { glUseProgram(programID); }

void Shader::setUniformMatrix4f(glm::mat4 matrix, const std::string& uniformName) {
    unsigned int uniformLocation = glGetUniformLocation(programID, uniformName.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, value_ptr(matrix));
}

void Shader::setUniform3f(glm::vec3 vec, const std::string& uniformName) {
    unsigned int uniformLocation = glGetUniformLocation(programID, uniformName.c_str());
    glUniform3fv(uniformLocation, 1, value_ptr(vec));
}

/* ********************************************** */
/*                PRIVATE                         */
/* ********************************************** */

/* ********************************************** */
/*                UTILITY                         */
/* ********************************************** */

unsigned int Shader::createShader(const std::string &shaderSource, GLenum type, bool *failed) {
    const char *cstr = shaderSource.c_str();

    unsigned int shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &cstr, NULL);
    glCompileShader(shaderID);

    int success;

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(!success) {
        char infoLog[1028];
        glGetShaderInfoLog(shaderID, 1028, NULL, infoLog);
        std::cerr << infoLog << std::endl;
        *failed = true;
    }

    return shaderID;
}

unsigned int Shader::createShaderProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID, bool *failed) {
    unsigned int programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    int success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if(!success) {
        char infoLog[1028];
        glGetProgramInfoLog(programID, 1028, NULL, infoLog);
        std::cerr << infoLog << std::endl;
        *failed = true;
    }

    return programID;
}

std::string Shader::readFileContents(const std::string &shaderFile) {
    std::ifstream fileStream;
    fileStream.exceptions(std::ifstream::badbit | std::fstream::failbit);
    std::string output;

    try {
        fileStream.open(SHADER_FOLDER + shaderFile);

        std::stringstream stringStream;
        stringStream << fileStream.rdbuf();

        fileStream.close();

        output = stringStream.str();
    } catch(std::ifstream::failure error) {
        std::cerr << "Could not read shader file" << std::endl;
    }
    return output;
}