#include <glad/glad.h>

#include <iostream>
#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "helpers.h"
#include "window.h"
#include "shaderprogram.h"
#include "vertexDataHandler.h"
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
        textureHandler.AddTexture("..\\..\\resources\\container.jpg", GL_RGB, GL_REPEAT, GL_LINEAR);
        textureHandler.AddTexture("..\\..\\resources\\awesomeface.png", GL_RGBA, GL_REPEAT, GL_LINEAR);
    }
    catch (const OpenGLException& exc)
    {
        std::cout << "ERROR::TEXTURE_LOADING::" << exc.what() << std::endl;
        return -1;
    }


    // Vertex data
    CVertexDataHandler vertexDataHandler;
    constexpr std::array<GLfloat, 20> vertices =
    {
        // positions            // texture coordinates
         0.5f,  0.5f, 0.0f,     1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,     1.0f, 0.0f, // bottom rigth
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f  // top left
    };
    vertexDataHandler.AddBufferObject(vertices, GL_ARRAY_BUFFER);

    constexpr std::array<GLint, 6> indices =
    {
         0, 1, 2,
         0, 2, 3
    };
    vertexDataHandler.AddBufferObject(indices, GL_ELEMENT_ARRAY_BUFFER);

    vertexDataHandler.AddAttributes(0, 3, 5, 0); // positions
    vertexDataHandler.AddAttributes(1, 2, 5, 3); // texture coordinates

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

        // Use shader
        shaderProgram.Use();

        // Apply transformations
        glm::mat4 transformMatrix{ 1.0f };
        transformMatrix = glm::translate(transformMatrix, glm::vec3(0.5f, -0.5f, 0.0f));
        transformMatrix = glm::rotate(transformMatrix, static_cast<float>(glfwGetTime()),
                                      glm::vec3(0.0f, 0.0f, 1.0f));

        glUniformMatrix4fv(shaderProgram.GetUniformLocation("transform"), 1, GL_FALSE,
                           glm::value_ptr(transformMatrix));

        // Render container
        vertexDataHandler.DrawElements();

        // Apply transformations
        transformMatrix = glm::mat4{ 1.0f }; // reset to identity matrix
        transformMatrix = glm::translate(transformMatrix, glm::vec3(-0.5f, 0.5f, 0.0f));
        GLfloat scaleValue = sin(static_cast<GLfloat>(glfwGetTime()));
        transformMatrix = glm::scale(transformMatrix, glm::vec3(scaleValue, scaleValue, 0.0f));

        glUniformMatrix4fv(shaderProgram.GetUniformLocation("transform"), 1, GL_FALSE,
            glm::value_ptr(transformMatrix));

        // Render container
        vertexDataHandler.DrawElements();

        // Poll events and redraw window
        window.RedrawAndPoll();
    }

    return 0;
}