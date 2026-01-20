#include "rectangular_prism.h"

/* ********************************************** */
/*                PUBLIC                         */
/* ********************************************** */

/* ********************************************** */
/*             STATIC VARIABLES                   */
/* ********************************************** */

/* ********************************************** */
/*                DIRECTIONS                      */
/* ********************************************** */

glm::vec2 RectangularPrism::topBasis   = glm::normalize(glm::vec2(0.0f, -1.0f));  
glm::vec2 RectangularPrism::leftBasis  = glm::normalize(glm::vec2(-1.0f, 0.5f));  
glm::vec2 RectangularPrism::rightBasis = glm::normalize(glm::vec2(1.0f, 0.5f)); 

/* ********************************************** */
/*                 MATRICES                       */
/* ********************************************** */

glm::mat4 RectangularPrism::topMatrix = glm::mat4(
                                            glm::vec4(-RectangularPrism::leftBasis.x, -RectangularPrism::leftBasis.y, 0.0f, 0.0f),
                                            glm::vec4(-RectangularPrism::rightBasis.x, -RectangularPrism::rightBasis.y, 0.0f, 0.0f),
                                            glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
                                            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
                                        );
glm::mat4 RectangularPrism::leftMatrix = glm::mat4(
                                            glm::vec4(-RectangularPrism::rightBasis.x, -RectangularPrism::rightBasis.y, 0.0f, 0.0f),
                                            glm::vec4(-RectangularPrism::topBasis.x, -RectangularPrism::topBasis.y, 0.0f, 0.0f),
                                            glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
                                            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
                                        );  
glm::mat4 RectangularPrism::rightMatrix = glm::mat4(
                                            glm::vec4(-RectangularPrism::leftBasis.x, -RectangularPrism::leftBasis.y, 0.0f, 0.0f),
                                            glm::vec4(-RectangularPrism::topBasis.x, -RectangularPrism::topBasis.y, 0.0f, 0.0f),
                                            glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
                                            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
                                        );

/* ********************************************** */
/*                CONSTRUCTORS                    */
/* ********************************************** */

// actual width and height of object will be dynamically calculated 
RectangularPrism::RectangularPrism (glm::vec2 origin,
                                    Shader *shader, 
                                    int sideWidth, 
                                    int sideLength, 
                                    int sideHeight):
                                    Platform::Platform(origin, shader) 
{
    setSideWidth(sideWidth);
    setSideLength(sideLength);
    setSideHeight(sideHeight);

    setCompletionCount(1);

    std::vector<glm::vec3> topColors   = {glm::vec3(80.0f / 255.0f, 64.0f / 255.0f, 239.0f / 255.0f), 
                                          glm::vec3(223.0f / 255.0f, 223.0f / 255.0f, 0.0f)};

    std::vector<glm::vec3> leftColors  = {glm::vec3(80.0f / 255.0f, 175.0f / 255.0f, 159.0f / 255.0f), 
                                          glm::vec3(80.0f / 255.0f, 175.0f / 255.0f, 159.0f / 255.0f)};

    std::vector<glm::vec3> rightColors = {glm::vec3(48.0f / 255.0f, 64.0f / 255.0f, 64.0f / 255.0f),
                                          glm::vec3(48.0f / 255.0f, 64.0f / 255.0f, 64.0f / 255.0f)};

    setTopColors(topColors);
    setLeftColors(leftColors);
    setRightColors(rightColors);

    setWidth(getWidth());
    setHeight(getHeight());
}

/* ********************************************** */
/*                GETTERS                         */
/* ********************************************** */

const std::vector<glm::vec3> &RectangularPrism::getTopColors()   const { return topColors;   }
const std::vector<glm::vec3> &RectangularPrism::getLeftColors()  const { return leftColors;  }
const std::vector<glm::vec3> &RectangularPrism::getRightColors() const { return rightColors; }

int RectangularPrism::getCompletionCount() const { return completionCount; } 
int RectangularPrism::getCurrentCount()    const { return currentCount;    }

int RectangularPrism::getSideWidth()  const { return sideWidth;  }
int RectangularPrism::getSideLength() const { return sideLength; }
int RectangularPrism::getSideHeight() const { return sideHeight; }

glm::vec2 RectangularPrism::getTopCenter() const {
    glm::vec2 origin = getOrigin();
    glm::vec2 center = origin - (sideLength / 2.0f * rightBasis) - (sideWidth / 2.0f * leftBasis); 
    return center;
}

glm::vec2 RectangularPrism::getLeftCenter() const {
    glm::vec2 origin = getOrigin();
    glm::vec2 center = origin - (sideLength / 2.0f * rightBasis) - (sideHeight / 2.0f * topBasis); 
    return center;
}

glm::vec2 RectangularPrism::getRightCenter() const {
    glm::vec2 origin = getOrigin();
    glm::vec2 center = origin - (sideWidth / 2.0f * leftBasis) - (sideHeight / 2.0f * topBasis); 
    return center;
}

int RectangularPrism::getWidth() const {
    glm::vec2 bottomHeight = topBasis * (float) sideHeight;
    glm::vec2 topHeight    = -leftBasis * (float) sideWidth - rightBasis * (float) sideLength;

    return (int) glm::length(glm::vec2(bottomHeight + topHeight));
}

