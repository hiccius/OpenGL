#include "mesh.hpp"

#include "texture.hpp"
#include "helpers.hpp"
#include "shaderprogram.hpp"
#include "vertexdatahandler.ipp"
#include "vertexbufferobject.ipp"
#include <iostream>

CMesh::CMesh(std::vector<Vertex>&& aVertices, std::vector<unsigned int>&& aIndices, std::vector<CTexture*>&& aTextures)
    : _vertices{aVertices}, _indices{aIndices}, _textures{aTextures}
{
    _vbo.AddVertexData(_vertices);

    _vertexDataHandler.AddVertexBufferObject(&_vbo);
    _vertexDataHandler.AddElementBufferObject(_indices);

    // vertex positions
    _vertexDataHandler.AddAttribute(3, sizeof(Vertex), 0);
    // normals
    _vertexDataHandler.AddAttribute(3, sizeof(Vertex), offsetof(Vertex, normal));
    // texture coordinates
    _vertexDataHandler.AddAttribute(2, sizeof(Vertex), offsetof(Vertex, textureCoordinates));
}

void CMesh::Draw(CShaderProgram& aShaderProgram)
{
    int textureUnit = 0;
    int specularTextureIndex = 1;
    int diffuseTextureIndex = 1;

    for(const auto& texture : _textures)
    {
        std::string uniformName{"material."};
        switch(texture->GetType())
        {
            case CTexture::Type::Specular:
                uniformName += "specular" + std::to_string(specularTextureIndex++);
                break;
            case CTexture::Type::Diffuse:
                uniformName += "diffuse" + std::to_string(diffuseTextureIndex++);
                break;
            default:
                throw OpenGLException("MODEL::TEXTURE", "Unsupported texture type");
        }
        aShaderProgram.SetUniform(uniformName, textureUnit);
        texture->ActivateAndBind(textureUnit++);
    }

    _vertexDataHandler.DrawElements(_indices.size());
}

/*
void CMesh::Draw(CShaderProgram& aShaderProgram)
{
    unsigned int diffuseNr = 1;
    //unsigned int specularNr = 1;
    for(std::size_t i = 0; i < _textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = _textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
        {
            //number = std::to_string(specularNr++);
            continue;
        }

        aShaderProgram.SetUniform(name + number, static_cast<int>(i));
        glBindTexture(GL_TEXTURE_2D, _textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
*/
