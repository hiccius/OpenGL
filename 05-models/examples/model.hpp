#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>
#include <vector>
#include <chrono>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shaderprogram.hpp"
#include "mesh.hpp"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model
{
    public:
        Model(const char *path)
        {
            loadModel(path);
        }
        void Draw(CShaderProgram &shader);
    private:
        // model data
        std::vector<Texture> textures_loaded;
        std::vector<Mesh> meshes;
        std::string directory;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                                  std::string typeName);
};

#endif // MODEL_HPP
