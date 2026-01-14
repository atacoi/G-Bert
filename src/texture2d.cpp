#include "texture2d.h"
#include "global_constants.h"

#include <stb_image.h>

/* ********************************************** */
/*                CONSTRUCTORS                    */
/* ********************************************** */

Texture2D::Texture2D(std::string imageFile) {
    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    const char *imagePath = (std::string(TEXTURE_FOLDER) + imageFile).c_str();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(imagePath, 
                                    &width,
                                    &height,
                                    &nrChannels,
                                    0);

    GLenum format = GL_RGB;
    if (nrChannels == 4)
        format = GL_RGBA;

    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 
                     0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture at file path" << imagePath << std::endl;
    }
    stbi_image_free(data);
    textureID = texID;
}

 /* ********************************************** */
/*                  UTILITY                       */
/* ********************************************** */

void Texture2D::use() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}