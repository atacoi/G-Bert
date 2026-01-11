#include "resource_manager.h"

/* ********************************************** */
/*                Static Fields                   */
/* ********************************************** */

std::map<std::string, Shader*> ResourceManager::_shaderMap;

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

/* ********************************************** */
/*                SETTERS                         */
/* ********************************************** */

void ResourceManager::createShader(const std::string &vertexShaderFilePath, 
                                   const std::string &fragmentShaderFilePath, 
                                   const std::string &shaderName) 
{
    Shader *shader = new Shader(vertexShaderFilePath, fragmentShaderFilePath);
    _shaderMap.insert({shaderName, shader});
}