#include <iostream>

#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "window.hpp"
#include "shaderprogram.hpp"
#include "vertexdatahandler.ipp"


int main()
{
    CWindow window;
    try
    {
        window.SetUp(800, 600, "LearnOpenGL");
        LoadGLAD();
    }
    catch (const OpenGLException& exc)
    {
        std::cerr << exc.what() << std::endl;
        return -1;
    }

    // Shader program
    CShaderProgram shaderProgram;
    try
    {
        CShader vertexShader{"05-shader.vert"};
        CShader fragmentShader{"05-shader.frag"};

        vertexShader.Compile();
        fragmentShader.Compile();

        shaderProgram.Link(vertexShader, fragmentShader);
    }
    catch (const OpenGLException& exc)
    {
        std::cerr << exc.what() << std::endl;
        return -1;
    }

    // Vertex data
    CVertexDataHandler vertexDataHandler;
    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    vertexDataHandler.AddVectorBufferObject(vertices);
    vertexDataHandler.AddAttribute(3, 3, 0);

    // Render loop
    while (window.IsOpen())
    {
        // Poll escape key to close
        window.PollCloseKey(Keys::Escape);

        // Render
        window.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shaderProgram.Use();
        vertexDataHandler.DrawArrays(3);

        // Poll events and redraw window
        window.RedrawAndPoll();
    }

    return 0;
}
