#include <iostream>

#include "shaderprogram.hpp"
#include "window.hpp"
#include "camera.hpp"
#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "model.hpp"
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
        auto shaderProgram{CShaderProgram::Build("02-shader.vert", "02-shader.frag")};
        auto lightShaderProgram{CShaderProgram::Build("02-light.vert", "02-light.frag")};
        shaderProgram.Use();

        CMatrix modelMatrix;
        modelMatrix.Scale(0.5);
        shaderProgram.SetUniform("model", modelMatrix);
        shaderProgram.SetUniform("normalMatrix", modelMatrix.Inverse().Transpose());

        shaderProgram.SetUniform("material.shininess", 32.0f);

        shaderProgram.SetUniform("directionalLight.direction", -0.1f,  -1.0f,   0.5f);
        shaderProgram.SetUniform("directionalLight.ambient",    0.2f,   0.2f,   0.2f);
        shaderProgram.SetUniform("directionalLight.diffuse",    0.5f,   0.5f,   0.5f);
        shaderProgram.SetUniform("directionalLight.specular",   1.0f,   1.0f,   1.0f);

        std::array<float, 3> pointLightPosition{1.0f, 1.0f, 1.0f};
        std::array<float, 3> pointLightColor{0.8f, 0.8f, 0.1f};
        shaderProgram.SetUniform("pointLight.ambient",          0.2f, 0.2f, 0.1f);
        shaderProgram.SetUniform("pointLight.diffuse",          pointLightColor);
        shaderProgram.SetUniform("pointLight.specular",         pointLightColor);
        shaderProgram.SetUniform("pointLight.constantAtt",      1.0f);
        shaderProgram.SetUniform("pointLight.linearAtt",        0.09f);
        shaderProgram.SetUniform("pointLight.quadraticAtt",     0.032f);

        shaderProgram.SetUniform("spotLight.ambient",           0.1f, 0.1f, 0.1f);
        shaderProgram.SetUniform("spotLight.diffuse",           0.5f, 0.5f, 0.5f);
        shaderProgram.SetUniform("spotLight.specular",          1.0f, 1.0f, 1.0f);
        shaderProgram.SetUniform("spotLight.constantAtt",       1.0f);
        shaderProgram.SetUniform("spotLight.linearAtt",         0.1f);
        shaderProgram.SetUniform("spotLight.quadraticAtt",      0.032f);
        shaderProgram.SetUniform("spotLight.cosCutOffAngle",      std::cos(ToRadians(5.0f)));
        shaderProgram.SetUniform("spotLight.cosOuterCutOffAngle", std::cos(ToRadians(10.0f)));

        // Model
        CModel model{"backpack/backpack.obj"};
        model.SetTextureUnitsUniforms(shaderProgram);

        lightShaderProgram.Use();
        lightShaderProgram.SetUniform("color", pointLightColor);

        // Light source
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

        CVertexDataHandler lightData;
        lightData.AddVertexBufferObject(&vbo);
        lightData.AddAttribute(3, 3, 0, false);

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);

            // Point light position
            double angle{window.GetTime()};
            pointLightPosition[0] = 2.5f * std::cos(angle);
            pointLightPosition[2] = 2.5f * std::sin(angle);

            // Render
            window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            shaderProgram.Use();
            shaderProgram.SetUniform("projection",    static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            shaderProgram.SetUniform("view",          static_cast<const CMatrix&>(camera.GetViewMatrix()));
            shaderProgram.SetUniform("viewPosition",  camera.GetPositionVector());

            shaderProgram.SetUniform("pointLight.position", pointLightPosition);

            shaderProgram.SetUniform("spotLight.position",  camera.GetPositionVector());
            shaderProgram.SetUniform("spotLight.direction", camera.GetDirectionVector());

            model.Draw();

            lightShaderProgram.Use();
            lightShaderProgram.SetUniform("projection", static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            lightShaderProgram.SetUniform("view",       static_cast<const CMatrix&>(camera.GetViewMatrix()));
            lightShaderProgram.SetUniform("model",      CMatrix{}.Translate(pointLightPosition).Scale(0.2f));
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
