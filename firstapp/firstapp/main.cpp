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

    constexpr std::array<float, 9> vertices = 
    { 
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // generate buffer
    GLuint VertexBufferObjectId;
    glGenBuffers(1, &VertexBufferObjectId);

    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(decltype(vertices)::value_type), 
                 vertices.data(), GL_STATIC_DRAW);

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

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}