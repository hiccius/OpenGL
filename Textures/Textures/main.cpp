#include <glad/glad.h>
#include <iostream>
#include <array>

#include "helpers.h"
#include "window.h"
#include "shaderprogram.h"
#include "vertexDataHandler.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

    // Load texture 1
    GLuint texture1Id;
    glGenTextures(1, &texture1Id);
    glBindTexture(GL_TEXTURE_2D, texture1Id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLint height, width, numberOfChannels;
    uint8_t* textureData = stbi_load("..\\Resources\\container.jpg", &width, &height, &numberOfChannels, 0);
    if (textureData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(textureData);
    }
    else
    {
        std::cout << "Error loading texture" << std::endl;
        return -1;
    }

    // Load texture 2
    GLuint texture2Id;
    glGenTextures(1, &texture2Id);
    glBindTexture(GL_TEXTURE_2D, texture2Id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    textureData = stbi_load("..\\Resources\\awesomeface.png", &width, &height, &numberOfChannels, 0);
    if (textureData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(textureData);
    }
    else
    {
        std::cout << "Error loading texture" << std::endl;
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

        // Bind texture

        // Render constainer
        shaderProgram.Use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1Id);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2Id);
        vertexDataHandler.DrawElements();

        // Poll events and redraw window
        window.RedrawAndPoll();
    }

    return 0;
}