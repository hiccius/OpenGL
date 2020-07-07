#include <iostream>

#include "window.hpp"
#include "camera.hpp"
#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "model.hpp"
#include "vertexbufferobject.ipp"
#include "shaderprogram.ipp"


int main(int argc, char* argv[])
{
    constexpr int screenWidth{800};
    constexpr int screenHeight{600};
    constexpr double aspect{static_cast<double>(screenWidth) / screenHeight};

    // Command options
    auto [exit, mergeBorders] = CommandOption("merge-borders",
                                              "The borders around the two containers appear merged",
                                              argc, argv, std::cout);
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
        window.SetStencilTest(true);

        // Shader programs
        auto shader{CShaderProgram::Build("shader.vert", "02-shader.frag")};
        auto shaderColor{CShaderProgram::Build("shader.vert", "02-shader_color.frag")};
        shader.Use();
        shader.SetUniform("diffuse", 0);

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
        CMatrix modelBigCube1{modelCube1};
        modelBigCube1.Scale(1.1f);

        CMatrix modelCube2;
        modelCube2.Translate(2.0f, 0.0f, 0.0f);
        CMatrix modelBigCube2{modelCube2};
        modelBigCube2.Scale(1.1f);

        float planeVertices[] =
        {
            // positions          // texture coordinates
             5.0f, -0.51f,  5.0f,  2.0f, 0.0f,
            -5.0f, -0.51f,  5.0f,  0.0f, 0.0f,
            -5.0f, -0.51f, -5.0f,  0.0f, 2.0f,

             5.0f, -0.51f,  5.0f,  2.0f, 0.0f,
            -5.0f, -0.51f, -5.0f,  0.0f, 2.0f,
             5.0f, -0.51f, -5.0f,  2.0f, 2.0f
        };
        CVertexBufferObject vboPlane;
        vboPlane.AddVertexData(planeVertices);

        CVertexDataHandler floorData;
        floorData.AddVertexBufferObject(&vboPlane);
        floorData.AddAttribute(3, 5, 0, false);
        floorData.AddAttribute(2, 5, 3, false);

        // Textures
        CTexture marble(CTexture::Type::Diffuse);
        marble.GenerateTexture("marble.jpg");

        CTexture metal(CTexture::Type::Diffuse);
        metal.GenerateTexture("metal.png");

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);

            // Render
            window.SetStencilMask(0xFF);
            window.SetStencilUpdate(StencilAction::Keep, StencilAction::Keep, StencilAction::Replace);
            window.SetDepthTest(true);
            window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            shader.Use();
            shader.SetUniform("projection",    static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            shader.SetUniform("view",          static_cast<const CMatrix&>(camera.GetViewMatrix()));

            // Floor
            window.SetStencilMask(0x00);
            window.SetStencilCondition(StencilCondition::Always, 1, 0xFF);
            window.SetDepthBufferWrite(false);
            shader.SetUniform("model", CMatrix{});
            metal.ActivateAndBind(0);
            floorData.DrawArrays(6);
            window.SetDepthBufferWrite(true);

            if (mergeBorders)
            {
                // Cube 1
                window.SetStencilMask(0xFF);
                marble.ActivateAndBind(0);
                shader.SetUniform("model", modelCube1);
                cubeData.DrawArrays(36);

                // Cube 2
                shader.Use();
                shader.SetUniform("model", modelCube2);
                cubeData.DrawArrays(36);

                // Borders
                shaderColor.Use();
                shaderColor.SetUniform("projection",    static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
                shaderColor.SetUniform("view",          static_cast<const CMatrix&>(camera.GetViewMatrix()));

                window.SetStencilCondition(StencilCondition::NotEqual, 1, 0xFF);
                window.SetStencilMask(0x00);
                window.SetDepthTest(false);
                shaderColor.SetUniform("model", modelBigCube1);
                cubeData.DrawArrays(36);

                shaderColor.SetUniform("model", modelBigCube2);
                cubeData.DrawArrays(36);
            }
            else
            {
                // Cube 1 and border
                marble.ActivateAndBind(0);
                window.SetStencilMask(0xFF);
                shader.SetUniform("model", modelCube1);
                cubeData.DrawArrays(36);

                shaderColor.Use();
                shaderColor.SetUniform("projection",    static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
                shaderColor.SetUniform("view",          static_cast<const CMatrix&>(camera.GetViewMatrix()));

                //window.SetDepthTest(false);
                window.SetStencilCondition(StencilCondition::NotEqual, 1, 0xFF);
                window.SetStencilMask(0x00);
                shaderColor.SetUniform("model", modelBigCube1);
                cubeData.DrawArrays(36);

                // Cube 2 and border
                window.SetDepthTest(true);
                window.SetStencilMask(0xFF);
                window.ClearStencilBuffer();
                window.SetStencilCondition(StencilCondition::Always, 1, 0xFF);
                shader.Use();
                shader.SetUniform("model", modelCube2);
                cubeData.DrawArrays(36);

                window.SetStencilCondition(StencilCondition::NotEqual, 1, 0xFF);
                window.SetStencilMask(0x00);
                shaderColor.Use();
                shaderColor.SetUniform("model", modelBigCube2);
                cubeData.DrawArrays(36);
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
