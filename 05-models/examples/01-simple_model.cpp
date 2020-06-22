#include <iostream>

#include "shaderprogram.hpp"
#include "window.hpp"
#include "camera.hpp"
#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "model.hpp"


int main(int argc, char* argv[])
{
    constexpr int screenHeight{800};
    constexpr int screenWidth{600};
    constexpr double aspect{static_cast<double>(screenHeight) / screenWidth};

    // Command options
    auto [exit, noFill] = CommandOption("no-fill", "Draw model in wireframe mode",
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
        window.SetUp(screenHeight, screenWidth, "LearnOpenGL", true, &camera);
        window.SetMouseControl();

        // Shader programs
        auto shaderProgram{CShaderProgram::Build("01-shader.vert", "01-shader.frag")};
        shaderProgram.Use();
        shaderProgram.SetUniform("model", CMatrix{});

        // Vertex data
        CModel model{"backpack/backpack.obj"};
        model.SetTextureUnitsUniforms(shaderProgram);

        FillShape(!noFill);

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
