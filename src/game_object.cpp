#include "game_object.h"
#include "game.h"
#include "global_constants.h"
#include <math.h>

/* ********************************************** */
/*                CONSTRUCTORS                    */
/* ********************************************** */

GameObject::GameObject() {
    shader = nullptr;
    texture = nullptr;
    position = glm::vec2(1.0f);
    width = 100;
    height = 100;
    rotationAngle = 0;
    ID = STATIC_IDs++;
}

GameObject::GameObject(Shader *shader): shader(shader), position(glm::vec2(100.0f, 100.0f)), width(100), height(100), rotationAngle(0) {
    texture = nullptr;
    modelUniformLocation = glGetUniformLocation(shader->getProgramID(), "model");
    ID = STATIC_IDs++;
    shader->use();
    glm::mat4 projection = glm::ortho(
                                        0.0f,
                                        (float)width,
                                        (float)height,
                                        0.0f,
                                        -1.0f,
                                        1.0f
                                     );
    glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "projection"), 1,  GL_FALSE, glm::value_ptr(projection));

}

GameObject::GameObject(Shader *shader, Texture2D *texture, GLint width, GLint height): shader(shader), texture(texture), position(glm::vec2(100.0f, 100.0f)), width(width), height(height), rotationAngle(0) {
    modelUniformLocation = glGetUniformLocation(shader->getProgramID(), "model");
    ID = STATIC_IDs++;
    shader->use();
    glm::mat4 projection = glm::ortho(
                                        0.0f,
                                        (float)width,
                                        (float)height,
                                        0.0f,
                                        -1.0f,
                                        1.0f
                                     );
    glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "projection"), 1,  GL_FALSE, glm::value_ptr(projection));

}

GameObject::GameObject(Shader *shader, glm::vec2 position, GLint width, GLint height): shader(shader), position(position), width(width), height(height), rotationAngle(0) {
    texture = nullptr;
    modelUniformLocation = glGetUniformLocation(shader->getProgramID(), "model");
    ID = STATIC_IDs++;
    shader->use();
    glm::mat4 projection = glm::ortho(
                                        0.0f,
                                        (float)width,
                                        (float)height,
                                        0.0f,
                                        -1.0f,
                                        1.0f
                                     );
    glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "projection"), 1,  GL_FALSE, glm::value_ptr(projection));
}

/* ********************************************** */
/*                DESTRUCTORS                     */
/* ********************************************** */

GameObject::~GameObject() { }

/* ********************************************** */
/*                  GETTERS                       */
/* ********************************************** */

GLuint GameObject::getID() const { return ID; }

Shader *GameObject::getShader() const { return shader; }

glm::vec2 GameObject::getPosition() const { return position; }

GLint GameObject::getWidth() const { return width; }

GLint GameObject::getHeight() const { return height; }

/* ********************************************** */
/*                  SETTERS                       */
/* ********************************************** */

void GameObject::setPosition(glm::vec2 position) {
    this->position = position;
}

/* ********************************************** */
/*                  Utility                       */
/* ********************************************** */

void GameObject::render(int screenWidth, int screenHeight) {
    if(!texture) {
        texture->use();
    }

    if(!shader) {
        std::cerr << "Shader is not defined for game object with ID" << ID << std::endl;
        return;
    }

    shader->use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * width, 0.5f * height, 0.0f));
    model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * width, -0.5f * height, 0.0f));
    model = glm::scale(model, glm::vec3(width, height, 1.0f));

    glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 projection = glm::ortho(
        0.0f,
        (float)screenWidth,
        (float)screenHeight,
        0.0f,
        -1.0f,
        1.0f
    );

    glUniformMatrix4fv(
        glGetUniformLocation(shader->getProgramID(), "projection"),
        1, GL_FALSE, glm::value_ptr(projection)
    );

    glDrawArrays(GL_TRIANGLES, 0, 6); // assumes that the VAO is bound before each object is rendered 
}

void GameObject::translate(glm::vec2 position) { setPosition(position); }

void GameObject::rotate(float degree) {
    float radians = degree *  M_PI / 180;
    rotationAngle = radians;
} 