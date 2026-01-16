#include "g_bert.h"

/* ********************************************** */
/*                CONSTRUCTORS                    */
/* ********************************************** */

GBert::GBert(Shader *shader, Texture2D *texture, GLint width, GLint height)
{

}

/* ********************************************** */
/*                  GETTERS                       */
/* ********************************************** */

GameObject *GBert::getCurrentObject() { return currObject; }

void GBert::render(int screenWidth, int screenHeight) {
    Shader *shader = getShader();

    if(!shader) {
        std::cerr << "Shader is not defined for game object with ID" << getID() << std::endl;
        return;
    }

    GameObject::render(screenWidth, screenHeight);
}

/* ********************************************** */
/*                 UTILITIES                      */
/* ********************************************** */

// void GBert::jump(GBert::DIRECTIONS direction, float delta) {
//     if(!currAirTime) {
//         isAirBorne = true;
//     }
//     float norm = delta / totalAirTime;

//     if(norm >= 1) {
//         setOrigin(destination);
//     } else {

//     }
// }