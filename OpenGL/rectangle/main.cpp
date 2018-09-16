#include <glad/glad.h>
#include <iostream>
#include <array>

#include "helpers.h"
#include "window.h"
#include "shaderprogram.h"

constexpr CStringLiteral vertexShaderSource =
"#version 440 core"                                     "\n"
"layout(location = 0) in vec3 aPos;"                    "\n"
"void main()"                                           "\n"
"{"                                                     "\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"  "\n"
"};";

constexpr CStringLiteral fragmentShaderSource =
"#version 440 core"                             "\n"
"out vec4 fragColor;"                           "\n"
"void main()"                                   "\n"
"{"                                             "\n"
"fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);"  "\n"
"};";


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
        shaderProgram.AttachNewShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
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

    // vertex array object
    GLuint vertexArrayObjectId;
    glGenVertexArrays(1, &vertexArrayObjectId);
    glBindVertexArray(vertexArrayObjectId);

    // generate vertex buffer
    constexpr std::array<GLfloat, 12> vertices =
    {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    GLuint vertexBufferObjectId;
    glGenBuffers(1, &vertexBufferObjectId);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(decltype(vertices)::value_type),
        vertices.data(), GL_STATIC_DRAW);

    // element buffer object
    constexpr std::array<GLint, 6> indices =
    {
        0, 1, 3,
        1, 2, 3
    };

    GLuint elementBufferObjectId;
    glGenBuffers(1, &elementBufferObjectId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(decltype(indices)::value_type),
        indices.data(), GL_STATIC_DRAW);

    // vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(decltype(vertices)::value_type), 0);
    glEnableVertexAttribArray(0);

    // Polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Render loop
    while (window.IsOpen())
    {
        // Poll escape key to close
        window.PollCloseKey(GLFW_KEY_ESCAPE);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Use();
        glBindVertexArray(vertexArrayObjectId);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Poll events and redraw window
        window.RedrawAndPoll();
    }

    glDeleteBuffers(1, &vertexBufferObjectId);
    glDeleteBuffers(1, &elementBufferObjectId);
    glDeleteVertexArrays(1, &vertexArrayObjectId);

    return 0;
}