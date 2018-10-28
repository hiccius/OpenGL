#include <glad/glad.h>

#include <iostream>
#include <array>

#include "helpers.h"
#include "window.h"
#include "shaderprogram.h"
#include "vertexdatahandler.h"
#include "texturehandler.h"
#include "projectionmatrix.h"


int32_t main(int32_t argc, char* argv[])
{
    constexpr int32_t windowWidth = 800;
    constexpr int32_t windowHeight = 600;
    constexpr float fieldOfView = 60.0f;

    CWindow window;
    if (!window.SetUp(windowWidth, windowHeight, "LearnOpenGL"))
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    if (!window.SetProjectionMatrix(EProjection::PerspectiveProportional, fieldOfView))
    {
        std::cout << "Failed to create projection matrix" << std::endl;
        return -1;
    }

    // Set window coordinates and adjust when resizing
    window.SetResizeCallback([](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
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
    constexpr std::array<GLfloat, 180> vertices =
    {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    vertexDataHandler.AddBufferObject(vertices, GL_ARRAY_BUFFER);

    vertexDataHandler.AddAttributes(0, 3, 5, 0); // positions
    vertexDataHandler.AddAttributes(1, 2, 5, 3); // texture coordinates

    // Set transformation matrices
    glm::mat4 viewMatrix{ 1.0f };
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));

    // Set uniforms for textures render
    shaderProgram.Use();
    glUniform1i(shaderProgram.GetUniformLocation("texture1"), 0);
    glUniform1i(shaderProgram.GetUniformLocation("texture2"), 1);

    // Enable depth testing (Z-buffer)
    glEnable(GL_DEPTH_TEST);

    // Cube positions
    std::array<glm::vec3, 10> cubePositions =
    {
        glm::vec3( 0.0f,  0.0f,   0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f,  -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f,  -3.5f),
        glm::vec3(-1.7f,  3.0f,  -7.5f),
        glm::vec3( 1.3f, -2.0f,  -2.5f),
        glm::vec3( 1.5f,  2.0f,  -2.5f),
        glm::vec3( 1.5f,  0.2f,  -1.5f),
        glm::vec3(-1.3f,  1.0f,  -1.5f)
    };

    // Render loop
    while (window.IsOpen())
    {
        // Poll escape key to close
        window.PollCloseKey(GLFW_KEY_ESCAPE);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Bind textures
        textureHandler.ActiveTextures();

        // Use shader
        shaderProgram.Use();

        // Apply transformations
        glUniformMatrix4fv(shaderProgram.GetUniformLocation("view"), 1, GL_FALSE,
                           glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(shaderProgram.GetUniformLocation("projection"), 1, GL_FALSE,
                           window.GetProjectionMatrixValuePtr());

        for (uint32_t i = 0; i < cubePositions.size(); ++i)
        {
            glm::mat4 modelMatrix{ 1.0f };

            modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
            float rotationAngle = glm::radians(20.0f * i);
            if (i % 3 == 0)
            {
                rotationAngle += glm::radians(static_cast<float>(glfwGetTime()) * 40.0f);
            }
            modelMatrix = glm::rotate(modelMatrix, rotationAngle, glm::vec3(1.0f, 0.3f, 0.5f));

            glUniformMatrix4fv(shaderProgram.GetUniformLocation("model"), 1, GL_FALSE,
                               glm::value_ptr(modelMatrix));

            // Render container
            vertexDataHandler.DrawArrays(36);
        }

        // Poll events and redraw window
        window.RedrawAndPoll();
    }

    return 0;
}
