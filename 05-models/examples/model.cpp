#include "model.hpp"

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "helpers.hpp"
#include <iostream>

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

void CModel::Draw(CShaderProgram& aShaderProgram)
{
    for (auto& mesh : _meshes)
    {
        mesh.Draw(aShaderProgram);
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

CMesh CModel::ProcessMesh(const aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    for(unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex vertex
        {
            {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z},
            {mesh->mNormals[i].x,  mesh->mNormals[i].y,  mesh->mNormals[i].z},
            {mesh->mTextureCoords[0] ? mesh->mTextureCoords[0][i].x : 0.0f,
             mesh->mTextureCoords[0] ? mesh->mTextureCoords[0][i].y : 0.0f}
        };
        vertices.push_back(std::move(vertex));
    }

    std::vector<unsigned int> indices;
    for(unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        const auto& face = mesh->mFaces[i];
        indices.insert(indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
    }

    std::vector<CTexture*> textures;
    if(mesh->mMaterialIndex >= 0)
    {
        const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<CTexture*> diffuseMaps = LoadMaterialTextures(material,
                                             aiTextureType_DIFFUSE, CTexture::Type::Diffuse);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<CTexture*> specularMaps = LoadMaterialTextures(material,
                                              aiTextureType_SPECULAR, CTexture::Type::Specular);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return CMesh{std::move(vertices), std::move(indices), std::move(textures)};
}

std::vector<CTexture*> CModel::LoadMaterialTextures(const aiMaterial* mat, aiTextureType aAssimpType, CTexture::Type aType)
{
    std::vector<CTexture*> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(aAssimpType); i++)
    {
        aiString str;
        mat->GetTexture(aAssimpType, i, &str);

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
