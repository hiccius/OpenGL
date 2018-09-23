#pragma once

#include <glad/glad.h>
#include <vector>

class CTextureHandler
{
public:
    void AddTexture(const std::string& textureLocation, GLenum textureFormat);
    void ActiveTextures();

private:
    std::vector<GLuint> _textureIds;
};