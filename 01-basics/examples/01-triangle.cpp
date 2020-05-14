#include <glad/glad.h>
#include <iostream>

#include "window.hpp"
#include "shader.hpp"
#include "glslprograms.hpp"
#include "helpers.hpp"
#include "shaderprogram.hpp"
#include "vertexdatahandler.ipp"


int main()
{
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

    // Set window coordinates and adjust when resizing
    window.SetResizeCallback([](GLFWwindow*, int width, int height)
    {
        glViewport(0, 0, width, height);
    });

    // Load GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Shader program
    CShader vertexShader{CShader::Type::VertexShader, vertexShaderSource.data()};
    CShader fragmentShader{CShader::Type::FragmentShader, fragmentShaderSource.data()};
    try
    {
        vertexShader.Compile();
        fragmentShader.Compile();
    }
    catch (const OpenGLException& exc)
    {
        std::cerr << exc.what() << std::endl;
        return -1;
    }

    CShaderProgram shaderProgram;
    try
    {
        shaderProgram.Link(vertexShader, fragmentShader);
    }
    catch (const OpenGLException& exc)
    {
        std::cout << exc.what() << std::endl;
        return -1;
    }

    vertexShader.Delete();
    fragmentShader.Delete();

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
        window.PollCloseKey(GLFW_KEY_ESCAPE);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Use();
        vertexDataHandler.DrawArrays(3);

        // Poll events and redraw window
        window.RedrawAndPoll();
    }

    return 0;
}
