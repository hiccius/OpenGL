#include <iostream>

#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "window.hpp"
#include "glslprograms.hpp"
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
    CShaderProgram shaderProgramOrange;
    CShaderProgram shaderProgramYellow;
    try
    {
        CShader vertexShader{CShader::Type::VertexShader, vertexShaderSource.data()};
        CShader fragmentShaderOrange{CShader::Type::FragmentShader, fragmentShaderOrangeSource.data()};
        CShader fragmentShaderYellow{CShader::Type::FragmentShader, fragmentShaderYellowSource.data()};

        vertexShader.Compile();
        fragmentShaderOrange.Compile();
        fragmentShaderYellow.Compile();

        shaderProgramOrange.Link(vertexShader, fragmentShaderOrange);
        shaderProgramYellow.Link(vertexShader, fragmentShaderYellow);
    }
    catch (const OpenGLException& exc)
    {
        std::cerr << exc.what() << std::endl;
        return -1;
    }

    // Vertex data
    CVertexDataHandler vertexDataHandlerOrange;
    float verticesOrange[] =
    {
        // first triangle
        -0.45f,  0.4f, 0.0f, // top
        -0.85f, -0.4f, 0.0f, // bottom left
        -0.05f, -0.4f, 0.0f  // bottom right
    };
    vertexDataHandlerOrange.AddVectorBufferObject(verticesOrange);
    vertexDataHandlerOrange.AddAttribute(3, 3, 0);

    CVertexDataHandler vertexDataHandlerYellow;
    float verticesYellow[] =
    {
         // second triangle
          0.45f,  0.4f, 0.0f, // top
          0.05f, -0.4f, 0.0f, // bottom left
          0.85f, -0.4f, 0.0f  // bottom right
    };
    vertexDataHandlerYellow.AddVectorBufferObject(verticesYellow);
    vertexDataHandlerYellow.AddAttribute(3, 3, 0);

    // Render loop
    while (window.IsOpen())
    {
        // Poll escape key to close
        window.PollCloseKey(Keys::Escape);

        // Render
        window.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shaderProgramOrange.Use();
        vertexDataHandlerOrange.DrawArrays(6);
        shaderProgramYellow.Use();
        vertexDataHandlerYellow.DrawArrays(6);

        // Poll events and redraw window
        window.RedrawAndPoll();
    }

    return 0;
}
