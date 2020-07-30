#include "mesh.hpp"

#include "texture.hpp"
#include "helpers.hpp"
#include "vertexdatahandler.ipp"
#include "vertexbufferobject.ipp"

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

void CMesh::SetAttribute(unsigned int aComponents, unsigned int aStride, unsigned int aOffset, bool aBytes) noexcept
{
    _vertexDataHandler.AddAttribute(aComponents, aStride, aOffset, aBytes);
}

void CMesh::SetAttributeDivisor(unsigned int aComponents, unsigned int aStride, unsigned int aOffset, unsigned int aDivisor, bool aBytes) noexcept
{
    _vertexDataHandler.AddAttributeDivisor(aComponents, aStride, aOffset, aDivisor, aBytes);
}

void CMesh::Draw(unsigned int aNumberDiffuseUnits, unsigned int aNumberSpecularUnits) const
{
    ActivateTextures(aNumberDiffuseUnits, aNumberSpecularUnits);
    _vertexDataHandler.DrawElements(_indices.size());
}

void CMesh::Draw(unsigned int aNumberDiffuseUnits, unsigned int aNumberSpecularUnits, unsigned int aInstances) const
{
    _vertexDataHandler.BindVAO();
    ActivateTextures(aNumberDiffuseUnits, aNumberSpecularUnits);
    _vertexDataHandler.DrawElements(_indices.size(), aInstances);
}

void CMesh::BindVAO() const noexcept
{
    _vertexDataHandler.BindVAO();
}

void CMesh::ActivateTextures(unsigned int aNumberDiffuseUnits, unsigned int aNumberSpecularUnits) const
{
    unsigned int diffuseIndex = 0;
    unsigned int specularIndex = aNumberDiffuseUnits;

    for(const auto& texture : _textures)
    {
        switch(texture->GetType())
        {
            case CTexture::Type::Diffuse:
                texture->ActivateAndBind(diffuseIndex++);
                break;
            case CTexture::Type::Specular:
                texture->ActivateAndBind(specularIndex++);
                break;
            default:
                throw OpenGLException("MODEL::TEXTURE", "Unsupported texture type");
        }
    }

    if (diffuseIndex > aNumberDiffuseUnits || (specularIndex - aNumberDiffuseUnits) > aNumberSpecularUnits)
    {
        throw OpenGLException("MODEL::TEXTURE", "Wrong number of texture units set");
    }
}
