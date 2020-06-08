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
        auto objectShaderProgram{CShaderProgram::Build("05-objectshader.vert", "05-objectshader.frag")};
        auto lightShaderProgram{CShaderProgram::Build("lightshader.vert", "05-lightshader.frag")};

        constexpr std::array<float, 3> lightPosition{1.2f, 1.0f, 2.0f};

        objectShaderProgram.Use();
        objectShaderProgram.SetUniform("model", CMatrix{});
        objectShaderProgram.SetUniform("material.ambient",      1.0f, 0.5f, 0.31f);
        objectShaderProgram.SetUniform("material.diffuse",      1.0f, 0.5f, 0.31f);
        objectShaderProgram.SetUniform("material.specular",     0.5f, 0.5f, 0.5f);
        objectShaderProgram.SetUniform("material.shininess",    32.0f);
        objectShaderProgram.SetUniform("light.position",    lightPosition);
        objectShaderProgram.SetUniform("light.specular",    1.0f, 1.0f, 1.0f);

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
            double time{window.GetTime()};
            std::array<float,3> lightColor{static_cast<float>(std::sin(time * 2.0)),
                                           static_cast<float>(std::sin(time * 0.7)),
                                           static_cast<float>(std::sin(time * 1.3))};
            std::array<float,3> ambientLight;
            std::array<float,3> diffuseLight;
            for (std::size_t i = 0; i < lightColor.size(); ++i)
            {
                ambientLight[i] = 0.2f * lightColor[i];
                diffuseLight[i] = 0.5f * lightColor[i];
                lightColor[i] *= 0.6f;
            }

            objectShaderProgram.Use();
            objectShaderProgram.SetUniform("projection",    static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            objectShaderProgram.SetUniform("view",          static_cast<const CMatrix&>(camera.GetViewMatrix()));
            objectShaderProgram.SetUniform("viewPosition",  camera.GetPositionVector());
            objectShaderProgram.SetUniform("light.ambient", ambientLight);
            objectShaderProgram.SetUniform("light.diffuse", diffuseLight);
            objectData.DrawArrays(36);

            lightShaderProgram.Use();
            lightShaderProgram.SetUniform("projection", static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            lightShaderProgram.SetUniform("view",       static_cast<const CMatrix&>(camera.GetViewMatrix()));
            lightShaderProgram.SetUniform("lightColor", lightColor);
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
