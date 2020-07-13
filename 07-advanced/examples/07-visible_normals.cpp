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
        window.SetDepthTest(true);
        window.SetMouseControl();

        // Shader programs
        auto objectShader{CShaderProgram::Build("07-shader.vert", "06-shader.frag")};
        auto normalsShader{CShaderProgram::Build("07-normals.vert", "07-normals.geom", "07-normals.frag")};

        // Model
        CModel model{"backpack/backpack.obj"};
        model.SetTextureUnitsUniforms(objectShader);

        // Uniforms
        CUniformBufferObject ubo;
        ubo.Allocate(3 * CMatrix::Size());
        ubo.SetBindingPoint(0);
        objectShader.SetBindingPoint("Matrices", 0);
        normalsShader.SetBindingPoint("Matrices", 0);
        ubo.SetData(CMatrix{});

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);
            window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            // Render cube
            ubo.SetData(CMatrix::Size(),
                        static_cast<const CMatrix&>(camera.GetViewMatrix()),
                        static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            objectShader.Use();
            model.Draw();
            normalsShader.Use();
            normalsShader.SetUniform("normalMatrix", CMatrix{camera.GetViewMatrix()}.Inverse().Transpose());
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
