#include <iostream>
#include <vector>
#include <chrono>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stb_image.h>

#include "shaderprogram.hpp"
#include "window.hpp"
#include "camera.hpp"
#include "helpers.hpp"
#include "model.hpp"


int main()
{
    constexpr int screenHeight{800};
    constexpr int screenWidth{600};
    constexpr double aspect{static_cast<double>(screenHeight) / screenWidth};

    try
    {
        // Init window
        CWindow window;
        CCamera camera{0.1, 2.5, aspect};
        window.SetUp(screenHeight, screenWidth, "LearnOpenGL", true, &camera);
        window.SetMouseControl();

        // Shader programs
        auto shaderProgram{CShaderProgram::Build("shader.vert", "shader.frag")};
        shaderProgram.Use();
        shaderProgram.SetUniform("model", CMatrix{});

        // Vertex data
        auto t1 = std::chrono::high_resolution_clock::now();
        CModel model{"backpack/backpack.obj"};
        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << "Load: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms" << std::endl;

        std::cout << "We are here" << std::endl;
        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);

            // Render
            window.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            shaderProgram.Use();
            shaderProgram.SetUniform("projection",    static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            shaderProgram.SetUniform("view",          static_cast<const CMatrix&>(camera.GetViewMatrix()));

            t1 = std::chrono::high_resolution_clock::now();
            model.Draw(shaderProgram);
            t2 = std::chrono::high_resolution_clock::now();

            std::cout << "Draw: " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " us" << std::endl;

            // Poll events and redraw window
            window.RedrawAndPoll();
        }

        return 0;
    }
    catch (const OpenGLException& exc)
    {
        std::cerr << exc.what() << std::endl;
        return -1;
    }
}
