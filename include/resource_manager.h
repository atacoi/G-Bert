#pragma once

#include <map>
#include "shader.h"

class ResourceManager {
    public:
        /* ********************************************** */
        /*                Static Fields                   */
        /* ********************************************** */

        static std::map<std::string, Shader*> _shaderMap;

        /* ********************************************** */
        /*               Static Functions                 */
        /* ********************************************** */

        /* ********************************************** */
        /*                GETTERS                         */
        /* ********************************************** */

        static Shader *getShader(const std::string &shaderName);

        /* ********************************************** */
        /*                SETTERS                         */
        /* ********************************************** */

        static void createShader(const std::string &vertexShaderFilePath, 
                                 const std::string &fragmentShaderFilePath, 
                                 const std::string &shaderName);
};