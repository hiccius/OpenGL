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
        CCamera camera{0.1, 2.5, aspect};
        window.SetUp(screenWidth, screenHeight, "LearnOpenGL", &camera);
        window.SetDepthTest(true);
        window.SetMouseControl();

        // Shader programs
        auto objectShader{CShaderProgram::Build("09-shader.vert", "08-shader.frag")};
        objectShader.Use();
        objectShader.SetUniform("model", CMatrix{});

        // Vertex data
        constexpr float quadVertices[] =
        {
            // positions     // colors
            -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
             0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
            -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

            -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
             0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
             0.05f,  0.05f,  0.0f, 1.0f, 1.0f
        };
        CVertexBufferObject vboQuads;
        vboQuads.AddVertexData(quadVertices);

        CVertexDataHandler quadsData;
        quadsData.AddVertexBufferObject(&vboQuads);
        quadsData.AddAttribute(2, 5, 0, false);
        quadsData.AddAttribute(3, 5, 2, false);

        float translations[2 * 100];
        int index = 0;
        for (int y = -10; y < 10; y += 2)
        {
            for (int x = -10; x < 10; x += 2)
            {
                translations[index++] = x / 10.0f + 0.1f;
                translations[index++] = y / 10.0f + 0.1f;
            }
        }
        CVertexBufferObject vboInstances;
        vboInstances.AddVertexData(translations);
        quadsData.AddAttributeDivisor(2, 2, 0, 1, false);

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);
            window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            // Render quads
            objectShader.Use();
            objectShader.SetUniform("view",         static_cast<const CMatrix&>(camera.GetViewMatrix()));
            objectShader.SetUniform("projection",   static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            quadsData.DrawArrays(6, 100);

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
