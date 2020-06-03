#include <iostream>

#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "window.ipp"
#include "shaderprogram.hpp"
#include "vertexdatahandler.ipp"
#include "texture.hpp"
#include "matrix.hpp"


int main()
{
    try
    {
        // Init window
        CWindow window;
        window.SetUp(800, 600, "LearnOpenGL");

        // Shader program
        CShaderProgram shaderProgram{CShaderProgram::Build("01-shader.vert", "01-shader.frag")};

        // Load textures
        CTexture containerTexture;
        containerTexture.SetWrappingMode(WrappingMode::Repeat);
        containerTexture.SetFilteringMode(FilteringMode::Linear);
        containerTexture.GenerateTexture("container.jpg");

        CTexture faceTexture;
        faceTexture.SetWrappingMode(WrappingMode::Repeat);
        faceTexture.SetFilteringMode(FilteringMode::Linear);
        faceTexture.GenerateTexture("awesomeface.png");

        // Set uniforms for samplers
        shaderProgram.Use();

        containerTexture.SetTextureUnitIndex(0);
        shaderProgram.SetUniform("texture1", 0);

        faceTexture.SetTextureUnitIndex(1);
        shaderProgram.SetUniform("texture2", 1);

        // Vertex data
        CVertexDataHandler vertexDataHandler;
        float vertices[] =
        {   // positions            // colors           // texture coordinates
             0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
             0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
        };
        vertexDataHandler.AddVectorBufferObject(vertices);

        int indices[] =
        {
            0, 1, 3,
            1, 2, 3
        };
        vertexDataHandler.AddElementBufferObject(indices);

        vertexDataHandler.AddAttribute(3, 8, 0);
        vertexDataHandler.AddAttribute(2, 8, 6);

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.PollCloseKey(Key::Escape);

            // Render
            window.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            containerTexture.ActivateAndBind();
            faceTexture.ActivateAndBind();

            CMatrix rotateTransforms;
            rotateTransforms.Translate(0.5f, -0.5f, 0.0f);
            rotateTransforms.Rotate(static_cast<float>(window.GetTime()), 0.0f, 0.0f, 1.0f);
            shaderProgram.SetUniform("transform", rotateTransforms);
            vertexDataHandler.DrawElements(6);

            CMatrix scaleTransforms;
            float scaleValue = static_cast<float>(std::sin(window.GetTime()));
            scaleTransforms.Translate(-0.5f, 0.5f, 0.0f);
            scaleTransforms.Scale(scaleValue, scaleValue, 0.0f);
            shaderProgram.SetUniform("transform", scaleTransforms);
            vertexDataHandler.DrawElements(6);

            // Poll events and redraw window
            window.RedrawAndPoll();
        }

        return 0;
    }
    catch (const OpenGLException& exc)
    {
        std::cerr << exc.what() << std::endl;
        return -1;
    }
}
