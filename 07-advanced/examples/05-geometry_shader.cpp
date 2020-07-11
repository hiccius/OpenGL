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

    try
    {
        // Init window
        CWindow window;
        window.SetUp(screenWidth, screenHeight, "LearnOpenGL");

        // Shader programs
        auto shaderProgram{CShaderProgram::Build("05-shader.vert", "05-shader.geom", "05-shader.frag")};
        shaderProgram.Use();

        // Vertex data
        constexpr float points[] =
        {
            // positions  // colors
            -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f,  0.5f, 1.0f, 0.0f, 0.0f
        };
        CVertexBufferObject vboPoints;
        vboPoints.AddVertexData(points);

        CVertexDataHandler pointsData;
        pointsData.AddVertexBufferObject(&vboPoints);
        pointsData.AddAttribute(2, 5, 0, false);
        pointsData.AddAttribute(3, 5, 2, false);

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);

            // Render
            window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            pointsData.DrawPoints(4);

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
