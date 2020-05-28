#include <iostream>

#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "window.ipp"
#include "shaderprogram.hpp"
#include "vertexdatahandler.ipp"
#include "texture.hpp"
#include "projection.hpp"

int main()
{
    constexpr int screenHeight{800};
    constexpr int screenWidth{600};
    static constexpr float aspect{static_cast<float>(screenHeight) / screenWidth};

    try
    {
        // Init window
        CWindow window;
        window.SetUp(screenHeight, screenWidth, "LearnOpenGL");

        // Shader program
        CShaderProgram shaderProgram;
        {
            CShader vertexShader{"04-shader.vert"};
            CShader fragmentShader{"01-shader.frag"};

            vertexShader.Compile();
            fragmentShader.Compile();

            shaderProgram.Link(vertexShader, fragmentShader);
        }

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
        {    // positions            // colors           // texture coordinates
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

        // Transformations
        CMatrix model, view;
        model.Rotate(-55.0f, 1.0f, 0.0f, 0.0f, true);
        view.Translate(0.0f, 0.0f, -3.0f);
        shaderProgram.SetUniform("model", model);
        shaderProgram.SetUniform("view", view);

        CPerspective projection{45.0f, aspect, 0.1f, 100.0f, true};
        shaderProgram.SetUniform("projection", static_cast<const CMatrix&>(projection));

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.PollCloseKey(Key::Escape);

            // Render
            window.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            containerTexture.ActivateAndBind();
            faceTexture.ActivateAndBind();
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
