#include <iostream>

#include "window.hpp"
#include "camera.hpp"
#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "model.hpp"
#include "vertexbufferobject.ipp"
#include "shaderprogram.ipp"
#include "uniformbufferobject.ipp"


int main()
{
    constexpr int screenWidth{800};
    constexpr int screenHeight{600};
    constexpr double aspect{static_cast<double>(screenWidth) / screenHeight};

    try
    {
        // Init window
        CWindow window;
        CCamera camera{0.1, 2.5, aspect};
        window.SetUp(screenWidth, screenHeight, "LearnOpenGL", &camera);
        window.SetMouseControl();
        window.SetDepthTest(true);

        // Shader programs
        auto redShader{CShaderProgram::Build("04-shader.vert", "04-red.frag")};
        auto greenShader{CShaderProgram::Build("04-shader.vert", "04-green.frag")};
        auto yellowShader{CShaderProgram::Build("04-shader.vert", "04-yellow.frag")};
        auto blueShader{CShaderProgram::Build("04-shader.vert", "04-blue.frag")};

        redShader.Use();
        redShader.SetUniform("model", CMatrix{}.Translate(-0.75f, 0.75f, 0.0f));
        greenShader.Use();
        greenShader.SetUniform("model", CMatrix{}.Translate(0.75f, 0.75f, 0.0f));
        yellowShader.Use();
        yellowShader.SetUniform("model", CMatrix{}.Translate(-0.75f, -0.75f, 0.0f));
        blueShader.Use();
        blueShader.SetUniform("model", CMatrix{}.Translate(0.75f, -0.75f, 0.0f));

        // Uniform buffer object
        CUniformBufferObject ubo;
        ubo.Allocate(2 * CMatrix::Size());
        ubo.SetBindingPoint(0);

        redShader.SetBindingPoint("Matrices", 0);
        greenShader.SetBindingPoint("Matrices", 0);
        blueShader.SetBindingPoint("Matrices", 0);
        yellowShader.SetBindingPoint("Matrices", 0);

        // Vertex data
        constexpr float cubeVertices[] =
        {
            // positions
            -0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

             0.5f,  0.5f,  0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f,  0.5f
        };
        CVertexBufferObject vboCube;
        vboCube.AddVertexData(cubeVertices);

        CVertexDataHandler cubeData;
        cubeData.AddVertexBufferObject(&vboCube);
        cubeData.AddAttribute(3, 3, 0, false);

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);

            // Render
            window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            ubo.SetData(static_cast<const CMatrix&>(camera.GetViewMatrix()),
                        static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));

            redShader.Use();
            cubeData.DrawArrays(36);
            greenShader.Use();
            cubeData.DrawArrays(36);
            yellowShader.Use();
            cubeData.DrawArrays(36);
            blueShader.Use();
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
