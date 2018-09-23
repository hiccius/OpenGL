#include "texturehandler.h"

#include "helpers.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void CTextureHandler::AddTexture(const std::string& textureLocation, GLenum textureFormat)
{
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLint height, width, numberOfChannels;
    stbi_set_flip_vertically_on_load(true);
    uint8_t* textureData = stbi_load(textureLocation.c_str(), &width, &height, &numberOfChannels, 0);
    if (textureData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(textureData);
        _textureIds.push_back(textureId);
    }
    else
    {
        throw OpenGLException("Error loading texture");
    }
}


void CTextureHandler::ActiveTextures()
{
    GLenum textureUnit = GL_TEXTURE0;

    for (const auto& textureId : _textureIds)
    {
        glActiveTexture(textureUnit++);
        glBindTexture(GL_TEXTURE_2D, textureId);
    }
}