int RectangularPrism::getHeight() const {
    glm::vec2 leftWidth = rightBasis * (float) sideLength;
    glm::vec2 rightWidth = -leftBasis * (float) sideWidth;

    return (int) glm::length(glm::vec2(leftWidth + rightWidth));
}

glm::vec2 RectangularPrism::getCenter() const { return getTopCenter(); }

/* ********************************************** */
/*                SETTERS                         */
/* ********************************************** */

void RectangularPrism::setTopColors(std::vector<glm::vec3> topColors) {
    if(!lenMatchesCompletionCount(topColors)) { 
        std::cerr << "Top Colors do not match completion count of " << completionCount << std::endl;
        return;
    }

    this->topColors = topColors;
}

void RectangularPrism::setLeftColors(std::vector<glm::vec3> leftColors) {
    if(!lenMatchesCompletionCount(leftColors)) { 
        std::cerr << "Left Colors do not match completion count of " << completionCount << std::endl;
        return;
    }

    this->leftColors = leftColors;
}

void RectangularPrism::setRightColors(std::vector<glm::vec3> rightColors) {
    if(!lenMatchesCompletionCount(rightColors)) { 
        std::cerr << "Right Colors do not match completion count of " << completionCount << std::endl;
        return;
    }

    this->rightColors = rightColors;
}

void RectangularPrism::setCompletionCount(int complecnt) { 
    if(complecnt < 0) { 
        std::cerr << "Completion count must be a non-negative integer" << std::endl;
        return;
    }

    completionCount = complecnt;
    setCurrentCount(0);
}
void RectangularPrism::setCurrentCount(int currcnt) {
    if(currcnt < 0) { 
        std::cerr << "Current count must be a non-negative integer" << std::endl;
        return;
    }

    currentCount = currcnt;
}

void RectangularPrism::setSideWidth(int sw) {
    if(sw < 0) { 
        std::cerr << "Side width must be a non-negative integer" << std::endl;
        return;
    }

    sideWidth = sw;
}

void RectangularPrism::setSideLength (int sl) {
    if(sl < 0) { 
        std::cerr << "Side length must be a non-negative integer" << std::endl;
        return;
    }

    sideLength = sl;
}

void RectangularPrism::setSideHeight (int sh) {
    if(sh < 0) { 
        std::cerr << "Side height must be a non-negative integer" << std::endl;
        return;
    }

    sideHeight = sh;
}

/* ********************************************** */
/*                UTILITY                         */
/* ********************************************** */

void RectangularPrism::render(int screenWidth, int screenHeight) {
    Shader *shader = getShader();

    if(!shader) {
        std::cerr << "Shader is not defined for game object with ID" << getID() << std::endl;
        return;
    }

    shader->use();

    glm::vec2 origin = getOrigin();

    glm::mat4 projection = glm::ortho(
                                        0.0f,
                                        (float)screenWidth,
                                        (float)screenHeight,
                                        0.0f,
                                        -1.0f,
                                        1.0f
                                     );

    shader->setUniformMatrix4f(projection, "projection");

    /* ********************************************** */
    /*                TOP                             */
    /* ********************************************** */

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(origin, 0.0f));
    model = model * topMatrix;
    model = glm::scale(model, glm::vec3(sideWidth, sideLength, 1.0f));

    shader->setUniformMatrix4f(model, "model");

    shader->setUniform3f(topColors[currentCount], "color");
    
    glDrawArrays(GL_TRIANGLES, 0, 6); // assumes that the VAO is bound before each object is rendered and projection is set

    /* ********************************************** */
    /*                LEFT                            */
    /* ********************************************** */

    model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(origin, 0.0f));
    model = model * leftMatrix;
    model = glm::scale(model, glm::vec3(sideLength, sideHeight, 1.0f));

    shader->setUniformMatrix4f(model, "model");

    shader->setUniform3f(leftColors[currentCount], "color");

    glDrawArrays(GL_TRIANGLES, 0, 6);

    /* ********************************************** */
    /*                RIGHT                           */
    /* ********************************************** */

    model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(origin, 0.0f));
    model = model * rightMatrix;
    model = glm::scale(model, glm::vec3(sideWidth, sideHeight, 1.0f));

    shader->setUniformMatrix4f(model, "model");

    shader->setUniform3f(rightColors[currentCount], "color");

    glDrawArrays(GL_TRIANGLES, 0, 6);

    // model = glm::mat4(1.0f);

    // model = glm::translate(model, glm::vec3(getTopCenter(), 0.0f));
    // model = glm::scale(model, glm::vec3(sideLen, sideLen, 1.0f));

    // glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(model));

    // glUniform3fv(glGetUniformLocation(shader->getProgramID(), "color"), 1, glm::value_ptr(rightColor));

    // glDrawArrays(GL_TRIANGLES, 0, 6);
}

void RectangularPrism::step() {
    if(currentCount >= completionCount) return;
    currentCount += 1; 
}


/* ********************************************** */
/*                PRIVATE                         */
/* ********************************************** */

/* ********************************************** */
/*                UTILITY                         */
/* ********************************************** */

bool RectangularPrism::lenMatchesCompletionCount(std::vector<glm::vec3> &colors) { return colors.size() - 1 == completionCount; }