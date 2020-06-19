#ifndef MODEL_HPP
#define MODEL_HPP

#include <string_view>
#include <map>
#include <assimp/scene.h>
#include "mesh.hpp"
#include "texture.hpp"

class CShaderProgram;

class CModel
{
public:
    CModel(const std::filesystem::path& aModelFile);

    void Draw(CShaderProgram& aShaderProgram);

private:
    std::map<std::string, CTexture> _loadedTextures;
    std::vector<CMesh>              _meshes;
    std::filesystem::path           _folder;

    void  ProcessNode(const aiNode* node, const aiScene* scene);
    CMesh ProcessMesh(const aiMesh* mesh, const aiScene* scene);

    std::vector<CTexture*> LoadMaterialTextures(const aiMaterial* material, aiTextureType aAssimpType,
                                                CTexture::Type aType);
};

#endif // MODEL_HPP
