#include <iostream>
#include <random>

#include "window.hpp"
#include "camera.hpp"
#include "helpers.hpp"
#include "gladhelpers.hpp"
#include "model.hpp"
#include "vertexbufferobject.ipp"
#include "shaderprogram.ipp"
#include "uniformbufferobject.ipp"

std::vector<CMatrix> GenerateRockModels(unsigned int aNumInstances)
{
    std::vector<CMatrix> rockModels;
    float sizeFactor = std::max(std::floor(std::log10(aNumInstances)), 1.0);
    float radius = sizeFactor * 40;
    float offset = sizeFactor * std::sqrt(10);

    std::default_random_engine generator{std::random_device{}()};
    std::uniform_real_distribution uniformDistributionTranslate{-offset, offset};
    std::uniform_real_distribution uniformDistributionScale{0.05f, 0.25f};
    std::uniform_int_distribution uniformDistributionRotate{0, 360};

    for (unsigned int i = 0; i < aNumInstances; ++i)
    {
        CMatrix rockModel{};
        float angle = ToRadians(i * 360.0f / aNumInstances);
        float x = std::sin(angle) * radius + uniformDistributionTranslate(generator);
        float y = 0.4f * uniformDistributionTranslate(generator);
        float z = std::cos(angle) * radius + uniformDistributionTranslate(generator);

        rockModel.Translate(x, y, z);
        rockModel.Scale(uniformDistributionScale(generator));
        rockModel.Rotate(uniformDistributionRotate(generator), 0.4f, 0.6f, 0.8f, true);

        rockModels.push_back(rockModel);
    }

    return rockModels;
}


int main(int argc, char* argv[])
{
    constexpr int screenWidth{800};
    constexpr int screenHeight{600};
    constexpr double aspect{static_cast<double>(screenWidth) / screenHeight};

    // Command options
    auto [exit, instancing, args] = CommandOptionArgs("instancing",
                                                      "Uses instanced arrays to draw the asteroids",
                                                      argc, argv, std::cout,
                                                      StringViewArrray<1>{"numAsteroids"});
    if (exit)
    {
        return 0;
    }

    // Number of asteroids to draw
    unsigned int numAsteroids;
    try
    {
        numAsteroids = std::stoul(std::string{args[0]});
    }
    catch(const std::exception& exc)
    {
        std::cerr << "'" << args[0] << "' cannot be converted to an integer (" << exc.what() << ")\n";
        return -1;
    }

    try
    {
        // Init window
        CWindow window;
        CCamera camera{0.1, 20.0, aspect};
        camera.SetFarPlane(1000.0f);
        window.SetUp(screenWidth, screenHeight, "LearnOpenGL", &camera);
        window.SetDepthTest(true);
        window.SetMouseControl();

        // Shader programs
        auto objectShader{CShaderProgram::Build("10-shader.vert", "10-shader.frag")};
        auto asteroidShader{CShaderProgram::Build(instancing ? "10-asteroid.vert" : "10-shader.vert", "10-shader.frag")};

        CUniformBufferObject ubo;
        ubo.Allocate(2 * CMatrix::Size());
        ubo.SetBindingPoint(0);

        objectShader.SetBindingPoint("Matrices", 0);
        asteroidShader.SetBindingPoint("Matrices", 0);

        // Planet data
        CModel planet{"planet/planet.obj"};
        objectShader.Use();
        planet.SetTextureUnitsUniforms(objectShader);
        CMatrix planetModel{};
        planetModel.Translate(0.0f, -3.0f, 0.0f).Scale(4.0f);

        // Asteroids data
        CModel rock{"rock/rock.obj"};
        asteroidShader.Use();
        rock.SetTextureUnitsUniforms(objectShader);

        auto rockModels{GenerateRockModels(numAsteroids)};

        CVertexBufferObject vboInstances;
        if (instancing)
        {
            vboInstances.AddVertexData(rockModels);
            for(auto& mesh : rock.GetMeshes())
            {
                mesh.BindVAO();
                mesh.SetAttributeDivisor(4, CMatrix::Size(), 0, 1);
                mesh.SetAttributeDivisor(4, CMatrix::Size(), 1 * CMatrix::Size() / 4, 1);
                mesh.SetAttributeDivisor(4, CMatrix::Size(), 2 * CMatrix::Size() / 4, 1);
                mesh.SetAttributeDivisor(4, CMatrix::Size(), 3 * CMatrix::Size() / 4, 1);
            }
        }

        // Render loop
        while (window.IsOpen())
        {
            // Poll keys
            window.UpdateDeltaFrames();
            window.PollCloseKey(Key::Escape);
            window.PollMovementKeys(Key::W, Key::A, Key::S, Key::D);
            window.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            ubo.SetData(static_cast<const CMatrix&>(camera.GetViewMatrix()),
                        static_cast<const CMatrix&>(camera.GetPerspectiveMatrix()));

            // Render data
            objectShader.Use();
            objectShader.SetUniform("model", planetModel);
            planet.Draw();

            asteroidShader.Use();
            if (instancing)
            {
                rock.Draw(numAsteroids);
            }
            else
            {
                for (auto& model : rockModels)
                {
                    objectShader.SetUniform("model", model);
                    rock.Draw();
                }
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
