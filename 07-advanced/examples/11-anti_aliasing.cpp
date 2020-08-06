#include <iostream>

#include "window.hpp"
#include "camera.hpp"
#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "model.hpp"
#include "cubemap.hpp"
#include "11-framebuffer_wrapper.hpp"

enum class AntiAliasing
{
    Enable, Disable, Framebuffer
};


int main(int argc, char* argv[])
{
    constexpr int screenWidth{800};
    constexpr int screenHeight{600};
    constexpr double aspect{static_cast<double>(screenWidth) / screenHeight};

    auto [exit, antiAliasing] = CommandOption({
        { "disable",        { "Disable anti-aliasing",                  AntiAliasing::Disable       }},
        { "framebuffer",    { "Applies anti-aliasing to a framebuffer", AntiAliasing::Framebuffer   }}},
        AntiAliasing::Enable, argc, argv, std::cout);

    try
    {
        // Init window
        CWindow window{antiAliasing == AntiAliasing::Enable};
        CCamera camera{0.1, 2.5, aspect};
        window.SetUp(screenWidth, screenHeight, "LearnOpenGL", &camera);
        window.SetDepthTest(true);
        window.SetMouseControl();

        // Shader programs
        auto objectShader{CShaderProgram::Build("11-shader.vert", "11-shader.frag")};
        objectShader.Use();
        objectShader.SetUniform("model", CMatrix{});

        // Vertex data
        constexpr float cubeVertices[] =
        {
            // positions
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
        CVertexBufferObject vboCube;
        vboCube.AddVertexData(cubeVertices);

        CVertexDataHandler cubeData;
        cubeData.AddVertexBufferObject(&vboCube);
        cubeData.AddAttribute(3, 3, 0, false);

        // Framebuffer
        std::unique_ptr<CFramebufferWrapper> framebuffer;
        if (antiAliasing == AntiAliasing::Framebuffer)
        {
            framebuffer = std::make_unique<CFramebufferWrapper>(screenWidth, screenHeight);
        }

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);

            // Framebuffer
            if (antiAliasing == AntiAliasing::Framebuffer)
            {
                framebuffer->Bind();
            }

            window.SetDepthTest(true);
            window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            objectShader.Use();
            objectShader.SetUniform("projection",   static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            objectShader.SetUniform("view",         static_cast<const CMatrix&>(camera.GetViewMatrix()));
            cubeData.DrawArrays(36);

            // Screen
            if (antiAliasing == AntiAliasing::Framebuffer)
            {
                framebuffer->Draw(window, screenWidth, screenHeight);
            }

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
