#include "game_object.h"
#include "game.h"
#include "global_constants.h"
#include <math.h>

/* ********************************************** */
/*                CONSTRUCTORS                    */
/* ********************************************** */

GameObject::GameObject(): shader(nullptr), position(glm::vec2(1.0f)), width(100), height(100), rotationAngle(0) {
    ID = STATIC_IDs++;
}

GameObject::GameObject(Shader *shader): shader(shader), position(glm::vec2(1.0f)), width(100), height(100), rotationAngle(0) {
    modelUniformLocation = glGetUniformLocation(shader->getProgramID(), "model");
    ID = STATIC_IDs++;
}

GameObject::GameObject(Shader *shader, glm::vec2 position, GLint width, GLint height): shader(shader), position(position), width(width), height(height), rotationAngle(0) {
    modelUniformLocation = glGetUniformLocation(shader->getProgramID(), "model");
    ID = STATIC_IDs++;
}

/* ********************************************** */
/*                DESTRUCTORS                     */
/* ********************************************** */

GameObject::~GameObject() { }

/* ********************************************** */
/*                  GETTERS                       */
/* ********************************************** */

GLuint GameObject::getID() const { return ID; }

/* ********************************************** */
/*                  Utility                       */
/* ********************************************** */

void GameObject::render(int screenWidth, int screenHeight) {
    if(!shader) {
        std::cerr << "Shader is not defined for game object with ID" << ID << std::endl;
        return;
    }

    shader->use();

    float color[] = {1.0f, 0.0f, 0.0f};
    glUniform3fv(glGetUniformLocation(shader->getProgramID(), "color"), 1, color);

    glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 shear = glm::mat4(1.0f);
    // shear[0][1] = -0.5f;
    model = glm::translate(model, glm::vec3(200.0f, 200.0f, 0.0f));
    // model = glm::translate(model, glm::vec3(0.5f * width, 0.5f * height, 0.0f));
    // model = glm::rotate(model, 3.14f / 4.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    // model = glm::translate(model, glm::vec3(-0.5f * width, -0.5f * height, 0.0f));
            shear[1][0] = -1.0f;
            shear[1][1] = -0.5f;

            shear[0][1] = -0.5f;
    model = model * shear;
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

//     glDrawArrays(GL_TRIANGLES, 0, 6); // assumes that the VAO is bound before each object is rendered 

//     model = glm::mat4(1.0f);
//     model = glm::translate(model, glm::vec3(200.0f, 200.0f, 0.0f));
//     shear[1][0] = 1.0f;
//     model = glm::translate(model, glm::vec3(0.5f * width, 0.5f * height, 0.0f));
//     model = glm::rotate(model, 3.14f / 4.0f, glm::vec3(0.0f, 0.0f, 1.0f));
//     model = glm::translate(model, glm::vec3(-0.5f * width, -0.5f * height, 0.0f));
//     model = model * shear;
//     model = glm::scale(model, glm::vec3(width, height, 1.0f));

//     glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(model));

//     glDrawArrays(GL_TRIANGLES, 0, 6); // assumes that the VAO is bound before each object is rendered

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(200.0f, 200.0f, 0.0f));
    shear = glm::mat4(1.0f);
    shear[0][1] = -0.5f;
    model = model * shear;
    model = glm::scale(model, glm::vec3(width, height, 1.0f));

    glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 6); // assumes that the VAO is bound before each object is rendered

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(200.0f, 200.0f, 0.0f));
    shear = glm::mat4(1.0f);
    shear[0][1] = -0.5f;
    shear[0][0] = -1.0f;
    model = model * shear;
    model = glm::scale(model, glm::vec3(width, height, 1.0f));

    glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 6); // assumes that the VAO is bound before each object is rendered

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(200.0f, 200.0f, 0.0f));
    //model = glm::translate(model, glm::vec3(-0.5f*width, 1.0f*height, 0.0f));
    //model = glm::translate(model, glm::vec3(0.0f, -height/4, 0.0f));
    shear = glm::mat4(1.0f);
    float len = sqrtf(5) / 2.0f;
                shear[1][0] = -1.0f;
            shear[1][1] = -0.5f;

            shear[0][1] = -0.5f;
    float t = sqrt(height * height / 4 + width * width);
    model = glm::translate(model, glm::vec3(0.0f, height, 0.0f));
    model = glm::translate(model, glm::vec3(-t / len, 0.5f * t / len, 0.0f));
    model = model * shear;
    model = glm::scale(model, glm::vec3(width, height, 1.0f));

    glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    color[1] = 1.0f;
    glUniform3fv(glGetUniformLocation(shader->getProgramID(), "color"), 1, color);

    glDrawArrays(GL_TRIANGLES, 0, 6); // assumes that the VAO is bound before each object is rendered
}

void GameObject::translate(glm::vec2 position) { this->position = position; }

void GameObject::rotate(float degree) {
    float radians = degree *  M_PI / 180;
    rotationAngle = radians;
} 