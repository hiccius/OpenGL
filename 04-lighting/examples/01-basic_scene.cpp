#include <iostream>

#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "window.ipp"
#include "shaderprogram.hpp"
#include "vertexdatahandler.ipp"
#include "texture.hpp"
#include "matrixderived.hpp"
#include "camera.hpp"
#include "vertexbufferobject.ipp"


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
        auto objectShaderProgram{CShaderProgram::Build("01-objectshader.vert", "01-objectshader.frag")};
        auto lightShaderProgram{CShaderProgram::Build("lightshader.vert", "lightshader.frag")};

        objectShaderProgram.Use();
        objectShaderProgram.SetUniform("model",       CMatrix{});
        objectShaderProgram.SetUniform("objectColor", 1.0f, 0.5f, 0.31f);
        objectShaderProgram.SetUniform("lightColor",  1.0f, 1.0f, 1.0f);

        lightShaderProgram.Use();
        lightShaderProgram.SetUniform("model", CMatrix{}.Translate(1.2f, 1.0f, 2.0f).Scale(0.2f));

        // Vertex data
        constexpr float vertices[] =
        {
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

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
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
        };
        CVertexBufferObject vbo;
        vbo.AddVertexData(vertices);

        CVertexDataHandler objectData;
        objectData.AddVertexBufferObject(&vbo);
        objectData.AddAttribute(3, 3, 0);

        CVertexDataHandler lightData;
        lightData.AddVertexBufferObject(&vbo);
        lightData.AddAttribute(3, 3, 0);

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);

            // Render
            window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            objectShaderProgram.Use();
            objectShaderProgram.SetUniform("projection",  static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            objectShaderProgram.SetUniform("view",        static_cast<const CMatrix&>(camera.GetViewMatrix()));
            objectData.DrawArrays(36);

            lightShaderProgram.Use();
            lightShaderProgram.SetUniform("projection",  static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            lightShaderProgram.SetUniform("view",        static_cast<const CMatrix&>(camera.GetViewMatrix()));
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
