#include "cube.h"

/* ********************************************** */
/*             STATIC VARIABLES                   */
/* ********************************************** */

glm::vec2 Cube::topBasis   = glm::normalize(glm::vec2(0.0f, -1.0f));  
glm::vec2 Cube::leftBasis  = glm::normalize(glm::vec2(-1.0f, 0.5f));  
glm::vec2 Cube::rightBasis = glm::normalize(glm::vec2(1.0f, 0.5f)); 

glm::mat4 Cube::topMatrix = glm::mat4(
                                glm::vec4(-Cube::leftBasis.x, -Cube::leftBasis.y, 0.0f, 0.0f),
                                glm::vec4(-Cube::rightBasis.x, -Cube::rightBasis.y, 0.0f, 0.0f),
                                glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
                                glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
                            );
glm::mat4 Cube::leftMatrix = glm::mat4(
                                glm::vec4(-Cube::rightBasis.x, -Cube::rightBasis.y, 0.0f, 0.0f),
                                glm::vec4(Cube::topBasis.x, -Cube::topBasis.y, 0.0f, 0.0f),
                                glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
                                glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
                              );  
glm::mat4 Cube::rightMatrix = glm::mat4(
                                glm::vec4(-Cube::leftBasis.x, -Cube::leftBasis.y, 0.0f, 0.0f),
                                glm::vec4(Cube::topBasis.x, -Cube::topBasis.y, 0.0f, 0.0f),
                                glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
                                glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
                              );  

/* ********************************************** */
/*                CONSTRUCTORS                    */
/* ********************************************** */

Cube::Cube(): GameObject::GameObject() {
    topColors = {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)};
    leftColor = glm::vec3(0.0f, 1.0f, 0.0f);
    rightColor =  glm::vec3(0.0f, 0.0f, 1.0f);

    completionCount = 1; 
    currentCount = 0;  

    sideLen = 100;
}

Cube::Cube(Shader *s): GameObject::GameObject(s) {
    topColors = {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)};
    leftColor = glm::vec3(0.0f, 1.0f, 0.0f);
    rightColor =  glm::vec3(0.0f, 0.0f, 1.0f);

    completionCount = 1; 
    currentCount = 0;  

    sideLen = 100;
}

Cube::Cube(Shader *shader, glm::vec2 position, GLint sideLen): GameObject::GameObject(shader, position, sideLen, sideLen) {
    topColors = {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)};
    leftColor = glm::vec3(0.0f, 1.0f, 0.0f);
    rightColor =  glm::vec3(0.0f, 0.0f, 1.0f);

    completionCount = 1; 
    currentCount = 0;  

    this->sideLen = sideLen;
}

/* ********************************************** */
/*                Utility                         */
/* ********************************************** */

void Cube::render(int screenWidth, int screenHeight) {
    /* ********************************************** */
    /*                TOP                             */
    /* ********************************************** */

    Shader *shader = getShader();

    if(!shader) {
        std::cerr << "Shader is not defined for game object with ID" << getID() << std::endl;
        return;
    }

    shader->use();

    glm::vec2 pos = getPosition();

    glm::mat4 projection = glm::ortho(
                                        0.0f,
                                        (float)screenWidth,
                                        (float)screenHeight,
                                        0.0f,
                                        -1.0f,
                                        1.0f
                                     );
    glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(pos, 0.0f));
    model = glm::scale(model, glm::vec3(sideLen, sideLen, 1.0f));
    model = model * topMatrix;

    glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(model));

    glUniform3fv(glGetUniformLocation(shader->getProgramID(), "color"), 1, glm::value_ptr(topColors[currentCount]));
    
    glDrawArrays(GL_TRIANGLES, 0, 6); // assumes that the VAO is bound before each object is rendered and projection is set

    /* ********************************************** */
    /*                LEFT                            */
    /* ********************************************** */

    model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(pos, 0.0f));
    model = glm::scale(model, glm::vec3(sideLen, sideLen, 1.0f));
    model = model * leftMatrix;

    glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(model));

    glUniform3fv(glGetUniformLocation(shader->getProgramID(), "color"), 1, glm::value_ptr(leftColor));

    glDrawArrays(GL_TRIANGLES, 0, 6);

    /* ********************************************** */
    /*                RIGHT                           */
    /* ********************************************** */

    model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(pos, 0.0f));
    model = glm::scale(model, glm::vec3(sideLen, sideLen, 1.0f));
    model = model * rightMatrix;

    glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(model));

    glUniform3fv(glGetUniformLocation(shader->getProgramID(), "color"), 1, glm::value_ptr(rightColor));

    glDrawArrays(GL_TRIANGLES, 0, 6);

    // model = glm::mat4(1.0f);

    // model = glm::translate(model, glm::vec3(getTopCenter(), 0.0f));
    // model = glm::scale(model, glm::vec3(sideLen, sideLen, 1.0f));

    // glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(model));

    // glUniform3fv(glGetUniformLocation(shader->getProgramID(), "color"), 1, glm::value_ptr(rightColor));

    // glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Cube::step() { 
    // if(currentCount >= completionCount) return;
    //currentCount += 1; 
    currentCount = (currentCount + 1) % topColors.size();
}

glm::vec2 Cube::getTopCenter() {
    glm::vec2 position = getPosition();
    glm::vec2 center = position - (sideLen / 2.0f * rightBasis) - (sideLen / 2.0f * leftBasis); 
    return center;
}

glm::vec2 Cube::getLeftCenter() {
    glm::vec2 position = getPosition();
    glm::vec2 center = position - (sideLen / 2.0f * rightBasis) - (sideLen / 2.0f * topBasis); 
    return center;
}

glm::vec2 Cube::getRightCenter() {
    glm::vec2 position = getPosition();
    glm::vec2 center = position - (sideLen / 2.0f * leftBasis) - (sideLen / 2.0f * topBasis); 
    return center;
}