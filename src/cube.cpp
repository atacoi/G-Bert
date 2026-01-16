#include "cube.h"

/* ********************************************** */
/*                CONSTRUCTORS                    */
/* ********************************************** */

Cube::Cube(glm::vec2 origin,
           Shader *shader,
           int sideLen):
           RectangularPrism::RectangularPrism(origin, shader, sideLen, sideLen, sideLen)
{

}

// GameObject *Board::getChildGameObject(GameObject *currObject, TREE_DIRECTION_TYPE tdt) {
//     if(numObjects == 0) return nullptr;

//     GLuint index = currObject->getID() - board[0][0]->getID();

//     if(index >= numObjects) {
//         std::cerr << "index:" << index << "is out of range" << std::endl;
//         return nullptr; 
//     }

//     if(tdt != TREE_DIRECTION_TYPE::LEFT && tdt != TREE_DIRECTION_TYPE::RIGHT) {
//         std::cerr << "Child type:" << tdt << "not recognized" << std::endl;
//         return nullptr;
//     }

//     GLuint level = std::floor(std::sqrt(2.0f * index + 1.0f / 4.0f) - 1.0f / 2.0f) + 1;
//     GLuint prevLevel = level - 1;
//     GLuint nextLevel = level + 1; // 1 indexed 
//     GLuint col = index - (prevLevel) * (prevLevel + 1) / 2.0f;

//     // out of bounds
//     if(nextLevel * (nextLevel + 1) / 2 > numObjects) return nullptr;

//     // always one extra cube on the next level preventing index out of bounds
//     return tdt == TREE_DIRECTION_TYPE::LEFT ? board[nextLevel - 1][col] : board[nextLevel - 1][col+1]; 
// }

// GameObject *Board::getParentGameObject(GameObject *currObject, TREE_DIRECTION_TYPE tdt) {
//     if(numObjects == 0) return nullptr;

//     GLuint index = currObject->getID() - board[0][0]->getID();

//     if(index >= numObjects) {
//         std::cerr << "index:" << index << "is out of range" << std::endl;
//         return nullptr; 
//     }

//     if(tdt != TREE_DIRECTION_TYPE::LEFT && tdt != TREE_DIRECTION_TYPE::RIGHT) {
//         std::cerr << "Parent type:" << tdt << "not recognized" << std::endl;
//         return nullptr;
//     }

//     GLuint level = std::floor(std::sqrt(2.0f * index + 1.0f / 4.0f) - 1.0f / 2.0f) + 1;
//     GLuint prevLevel = level - 1;
//     GLuint col = index - (prevLevel) * (prevLevel + 1) / 2.0f;

//     if(prevLevel == 0 || 
//        (tdt == TREE_DIRECTION_TYPE::LEFT && col == 0) ||
//        (tdt == TREE_DIRECTION_TYPE::RIGHT && col == level - 1)) return nullptr;

//     return tdt == TREE_DIRECTION_TYPE::LEFT ? board[prevLevel - 1][col - 1] : board[prevLevel - 1][col]; 
// }