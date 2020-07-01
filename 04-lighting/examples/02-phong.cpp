#include <iostream>
#include <array>

#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "window.ipp"
#include "shaderprogram.hpp"
#include "vertexdatahandler.ipp"
#include "texture.hpp"
#include "matrixderived.hpp"
#include "camera.hpp"
#include "vertexbufferobject.ipp"


int main(int argc, char* argv[])
{
    constexpr int screenWidth{800};
    constexpr int screenHeight{600};
    constexpr double aspect{static_cast<double>(screenWidth) / screenHeight};

    // Command options
    auto [exit, orbitLight] = CommandOption("orbit",
                                            "The light source orbits above the container",
                                            argc, argv, std::cout);
    if (exit)
    {
        return 0;
    }

    try
    {
        // Init window
        CWindow window;
        CCamera camera{0.1, 2.5, aspect};
        window.SetUp(screenWidth, screenHeight, "LearnOpenGL", true, &camera);
        window.SetMouseControl();

        // Shader programs
        auto objectShaderProgram{CShaderProgram::Build("02-objectshader.vert", "02-objectshader.frag")};
        auto lightShaderProgram{CShaderProgram::Build("lightshader.vert", "lightshader.frag")};

        objectShaderProgram.Use();
        objectShaderProgram.SetUniform("model",         CMatrix{});
        objectShaderProgram.SetUniform("objectColor",   1.0f, 0.5f, 0.31f);
        objectShaderProgram.SetUniform("lightColor",    1.0f, 1.0f, 1.0f);

        // Vertex data
        constexpr float vertices[] =
        {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };
        CVertexBufferObject vbo;
        vbo.AddVertexData(vertices);

        CVertexDataHandler objectData;
        objectData.AddVertexBufferObject(&vbo);
        objectData.AddAttribute(3, 6, 0);
        objectData.AddAttribute(3, 6, 3);

        CVertexDataHandler lightData;
        lightData.AddVertexBufferObject(&vbo);
        lightData.AddAttribute(3, 6, 0);

        std::array<float, 3> lightPosition{1.2f, 1.0f, 2.0f};

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);

            // Render
            window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            if (orbitLight)
            {
                double angle{window.GetTime()};
                lightPosition[0] = 2.5f * std::cos(angle);
                lightPosition[2] = 2.5f * std::sin(angle);
            }

            objectShaderProgram.Use();
            objectShaderProgram.SetUniform("projection",    static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            objectShaderProgram.SetUniform("view",          static_cast<const CMatrix&>(camera.GetViewMatrix()));
            objectShaderProgram.SetUniform("viewPosition",  camera.GetPositionVector());
            objectShaderProgram.SetUniform("lightPosition", lightPosition);
            objectData.DrawArrays(36);

            lightShaderProgram.Use();
            lightShaderProgram.SetUniform("projection", static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            lightShaderProgram.SetUniform("view",       static_cast<const CMatrix&>(camera.GetViewMatrix()));
            lightShaderProgram.SetUniform("model",      CMatrix{}.Translate(lightPosition).Scale(0.2f));
            lightData.DrawArrays(36);

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
