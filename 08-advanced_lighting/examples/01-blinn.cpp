#include <iostream>

#include "window.hpp"
#include "camera.hpp"
#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "vertexbufferobject.ipp"
#include "vertexdatahandler.hpp"
#include "texture.hpp"
#include "shaderprogram.ipp"


int main()
{
    constexpr int screenWidth{800};
    constexpr int screenHeight{600};
    constexpr double aspect{static_cast<double>(screenWidth) / screenHeight};

    try
    {
        // Init window
        CWindow window;
        CCamera camera{0.1, 2.5, aspect};
        window.SetUp(screenWidth, screenHeight, "LearnOpenGL", &camera);
        window.SetMouseControl();
        window.SetDepthTest(true);

        SetBlending(BlendingFactor::Alpha, BlendingFactor::AlphaComplement);

        // Shader programs
        auto shaderProgram{CShaderProgram::Build("01-shader.vert", "01-shader.frag")};
        shaderProgram.Use();
        shaderProgram.SetUniform("model",           CMatrix{});
        shaderProgram.SetUniform("light.position",  0.0f, 0.0f, 0.0f);
        shaderProgram.SetUniform("light.ambient",   0.05f);
        shaderProgram.SetUniform("light.diffuse",   1.0f);
        shaderProgram.SetUniform("light.specular",  0.3f);
        shaderProgram.SetUniform("diffuse",         0);

        // Vertex data
        float planeVertices[] =
        {
            // positions            // normals         // texture coordinates
             10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
            -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
            -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

             10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
            -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
             10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
        };
        CVertexBufferObject vboPlane;
        vboPlane.AddVertexData(planeVertices);

        CVertexDataHandler floorData;
        floorData.AddVertexBufferObject(&vboPlane);
        floorData.AddAttribute(3, 8, 0, false);
        floorData.AddAttribute(3, 8, 3, false);
        floorData.AddAttribute(2, 8, 6, false);

        // Textures
        CTexture wood(CTexture::Type::Diffuse);
        wood.GenerateTexture("wood.png");

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);

            // Render
            window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            shaderProgram.Use();
            shaderProgram.SetUniform("projection",    static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            shaderProgram.SetUniform("view",          static_cast<const CMatrix&>(camera.GetViewMatrix()));
            shaderProgram.SetUniform("viewPosition",  camera.GetPositionVector());
            wood.ActivateAndBind(0);
            floorData.DrawArrays(6);

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
