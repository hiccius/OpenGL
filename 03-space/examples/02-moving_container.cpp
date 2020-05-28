#include <iostream>

#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "window.ipp"
#include "shaderprogram.hpp"
#include "vertexdatahandler.ipp"
#include "texture.hpp"
#include "matrix.hpp"


int main(int argc, char* argv[])
{
    bool orbit{false};
    if (argc == 2)
    {
        std::string_view option{argv[1]};
        if (option == "--orbit")
        {
            orbit = true;
        }
        else if (option == "--help")
        {
            std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
            std::cout << "Usage: " << argv[0] << " [option]\n\n";
            std::cout << "Options:\n";
            std::cout << std::setw(15) << "  --orbit";
            std::cout << "The container orbits instead of rotate\n";
            std::cout << std::setw(15) << "  --help";
            std::cout << "Displays this message\n\n";
            return 0;
        }
    }

    CWindow window;
    try
    {
        window.SetUp(800, 600, "LearnOpenGL");
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
        std::cout << exc.what() << std::endl;
        return -1;
    }

    // Load textures
    CTexture containerTexture;
    try
    {
        containerTexture.SetWrappingMode(WrappingMode::Repeat);
        containerTexture.SetFilteringMode(FilteringMode::Linear);
        containerTexture.GenerateTexture("container.jpg");
    }
    catch(const OpenGLException& exc)
    {
        std::cerr << exc.what() << std::endl;
    }

    CTexture faceTexture;
    try
    {
        faceTexture.SetWrappingMode(WrappingMode::Repeat);
        faceTexture.SetFilteringMode(FilteringMode::Linear);
        faceTexture.GenerateTexture("awesomeface.png");
    }
    catch(const OpenGLException& exc)
    {
        std::cerr << exc.what() << std::endl;
    }

    // Set uniforms for samplers
    try
    {
        shaderProgram.Use();

        containerTexture.SetTextureUnitIndex(0);
        shaderProgram.SetUniform("texture1", 0);

        faceTexture.SetTextureUnitIndex(1);
        shaderProgram.SetUniform("texture2", 1);
    }
    catch (const OpenGLException& exc)
    {
        std::cerr << exc.what() << std::endl;
        return -1;
    }

    // Vertex data
    CVertexDataHandler vertexDataHandler;
    float vertices[] =
    {   // positions            // colors           // texture coordinates
         0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };
    vertexDataHandler.AddVectorBufferObject(vertices);

    int indices[] =
    {
        0, 1, 3,
        1, 2, 3
    };
    vertexDataHandler.AddElementBufferObject(indices);

    vertexDataHandler.AddAttribute(3, 8, 0);
    vertexDataHandler.AddAttribute(2, 8, 6);

    // Render loop
    while (window.IsOpen())
    {
        // Poll keys
        window.PollCloseKey(Key::Escape);

        // Render
        window.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        containerTexture.ActivateAndBind();
        faceTexture.ActivateAndBind();

        CMatrix transformations;
        if (orbit)
        {
            transformations.Rotate(static_cast<float>(window.GetTime()), 0.0f, 0.0f, 1.0f);
            transformations.Translate(0.5f, -0.5f, 0.0f);
        }
        else
        {
            transformations.Translate(0.5f, -0.5f, 0.0f);
            transformations.Rotate(static_cast<float>(window.GetTime()), 0.0f, 0.0f, 1.0f);
        }
        shaderProgram.SetUniform("transform", transformations);

        vertexDataHandler.DrawElements(6);

        // Poll events and redraw window
        window.RedrawAndPoll();
    }

    return 0;
}