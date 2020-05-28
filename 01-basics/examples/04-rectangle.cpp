#include <iostream>

#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "window.hpp"
#include "shaderprogram.hpp"
#include "vertexdatahandler.ipp"


int main(int argc, char* argv[])
{
    bool fill{true};
    if (argc == 2)
    {
        std::string_view option{argv[1]};
        if (option == "--no-fill")
        {
            fill = false;
        }
        else if (option == "--help")
        {
            std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
            std::cout << "Usage: " << argv[0] << " [option]\n\n";
            std::cout << "Options:\n";
            std::cout << std::setw(15) << "  --no-fill";
            std::cout << "Draw shape in wireframe mode\n";
            std::cout << std::setw(15) << "  --help";
            std::cout << "Displays this message\n\n";
            return 0;
        }
    }

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
        CShader vertexShader{"04-shader.vert"};
        CShader fragmentShader{"04-shader.frag"};

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
         0.5f,  0.5f, 0.0f, // top right
         0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f  // top left
    };
    vertexDataHandler.AddVectorBufferObject(vertices);

    int indices[] =
    {
        0, 1, 3,
        1, 2, 3
    };
    vertexDataHandler.AddElementBufferObject(indices);

    vertexDataHandler.AddAttribute(3, 3, 0);

    // Polygon mode
    FillShape(fill);

    // Render loop
    while (window.IsOpen())
    {
        // Poll escape key to close
        window.PollCloseKey(Keys::Escape);

        // Render
        window.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shaderProgram.Use();
        vertexDataHandler.DrawElements(6);

        // Poll events and redraw window
        window.RedrawAndPoll();
    }

    return 0;
}
