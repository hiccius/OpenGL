#include <glad/glad.h>
#include <iostream>
#include <array>

#include "helpers.h"
#include "window.h"
#include "shaderprogram.h"
#include "vertexDataHandler.h"
#include "glslcode.h"


int32_t main(int32_t argc, char* argv[])
{
    CWindow window;
    if (!window.SetUp(800, 600, "LearnOpenGL"))
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    // Set window coordinates and adjust when resizing
    window.SetResizeCallback([](GLFWwindow* window, int width, int height)
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
    CShaderProgram shaderProgram;
    try
    {
        shaderProgram.AttachNewShader(GL_VERTEX_SHADER, vertexShaderSource);
    }
    catch (const OpenGLException& exc)
    {
        std::cout << "ERROR::SHADER::VERTEX::" << exc.what() << std::endl;
        return -1;
    }

    try
    {
        shaderProgram.AttachNewShader(GL_FRAGMENT_SHADER, fragmentShaderSourceOrange);
    }
    catch (const OpenGLException& exc)
    {
        std::cout << "ERROR::SHADER::FRAGMENT::" << exc.what() << std::endl;
        return -1;
    }

    try
    {
        shaderProgram.Link();
    }
    catch (const OpenGLException& exc)
    {
        std::cout << "ERROR::SHADER::PROGRAM::" << exc.what() << std::endl;
        return -1;
    }

    // Vertex data
    CVertexDataHandler vertexDataHandler;
    constexpr std::array<GLfloat, 9> vertices =
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    vertexDataHandler.AddBufferObject(vertices, GL_ARRAY_BUFFER);
    vertexDataHandler.AddAttributes(0, 3, 0);

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