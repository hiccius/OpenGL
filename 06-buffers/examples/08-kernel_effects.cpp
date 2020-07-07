#include <iostream>

#include "window.hpp"
#include "camera.hpp"
#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "model.hpp"
#include "vertexbufferobject.ipp"
#include "shaderprogram.ipp"
#include "framebuffer.hpp"
#include "renderbufferobject.hpp"


int main(int argc, char* argv[])
{
    constexpr int screenWidth{800};
    constexpr int screenHeight{600};
    constexpr double aspect{static_cast<double>(screenWidth) / screenHeight};

    // Command options
    auto [exit, effect] = CommandOption({
        { "sharpen",    { "Sharpens the objects",                   1 }},
        { "blur",       { "Applies a blur effect to the scene",     2 }},
        { "edges",      { "Performs edge-detection over the scene", 3 }}},
        0, argc, argv, std::cout);

    if (exit)
    {
        return 0;
    }

    try
    {
        // Init window
        CWindow window;
        CCamera camera{0.1, 2.5, aspect};
        window.SetUp(screenWidth, screenHeight, "LearnOpenGL", &camera);
        window.SetMouseControl();

        // Shader programs
        auto objectShader{CShaderProgram::Build("shader.vert", "02-shader.frag")};
        auto screenShader{CShaderProgram::Build("06-shader.vert", "08-shader.frag")};

        objectShader.Use();
        objectShader.SetUniform("diffuse", 0);

        screenShader.Use();
        screenShader.SetUniform("screenTexture", 0);
        screenShader.SetUniform("effect", effect);

        // Framebuffer
        CFramebuffer framebuffer;

        CTextureBuffer colorBuffer;
        colorBuffer.GenerateTexture(screenWidth, screenHeight);
        framebuffer.Attach(&colorBuffer);

        CRenderbufferObject rbo{CRenderbufferObject::Type::DepthAndStencil};
        rbo.SetUp(screenWidth, screenHeight);
        framebuffer.Attach(&rbo);

        if (!framebuffer.IsComplete())
        {
            throw OpenGLException{"FRAMEBUFFER", "Framebuffer is not complete"};
        }

        CFramebuffer::BindDefault();

        // Vertex data
        constexpr float cubeVertices[] =
        {
            // positions          // texture coordinates
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
        CVertexBufferObject vboCube;
        vboCube.AddVertexData(cubeVertices);

        CVertexDataHandler cubeData;
        cubeData.AddVertexBufferObject(&vboCube);
        cubeData.AddAttribute(3, 5, 0, false);
        cubeData.AddAttribute(2, 5, 3, false);

        CMatrix modelCube1;
        modelCube1.Translate(-1.0f, 0.0f, -1.0f);
        CMatrix modelCube2;
        modelCube2.Translate(2.0f, 0.0f, 0.0f);

        float planeVertices[] =
        {
            // positions          // texture coordinates
             5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
            -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

             5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
             5.0f, -0.5f, -5.0f,  2.0f, 2.0f
        };
        CVertexBufferObject vboPlane;
        vboPlane.AddVertexData(planeVertices);

        CVertexDataHandler floorData;
        floorData.AddVertexBufferObject(&vboPlane);
        floorData.AddAttribute(3, 5, 0, false);
        floorData.AddAttribute(2, 5, 3, false);

        constexpr float quadVertices[] =
        {
            // positions   // texture coordinates
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
             1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
             1.0f, -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f,  1.0f, 1.0f
        };
        CVertexBufferObject vboQuad;
        vboQuad.AddVertexData(quadVertices);

        CVertexDataHandler quadData;
        quadData.AddVertexBufferObject(&vboQuad);
        quadData.AddAttribute(2, 4, 0, false);
        quadData.AddAttribute(2, 4, 2, false);

        // Textures
        CTexture wood(CTexture::Type::Diffuse);
        wood.GenerateTexture("container.jpg");

        CTexture metal(CTexture::Type::Diffuse);
        metal.GenerateTexture("metal.png");

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);

            // Render framebuffer
            framebuffer.Bind();
            window.SetDepthTest(true);
            window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            objectShader.Use();
            objectShader.SetUniform("projection",   static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            objectShader.SetUniform("view",         static_cast<const CMatrix&>(camera.GetViewMatrix()));
            wood.ActivateAndBind(0);

            // Cube 1
            objectShader.SetUniform("model", modelCube1);
            cubeData.DrawArrays(36);

            // Cube 2
            objectShader.SetUniform("model", modelCube2);
            cubeData.DrawArrays(36);

            // Floor
            metal.ActivateAndBind(0);
            objectShader.SetUniform("model", CMatrix{});
            floorData.DrawArrays(6);

            // screen
            CFramebuffer::BindDefault();
            window.SetDepthTest(false);
            window.ClearColor(1.0f, 1.0f, 1.0f, 1.0f);

            screenShader.Use();
            colorBuffer.ActivateAndBind(0);
            quadData.DrawArrays(6);

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
