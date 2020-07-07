#include <iostream>

#include "window.hpp"
#include "camera.hpp"
#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "glmhelpers.hpp"
#include "model.hpp"
#include "vertexbufferobject.ipp"
#include "shaderprogram.ipp"


int main(int argc, char* argv[])
{
    constexpr int screenWidth{800};
    constexpr int screenHeight{600};
    constexpr double aspect{static_cast<double>(screenWidth) / screenHeight};

    // Command options
    auto [exit, noOrder] = CommandOption("no-order",
                                         "The objects with transparencies are not drawn ordered",
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
        window.SetDepthTest(true);

        // Blending
        SetBlending(BlendingFactor::Alpha, BlendingFactor::AlphaComplement);

        // Shader programs
        auto shaderProgram{CShaderProgram::Build("shader.vert", "04-shader.frag")};
        shaderProgram.Use();
        shaderProgram.SetUniform("diffuse", 0);

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

        constexpr float planeVertices[] =
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

        constexpr float glassVertices[] =
        {
            // positions        // texture coordinates
             0.0f,  0.5f, 0.0f,  0.0f, 1.0f,
             0.0f, -0.5f, 0.0f,  0.0f, 0.0f,
             1.0f, -0.5f, 0.0f,  1.0f, 0.0f,

             0.0f,  0.5f, 0.0f,  0.0f, 1.0f,
             1.0f, -0.5f, 0.0f,  1.0f, 0.0f,
             1.0f,  0.5f, 0.0f,  1.0f, 1.0f
        };
        CVertexBufferObject vboGlass;
        vboGlass.AddVertexData(glassVertices);

        CVertexDataHandler glassData;
        glassData.AddVertexBufferObject(&vboGlass);
        glassData.AddAttribute(3, 5, 0, false);
        glassData.AddAttribute(2, 5, 3, false);

        //std::vector<std::array<float, 3>> glassPositions{
        std::vector<std::array<float, 3>> glassPositions
        {
            { -1.5f,  0.0f, -0.48f },
            {  1.5f,  0.0f,  0.51f },
            {  0.0f,  0.0f,  0.7f  },
            { -0.3f,  0.0f, -2.3f  },
            {  0.5f,  0.0f, -0.6f  },
        };

        // Textures
        CTexture marble(CTexture::Type::Diffuse);
        marble.GenerateTexture("marble.jpg");

        CTexture metal(CTexture::Type::Diffuse);
        metal.GenerateTexture("metal.png");

        CTexture glass(CTexture::Type::Diffuse);
        glass.GenerateTexture("blending_transparent_window.png");

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
            marble.ActivateAndBind(0);

            // Cube 1
            shaderProgram.SetUniform("model", modelCube1);
            cubeData.DrawArrays(36);

            // Cube 2
            shaderProgram.SetUniform("model", modelCube2);
            cubeData.DrawArrays(36);

            // Floor
            metal.ActivateAndBind(0);
            shaderProgram.SetUniform("model", CMatrix{});
            floorData.DrawArrays(6);

            // Windows
            if(!noOrder)
            {
                std::sort(glassPositions.begin(), glassPositions.end(),
                          [&cameraPosition = camera.GetPositionVector()](const auto& aPosition1, const auto& aPosition2)
                          {
                              return DistanceVector3(aPosition1, cameraPosition) > DistanceVector3(aPosition2, cameraPosition);
                          });
            }
            for (const auto& position : glassPositions)
            {
                glass.ActivateAndBind(0);
                shaderProgram.SetUniform("model", CMatrix{}.Translate(position));
                glassData.DrawArrays(6);
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
