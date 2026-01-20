#include "resource_manager.h"

#include <glm/glm.hpp>

/* ********************************************** */
/*                Static Fields                   */
/* ********************************************** */

std::map<std::string, Shader*>    ResourceManager::_shaderMap;
std::map<std::string, Texture2D*> ResourceManager::_textureMap;

/* ********************************************** */
/*               Static Functions                 */
/* ********************************************** */

/* ********************************************** */
/*                GETTERS                         */
/* ********************************************** */

Shader *ResourceManager::getShader(const std::string &shaderName) {
    std::map<std::string, Shader*>::const_iterator pos = _shaderMap.find(shaderName);

    if(pos != _shaderMap.end()) {
        return pos->second;
    } 

    std::cerr << "Could not find the shader under the name" << shaderName << std::endl;
    return nullptr;
}

Texture2D *ResourceManager::getTexture(const std::string &textureName) {
    std::map<std::string, Texture2D*>::const_iterator pos = _textureMap.find(textureName);

    if(pos != _textureMap.end()) {
        return pos->second;
    } 

    std::cerr << "Could not find the texture under the name" << textureName << std::endl;
    return nullptr;
}

/* ********************************************** */
/*                SETTERS                         */
/* ********************************************** */

void ResourceManager::createShader(const std::string &vertexShaderFileName, 
                                   const std::string &fragmentShaderFileName, 
                                   const std::string &shaderName) 
{
    Shader *shader = new Shader(vertexShaderFileName, fragmentShaderFileName);
    _shaderMap.insert({shaderName, shader});
}

void ResourceManager::createTexture(const std::string &textureFileName, 
                   const std::string &textureName)
{
    Texture2D *texture = new Texture2D(textureFileName);
    _textureMap.insert({textureName, texture});
}

void ResourceManager::cleanup() {
    for (auto &shader : _shaderMap) {
        free(shader.second);
    }

    for (auto &texture : _textureMap) {
        free(texture.second);
    }
}