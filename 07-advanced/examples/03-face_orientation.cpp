#include <iostream>

#include "window.hpp"
#include "camera.hpp"
#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "model.hpp"
#include "vertexbufferobject.ipp"
#include "shaderprogram.ipp"


int main()
{
    constexpr int screenWidth{800};
    constexpr int screenHeight{600};
    constexpr double aspect{static_cast<double>(screenWidth) / screenHeight};

    try
    {
        // Init window
        CWindow window;
        CCamera camera{0.05, 0.5, aspect};
        window.SetUp(screenWidth, screenHeight, "LearnOpenGL", &camera);
        window.SetMouseControl();
        window.SetDepthTest(true);

        // Shader programs
        auto shaderProgram{CShaderProgram::Build("03-shader.vert", "03-shader.frag")};
        shaderProgram.Use();
        shaderProgram.SetUniform("frontTexture", 0);
        shaderProgram.SetUniform("backTexture", 1);

        // Vertex data
        constexpr float cubeVertices[] =
        {
            // positions          // texture coordinates
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f
        };
        CVertexBufferObject vboCube;
        vboCube.AddVertexData(cubeVertices);

        CVertexDataHandler cubeData;
        cubeData.AddVertexBufferObject(&vboCube);
        cubeData.AddAttribute(3, 5, 0, false);
        cubeData.AddAttribute(2, 5, 3, false);

        // Textures
        CTexture grid(CTexture::Type::Diffuse);
        grid.GenerateTexture("grid.jpg");

        CTexture tile(CTexture::Type::Diffuse);
        tile.GenerateTexture("tile.jpg");

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);

            // Render
            window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            shaderProgram.Use();
            shaderProgram.SetUniform("model",       CMatrix{});
            shaderProgram.SetUniform("view",        static_cast<const CMatrix&>(camera.GetViewMatrix()));
            shaderProgram.SetUniform("projection",  static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));


            grid.ActivateAndBind(0);
            tile.ActivateAndBind(1);
            cubeData.DrawArrays(36);

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
