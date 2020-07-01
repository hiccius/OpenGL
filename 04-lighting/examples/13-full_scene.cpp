#include <iostream>
#include <array>

#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "window.ipp"
#include "shaderprogram.hpp"
#include "vertexdatahandler.ipp"
#include "texture.hpp"
#include "matrixderived.hpp"
#include "camera.hpp"
#include "vertexbufferobject.ipp"

#include "13-atmosphere.hpp"


int main(int argc, char* argv[])
{
    constexpr int screenWidth{800};
    constexpr int screenHeight{600};
    constexpr double aspect{static_cast<double>(screenWidth) / screenHeight};

    auto [exit, atmosphereType] = CommandOption({
        { "desert",  { "Simulates a desert",            Atmosphere::Type::Desert           }},
        { "factory", { "Simulates a factory",           Atmosphere::Type::Factory          }},
        { "horror",  { "Simulates a horror atmosphere", Atmosphere::Type::Horror           }},
        { "lab",     { "Simulates a biochemical lab",   Atmosphere::Type::BiochemicalLab   }}},
        Atmosphere::Type::Default, argc, argv, std::cout);

    if (exit)
    {
        return 0;
    }

    try
    {
        // Init window
        CWindow window;
        CCamera camera{0.1, 2.5, aspect};
        window.SetUp(screenWidth, screenHeight, "LearnOpenGL", true, &camera);
        window.SetMouseControl();

        // Shader programs
        auto objectShaderProgram{CShaderProgram::Build("09-objectshader.vert", "13-objectshader.frag")};
        auto lightShaderProgram{CShaderProgram::Build("lightshader.vert", "13-lightshader.frag")};

        objectShaderProgram.Use();

        CTexture diffuseMap;
        diffuseMap.GenerateTexture("container2.png");
        diffuseMap.SetTextureUnitIndex(0);
        objectShaderProgram.SetUniform("material.diffuse", 0);

        CTexture specularMap;
        specularMap.GenerateTexture("container2_specular.png");
        specularMap.SetTextureUnitIndex(1);
        objectShaderProgram.SetUniform("material.specular", 1);

        objectShaderProgram.SetUniform("material.shininess", 32.0f);

        // Vertex data
        constexpr float vertices[] =
        {
             // positions         // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
        };
        CVertexBufferObject vbo;
        vbo.AddVertexData(vertices);

        CVertexDataHandler objectData;
        objectData.AddVertexBufferObject(&vbo);
        objectData.AddAttribute(3, 8, 0);
        objectData.AddAttribute(3, 8, 3);
        objectData.AddAttribute(2, 8, 6);

        CVertexDataHandler lightData;
        lightData.AddVertexBufferObject(&vbo);
        lightData.AddAttribute(3, 8, 0);

        constexpr std::array<std::array<float, 3>, 10> cubePositions{
        {
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

        // Lighting
        objectShaderProgram.Use();
        Atmosphere atmosphere{Atmosphere::GetAtmosphereData(atmosphereType)};
        atmosphere.SetDirectionalLight(objectShaderProgram);
        atmosphere.SetPointLights(objectShaderProgram);
        atmosphere.SetSpotlight(objectShaderProgram);

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);

            // Render
            atmosphere.ClearBackground(window);
            diffuseMap.ActivateAndBind();
            specularMap.ActivateAndBind();

            objectShaderProgram.Use();
            objectShaderProgram.SetUniform("projection",    static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            objectShaderProgram.SetUniform("view",          static_cast<const CMatrix&>(camera.GetViewMatrix()));
            objectShaderProgram.SetUniform("viewPosition",  camera.GetPositionVector());

            objectShaderProgram.SetUniform("spotLight.position",    camera.GetPositionVector());
            objectShaderProgram.SetUniform("spotLight.direction",   camera.GetDirectionVector());

            for (std::size_t i = 0; i < cubePositions.size(); ++i)
            {
                CMatrix model;
                const auto& [x, y, z] = cubePositions[i];

                model.Translate(x, y, z).Rotate(static_cast<float>(20.0 * i), 1.0f, 0.3f, 0.5f, true);
                objectShaderProgram.SetUniform("model", model);
                objectShaderProgram.SetUniform("normalMatrix", model.Inverse().Transpose());
                objectData.DrawArrays(36);
            }

            lightShaderProgram.Use();
            lightShaderProgram.SetUniform("projection", static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));
            lightShaderProgram.SetUniform("view",       static_cast<const CMatrix&>(camera.GetViewMatrix()));

            for (std::size_t i = 0; i < atmosphere.PointLightsNumber(); ++i)
            {
                const auto& [x, y, z] = atmosphere.GetPointLightPosition(i);
                const auto& [r, g, b] = atmosphere.GetPointLightColor(i);
                lightShaderProgram.SetUniform("model", CMatrix{}.Translate(x, y, z).Scale(0.2f));
                lightShaderProgram.SetUniform("color", r, g, b);
                lightData.DrawArrays(36);
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
