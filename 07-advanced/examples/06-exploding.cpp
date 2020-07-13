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
        auto objectShader{CShaderProgram::Build("06-shader.vert", "06-shader.geom", "06-shader.frag")};
        objectShader.Use();
        objectShader.SetUniform("model", CMatrix{});

        // Model
        CModel model{"backpack/backpack.obj"};
        model.SetTextureUnitsUniforms(objectShader);

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);
            window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            // Render cube
            objectShader.SetUniform("projection",   static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            objectShader.SetUniform("view",         static_cast<const CMatrix&>(camera.GetViewMatrix()));
            objectShader.SetUniform("time",         static_cast<float>(window.GetTime()));
            model.Draw();

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
