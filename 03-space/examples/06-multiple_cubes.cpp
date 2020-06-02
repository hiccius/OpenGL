#include <iostream>
#include <array>
#include <tuple>

#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "window.ipp"
#include "shaderprogram.hpp"
#include "vertexdatahandler.ipp"
#include "texture.hpp"
#include "matrixderived.hpp"


int main(int argc, char* argv[])
{
    constexpr int screenHeight{800};
    constexpr int screenWidth{600};
    constexpr float aspect{static_cast<float>(screenHeight) / screenWidth};

    auto [exit, rotate] = CommandOption("rotate", "Rotate every third container",
                                        argc, argv, std::cout);
    if (exit)
    {
        return 0;
    }

    try
    {
        // Init window
        CWindow window;
        window.SetUp(screenHeight, screenWidth, "LearnOpenGL", true);

        // Shader program
        CShaderProgram shaderProgram{CShaderProgram::Build("04-shader.vert", "01-shader.frag")};

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
        vertexDataHandler.AddVectorBufferObject(vertices);

        vertexDataHandler.AddAttribute(3, 5, 0);
        vertexDataHandler.AddAttribute(2, 5, 3);

        // Transformations
        CMatrix view;
        view.Translate(0.0f, 0.0f, -3.0f);
        shaderProgram.SetUniform("view", view);

        CPerspectiveMatrix projection{45.0f, aspect, 0.1f, 100.0f, true};
        shaderProgram.SetUniform("projection", static_cast<const CMatrix&>(projection));

        constexpr std::array<std::array<float, 3>, 10> cubePositions{{
            {  0.0f,  0.0f,   0.0f },
            {  2.0f,  5.0f, -15.0f },
            { -1.5f, -2.2f, - 2.5f },
            { -3.8f, -2.0f, -12.3f },
            {  2.4f, -0.4f, - 3.5f },
            { -1.7f,  3.0f, - 7.5f },
            {  1.3f, -2.0f, - 2.5f },
            {  1.5f,  2.0f, - 2.5f },
            {  1.5f,  0.2f, - 1.5f },
            { -1.3f,  1.0f, - 1.5f }
        }};

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.PollCloseKey(Key::Escape);

            // Render
            window.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            containerTexture.ActivateAndBind();
            faceTexture.ActivateAndBind();

            for (std::size_t i = 0; i < cubePositions.size(); ++i)
            {
                CMatrix model;
                const auto& [x, y, z] = cubePositions[i];

                model.Translate(x, y, z);
                float rotationAngle = static_cast<float>(20.0 * (rotate && (i % 3 == 0) ? window.GetTime() : i));
                model.Rotate(rotationAngle, 1.0f, 0.3f, 0.5f, true);

                shaderProgram.SetUniform("model", model);
                vertexDataHandler.DrawArrays(36);
            }

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
