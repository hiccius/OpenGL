#include <glad/glad.h>
#include <iostream>
#include <array>

#include "helpers.h"
#include "window.h"
#include "shaderprogram.h"
#include "vertexdatahandler.h"
#include "texturehandler.h"


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
        shaderProgram.AttachShadersFromFile("shader.vert", "shader.frag");
    }
    catch (const OpenGLException& exc)
    {
        std::cout << "ERROR::SHADER::" << exc.what() << std::endl;
        return -1;
    }

    // Load textures
    CTextureHandler textureHandler;

    try
    {
        textureHandler.AddTexture("..\\Resources\\container.jpg", GL_RGB);
        textureHandler.AddTexture("..\\Resources\\awesomeface.png", GL_RGBA);
    }
    catch (const OpenGLException& exc)
    {
        std::cout << "ERROR::TEXTURE_LOADING::" << exc.what() << std::endl;
        return -1;
    }


    // Vertex data
    CVertexDataHandler vertexDataHandler;

    constexpr std::array<GLfloat, 32> vertices =
    {
        // positions            // color            // texture coordinates
         0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom rigth
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    vertexDataHandler.AddBufferObject(vertices, GL_ARRAY_BUFFER);

    constexpr std::array<GLint, 6> indices =
    {
         0, 1, 2,
         0, 2, 3
    };
    vertexDataHandler.AddBufferObject(indices, GL_ELEMENT_ARRAY_BUFFER);

    vertexDataHandler.AddAttributes(0, 3, 8, 0); // positions
    vertexDataHandler.AddAttributes(1, 3, 8, 3); // color
    vertexDataHandler.AddAttributes(2, 2, 8, 6); // texture coordinates

    // Set uniforms for textures render
    shaderProgram.Use();
    glUniform1i(shaderProgram.GetUniformLocation("texture1"), 0);
    glUniform1i(shaderProgram.GetUniformLocation("texture2"), 1);

    // Render loop
    while (window.IsOpen())
    {
        // Poll escape key to close
        window.PollCloseKey(GLFW_KEY_ESCAPE);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind textures
        textureHandler.ActiveTextures();

        // Render container
        shaderProgram.Use();
        vertexDataHandler.DrawElements();

        // Poll events and redraw window
        window.RedrawAndPoll();
    }

    return 0;
}