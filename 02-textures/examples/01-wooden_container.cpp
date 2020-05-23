#include <iostream>

#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "window.hpp"
#include "shaderprogram.hpp"
#include "vertexdatahandler.ipp"
#include "texturehandler.hpp"


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
        CShader vertexShader{"01-shader.vert"};
        CShader fragmentShader{"01-shader.frag"};

        vertexShader.Compile();
        fragmentShader.Compile();

        shaderProgram.Link(vertexShader, fragmentShader);
    }
    catch (const OpenGLException& exc)
    {
        std::cerr << exc.what() << std::endl;
        return -1;
    }

    // Texture data
    CTextureHandler textureHandler;
    try
    {
        textureHandler.SetWrappingMode(WrappingMode::Repeat);
        textureHandler.SetFilteringMode(FilteringMode::Linear);
        textureHandler.GenerateTexture("container.jpg");
    }
    catch (const OpenGLException& exc)
    {
        std::cerr << exc.what() << std::endl;
    }

    // Vertex data
    CVertexDataHandler vertexDataHandler;
    float vertices[] =
    {   // positions            // colors           // texture coordinates
         0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,     // top right
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,     // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,     // bottom left
        -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f,   0.0f, 1.0f      // top left
    };
    vertexDataHandler.AddVectorBufferObject(vertices);

    int indices[] =
    {
        0, 1, 3,
        1, 2, 3
    };
    vertexDataHandler.AddElementBufferObject(indices);

    vertexDataHandler.AddAttribute(3, 8, 0);
    vertexDataHandler.AddAttribute(3, 8, 3);
    vertexDataHandler.AddAttribute(2, 8, 6);

    // Render loop
    while (window.IsOpen())
    {
        // Poll escape key to close
        window.PollCloseKey(Key::Escape);

        // Render
        window.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shaderProgram.Use();
        textureHandler.BindTexture();
        vertexDataHandler.DrawElements(6);

        // Poll events and redraw window
        window.RedrawAndPoll();
    }

    return 0;
}
