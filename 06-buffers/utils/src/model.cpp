#include "model.hpp"

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "helpers.hpp"
#include "shaderprogram.ipp"

CModel::CModel(const std::filesystem::path& aModelFile)
    : _folder{aModelFile.parent_path()}
{
    auto resourceFilePath = GetFullPath("resources" / aModelFile);

    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(resourceFilePath.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        throw OpenGLException{"ASSIMP", import.GetErrorString()};
    }

    ProcessNode(scene->mRootNode, scene);
}

void CModel::SetTextureUnitsUniforms(CShaderProgram& aShaderProgram)
{
    int textureUnit{0};
    std::string uniformName{"material."};

    for (std::size_t i = 1; i <= _numberDiffuseUnits; ++i)
    {
        aShaderProgram.SetUniform("material.diffuse" + std::to_string(i), textureUnit++);
    }

    for (std::size_t i = 1; i <= _numberSpecularUnits; ++i)
    {
        aShaderProgram.SetUniform("material.specular" + std::to_string(i), textureUnit++);
    }
}

void CModel::Draw() const
{
    for (const auto& mesh : _meshes)
    {
        mesh.Draw(_numberDiffuseUnits, _numberSpecularUnits);
    }
}

void CModel::ProcessNode(const aiNode* aNode, const aiScene* aScene)
{
    for(unsigned int i = 0; i < aNode->mNumMeshes; ++i)
    {
        const aiMesh* mesh = aScene->mMeshes[aNode->mMeshes[i]];
        _meshes.push_back(ProcessMesh(mesh, aScene));
    }

    for(unsigned int i = 0; i < aNode->mNumChildren; ++i)
    {
        ProcessNode(aNode->mChildren[i], aScene);
    }
}

CMesh CModel::ProcessMesh(const aiMesh* aMesh, const aiScene* aScene)
{
    std::vector<Vertex> vertices;
    for(unsigned int i = 0; i < aMesh->mNumVertices; ++i)
    {
        Vertex vertex
        {
            {aMesh->mVertices[i].x, aMesh->mVertices[i].y, aMesh->mVertices[i].z},
            {aMesh->mNormals[i].x,  aMesh->mNormals[i].y,  aMesh->mNormals[i].z},
            {aMesh->mTextureCoords[0] ? aMesh->mTextureCoords[0][i].x : 0.0f,
             aMesh->mTextureCoords[0] ? aMesh->mTextureCoords[0][i].y : 0.0f}
        };
        vertices.push_back(std::move(vertex));
    }

    std::vector<unsigned int> indices;
    for(unsigned int i = 0; i < aMesh->mNumFaces; ++i)
    {
        const auto& face = aMesh->mFaces[i];
        indices.insert(indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
    }

    std::vector<CTexture*> textures;
    if(aMesh->mMaterialIndex >= 0)
    {
        const aiMaterial* material = aScene->mMaterials[aMesh->mMaterialIndex];

        std::vector<CTexture*> diffuseMaps = LoadMaterialTextures(material,
                                             aiTextureType_DIFFUSE, CTexture::Type::Diffuse);
        _numberDiffuseUnits = std::max(_numberDiffuseUnits, diffuseMaps.size());
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<CTexture*> specularMaps = LoadMaterialTextures(material,
                                              aiTextureType_SPECULAR, CTexture::Type::Specular);
        _numberSpecularUnits = std::max(_numberSpecularUnits, specularMaps.size());
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return CMesh{std::move(vertices), std::move(indices), std::move(textures)};
}

std::vector<CTexture*> CModel::LoadMaterialTextures(const aiMaterial* aMaterial, aiTextureType aAssimpType, CTexture::Type aType)
{
    std::vector<CTexture*> textures;
    for(unsigned int i = 0; i < aMaterial->GetTextureCount(aAssimpType); i++)
    {
        aiString str;
        aMaterial->GetTexture(aAssimpType, i, &str);

        auto textureLoaded = _loadedTextures.find(str.C_Str());
        if (textureLoaded == _loadedTextures.end())
        {
            CTexture texture{aType};
            auto texturePath{_folder / std::filesystem::path{str.C_Str()}};
            texture.GenerateTexture(texturePath);
            textureLoaded = _loadedTextures.emplace(str.C_Str(), std::move(texture)).first;
        }
        textures.push_back(&textureLoaded->second);
    }
    return textures;
}
