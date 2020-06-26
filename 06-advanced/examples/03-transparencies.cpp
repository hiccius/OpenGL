#include <iostream>

#include "window.hpp"
#include "camera.hpp"
#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "model.hpp"
#include "vertexbufferobject.ipp"
#include "shaderprogram.ipp"


int main()
{
    constexpr int screenHeight{800};
    constexpr int screenWidth{600};
    constexpr double aspect{static_cast<double>(screenHeight) / screenWidth};

    try
    {
        // Init window
        CWindow window;
        CCamera camera{0.1, 2.5, aspect};
        window.SetUp(screenHeight, screenWidth, "LearnOpenGL", &camera);
        window.SetMouseControl();
        window.SetDepthTest(true);

        // Shader programs
        auto shaderProgram{CShaderProgram::Build("shader.vert", "03-shader.frag")};
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

        constexpr float grassVertices[] =
        {
            // positions        // texture coordinates
             0.0f,  0.5f, 0.0f,  0.0f, 1.0f,
             0.0f, -0.5f, 0.0f,  0.0f, 0.0f,
             1.0f, -0.5f, 0.0f,  1.0f, 0.0f,

             0.0f,  0.5f, 0.0f,  0.0f, 1.0f,
             1.0f, -0.5f, 0.0f,  1.0f, 0.0f,
             1.0f,  0.5f, 0.0f,  1.0f, 1.0f
        };
        CVertexBufferObject vboGrass;
        vboGrass.AddVertexData(grassVertices);

        CVertexDataHandler grassData;
        grassData.AddVertexBufferObject(&vboGrass);
        grassData.AddAttribute(3, 5, 0, false);
        grassData.AddAttribute(2, 5, 3, false);

        constexpr std::array<std::array<float, 3>, 5> grassPositions{
        {
            { -1.5f,  0.0f, -0.48f },
            {  1.5f,  0.0f,  0.51f },
            {  0.0f,  0.0f,  0.7f  },
            { -0.3f,  0.0f, -2.3f  },
            {  0.5f,  0.0f, -0.6f  },
        }};

        // Textures
        CTexture marble(CTexture::Type::Diffuse);
        marble.GenerateTexture("marble.jpg");

        CTexture metal(CTexture::Type::Diffuse);
        metal.GenerateTexture("metal.png");

        CTexture grass(CTexture::Type::Diffuse);
        grass.GenerateTexture("grass.png");

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

            // Grass
            for(const auto& position : grassPositions) 
            {
                grass.ActivateAndBind(0);
                shaderProgram.SetUniform("model", CMatrix{}.Translate(position));
                grassData.DrawArrays(6);
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
