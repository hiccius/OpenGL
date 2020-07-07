#ifndef MODEL_HPP
#define MODEL_HPP

#include <map>
#include <assimp/scene.h>
#include "mesh.hpp"
#include "texture.hpp"
#include "drawable.hpp"

class CShaderProgram;
class CModel : public CDrawable
{
public:
    CModel(const std::filesystem::path& aModelFile);

    void SetTextureUnitsUniforms(CShaderProgram& aShaderProgram);
    virtual void Draw() const override final;

private:
    std::map<std::string, CTexture> _loadedTextures;
    std::vector<CMesh>              _meshes;
    std::filesystem::path           _folder;

    std::size_t    _numberDiffuseUnits{0};
    std::size_t    _numberSpecularUnits{0};

    void  ProcessNode(const aiNode* aNode, const aiScene* aScene);
    CMesh ProcessMesh(const aiMesh* aMesh, const aiScene* aScene);

    std::vector<CTexture*> LoadMaterialTextures(const aiMaterial* aMaterial, aiTextureType aAssimpType,
                                                CTexture::Type aType);
};

#endif // MODEL_HPP
