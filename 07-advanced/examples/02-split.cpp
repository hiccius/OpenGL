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
        window.SetMouseControl();
        window.SetDepthTest(true);
        glEnable(GL_PROGRAM_POINT_SIZE);

        // Shader programs
        auto shaderProgram{CShaderProgram::Build("01-shader.vert", "01-shader.frag")};
        shaderProgram.Use();

        // Vertex data
        constexpr float points[] =
        {
            // positions
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f
        };
        CVertexBufferObject vboPoints;
        vboPoints.AddVertexData(points);

        CVertexDataHandler pointsData;
        pointsData.AddVertexBufferObject(&vboPoints);
        pointsData.AddAttribute(3, 3, 0, false);

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);

            // Render
            window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            shaderProgram.Use();
            shaderProgram.SetUniform("model",       CMatrix{});
            shaderProgram.SetUniform("view",        static_cast<const CMatrix&>(camera.GetViewMatrix()));
            shaderProgram.SetUniform("projection",  static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));

            pointsData.DrawPoints(8);

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
