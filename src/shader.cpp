#include "shader.h"
#include "game.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include "global_constants.h"

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

    GLuint vertexShaderID    = this->createShader(vertexSource,   GL_VERTEX_SHADER,   &failed);
    if(failed) return;

    GLuint fragmenetShaderID = this->createShader(fragmentSource, GL_FRAGMENT_SHADER, &failed);
    if(failed) return;

    programID = this->createShaderProgram(vertexShaderID, fragmenetShaderID, &failed);
    if(failed) return;

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmenetShaderID);
}

/* ********************************************** */
/*                UTILITY                         */
/* ********************************************** */

void Shader::use() { glUseProgram(programID); }

/* ********************************************** */
/*                DESTRUCTORS                     */
/* ********************************************** */

Shader::~Shader() { glDeleteProgram(programID); }

/* ********************************************** */
/*                GETTERS                         */
/* ********************************************** */

GLuint Shader::getProgramID() { return programID; }

/* ********************************************** */
/*                PRIVATE                         */
/* ********************************************** */

/* ********************************************** */
/*                UTILITY                         */
/* ********************************************** */

GLuint Shader::createShader(const std::string &shaderSource, GLenum type, bool *failed) {
    const char *cstr = shaderSource.c_str();

    GLuint shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &cstr, NULL);
    glCompileShader(shaderID);

    GLint success;

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(!success) {
        char infoLog[1028];
        glGetShaderInfoLog(shaderID, 1028, NULL, infoLog);
        std::cerr << infoLog << std::endl;
        *failed = true;
    }

    return shaderID;
}

GLuint Shader::createShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID, bool *failed) {
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    GLint success;
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