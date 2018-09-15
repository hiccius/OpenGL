#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>

#include "helpers.h"

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


GLFWwindow* InitWindow(int32_t width, int32_t weight, const std::string title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    return glfwCreateWindow(width, weight, title.c_str(), nullptr, nullptr);
}

int32_t main(int32_t argc, char* argv[])
{
    GLFWwindow* window = InitWindow(800, 600, "LearnOpenGL");
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Set window coordinates and adjust when resizing
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
                                           {
                                               glViewport(10, 0, width, height);
                                           });

    // vertex shader
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShaderId);

    GLint success;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        constexpr uint32_t infoLogSize{ 512 };
        char infoLog[infoLogSize];
        glGetShaderInfoLog(vertexShaderId, infoLogSize, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        glfwTerminate();
        return -1;
    }

    // fragment shader
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShaderId);

    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        constexpr uint32_t infoLogSize{ 512 };
        char infoLog[infoLogSize];
        glGetShaderInfoLog(fragmentShaderId, infoLogSize, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        glfwTerminate();
        return -1;
    }


    // shader program
    GLuint shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram(shaderProgramId);

    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
    if (!success)
    {
        constexpr uint32_t infoLogSize{ 512 };
        char infoLog[infoLogSize];
        glGetProgramInfoLog(shaderProgramId, infoLogSize, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
        glfwTerminate();
        return -1;
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    // generate vertex buffer
    constexpr std::array<GLfloat, 9> vertices =
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    GLuint vertexBufferObjectId;
    glGenBuffers(1, &vertexBufferObjectId);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(decltype(vertices)::value_type),
                 vertices.data(), GL_STATIC_DRAW);

    // vertex array object
    GLuint vertexArrayObjectId;
    glGenVertexArrays(1, &vertexArrayObjectId);

    // vertex attributes
    glBindVertexArray(vertexArrayObjectId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(decltype(vertices)::value_type), 0);
    glEnableVertexAttribArray(0);
    
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramId);
        glBindVertexArray(vertexArrayObjectId);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vertexBufferObjectId);
    glDeleteVertexArrays(1, &vertexArrayObjectId);

    glfwTerminate();
    return 0;
}