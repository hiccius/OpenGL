#include <glad/glad.h>
#include <iostream>

#include "helpers.hpp"
#include "window.hpp"
#include "shaderprogram.hpp"
#include "vertexdatahandler.ipp"
#include "glslprograms.hpp"


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
        glViewport(10, 0, width, height);
    });

    // Load GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
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
        // first triangle
        -0.4f,  0.4f, 0.0f, // top
        -0.8f, -0.4f, 0.0f, // bottom left
         0.0f, -0.4f, 0.0f, // bottom right
        // second triangle
         0.4f,  0.4f, 0.0f, // top
         0.0f, -0.4f, 0.0f, // bottom left
         0.8f, -0.4f, 0.0f, // bottom right
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
        vertexDataHandler.DrawArrays(6);

        // Poll events and redraw window
        window.RedrawAndPoll();
    }

    return 0;
}
