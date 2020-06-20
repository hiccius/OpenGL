#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include "vertexdatahandler.hpp"
#include "vertexbufferobject.hpp"

struct Vertex
{
    const float position[3];
    const float normal[3];
    const float textureCoordinates[2];
};

class CTexture;
class CMesh
{
public:
    CMesh(std::vector<Vertex>&& aVertices, std::vector<unsigned int>&& aIndices, std::vector<CTexture*>&& aTextures);

    void Draw(unsigned int aNumberDiffuseUnits, unsigned int aNumberSpecularUnits) const;

private:
    CVertexBufferObject _vbo;
    CVertexDataHandler  _vertexDataHandler;

    std::vector<Vertex>         _vertices;
    std::vector<unsigned int>   _indices;
    std::vector<CTexture*>      _textures;
};

#endif // MESH_HPP
