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
        window.SetUp(screenWidth, screenHeight, "LearnOpenGL", true, &camera);
        window.SetMouseControl();

        // Shader programs
        auto objectShaderProgram{CShaderProgram::Build("03-objectshader.vert", "03-objectshader.frag")};
        auto lightShaderProgram{CShaderProgram::Build("lightshader.vert", "lightshader.frag")};

        constexpr std::array<float, 3> lightPosition{1.2f, 1.0f, 2.0f};

        objectShaderProgram.Use();
        objectShaderProgram.SetUniform("objectColor",   1.0f, 0.5f, 0.31f);
        objectShaderProgram.SetUniform("lightColor",    1.0f, 1.0f, 1.0f);
        objectShaderProgram.SetUniform("worldLightPos", lightPosition);

        lightShaderProgram.Use();
        lightShaderProgram.SetUniform("model", CMatrix{}.Translate(lightPosition).Scale(0.2f));

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

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);

            // Render
            window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            CMatrix normalMatrix{CMatrix{camera.GetViewMatrix()}.Inverse().Transpose()};

            objectShaderProgram.Use();
            objectShaderProgram.SetUniform("projection",   static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            objectShaderProgram.SetUniform("view",         static_cast<const CMatrix&>(camera.GetViewMatrix()));
            objectShaderProgram.SetUniform("modelView",    static_cast<const CMatrix&>(camera.GetViewMatrix()));
            objectShaderProgram.SetUniform("normalMatrix", normalMatrix);
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
