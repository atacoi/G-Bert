#pragma once

#include <map>

#include "shader.h"
#include "texture2d.h"

class ResourceManager {
    public:
        /* ********************************************** */
        /*                Static Fields                   */
        /* ********************************************** */

        static std::map<std::string, Shader*> _shaderMap;
        static std::map<std::string, Texture2D*> _textureMap;

        /* ********************************************** */
        /*               Static Functions                 */
        /* ********************************************** */

        /* ********************************************** */
        /*                GETTERS                         */
        /* ********************************************** */

        static Shader    *getShader  (const std::string &shaderName);
        static Texture2D *getTexture (const std::string &textureName);

        /* ********************************************** */
        /*                SETTERS                         */
        /* ********************************************** */

        static void createShader(const std::string &vertexShaderFileName, 
                                 const std::string &fragmentShaderFileName, 
                                 const std::string &shaderName);
        
        static void createTexture(const std::string &textureFileName, 
                                  const std::string &textureName);

        static void cleanup();
};