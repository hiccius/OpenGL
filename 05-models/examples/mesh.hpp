#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <glm/glm.hpp>
#include "shaderprogram.hpp"


struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoordinates;
};

struct Texture
{
    unsigned int    id;
    std::string     type;
    std::string     path;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> aVertices, std::vector<unsigned int> aIndices, std::vector<Texture> aTextures)
        : _vertices{aVertices}, _indices{aIndices}, _textures{aTextures}
    {
        SetupMesh();
    }

    void Draw(CShaderProgram& shader);

private:
    void SetupMesh();

    unsigned int VAO, VBO, EBO;

    std::vector<Vertex>         _vertices;
    std::vector<unsigned int>   _indices;
    std::vector<Texture>        _textures;
};






#endif // MESH_HPP
