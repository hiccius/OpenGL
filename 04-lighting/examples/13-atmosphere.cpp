#include "13-atmosphere.hpp"

#include "shaderprogram.hpp"
#include "window.hpp"
#include "helpers.hpp"


Atmosphere::Data Atmosphere::GetAtmosphereData(Atmosphere::Type type)
{
    switch (type)
    {
        case Type::Desert:
        {
            return Data
            {
                .background = {0.75f, 0.52f, 0.3f},
                .directionalLight =
                {
                    .ambient = {0.3f, 0.24f, 0.14f},
                    .diffuse = {0.7f, 0.42f, 0.26f},
                    .specular = {0.5f, 0.5f, 0.5f}
                },
                .pointLights =
                {{
                    {
                        .position = {1.0f, 0.6f, 0.0f},
                        .color = {1.0f, 0.6f, 0.0f},
                        .linearAttenuation = 0.09f,
                        .quadraticAttenuation = 0.032f
                    },
                    {
                        .position = {2.3f, -3.3f, -4.0f},
                        .color = {1.0f, 0.0f, 0.0f},
                        .linearAttenuation = 0.09f,
                        .quadraticAttenuation = 0.032f
                    },
                    {
                        .position = {-4.0f, 2.0f, -12.0f},
                        .color = {1.0f, 1.0f, 0.0f},
                        .linearAttenuation = 0.09f,
                        .quadraticAttenuation = 0.032f
                    },
                    {
                        .position = {0.0f, 0.0f, -3.0f},
                        .color = {0.2f, 0.2f, 1.0f},
                        .linearAttenuation = 0.09f,
                        .quadraticAttenuation = 0.32f
                    }
                }},
                .spotlight =
                {
                    .color = {1.0f, 1.0f, 1.0f},
                    .cutOffAngles = {10.0f, 12.5f},
                    .linearAttenuation = 0.09f,
                    .quadraticAttenuation = 0.032f
                }
            };
        }
        case Type::Factory:
        {
            return Data
            {
                .background = {0.1f, 0.1f, 0.1f},
                .directionalLight =
                {
                    .ambient = {0.05f, 0.05f, 0.1f},
                    .diffuse = {0.2f, 0.2f, 0.7f},
                    .specular = {0.7f, 0.7f, 0.7f}
                },
                .pointLights =
                {{
                    {
                        .position = {0.7f, 0.2f, 2.0f},
                        .color = {0.2f, 0.2f, 0.6f},
                        .linearAttenuation = 0.09f,
                        .quadraticAttenuation = 0.032f
                    },
                    {
                        .position = {2.3f, -3.3f, -4.0f},
                        .color = {0.3f, 0.3f, 0.7f},
                        .linearAttenuation = 0.09f,
                        .quadraticAttenuation = 0.032f
                    },
                    {
                        .position = {-4.0f, 2.0f, -12.0f},
                        .color = {0.0f, 0.0f, 0.3f},
                        .linearAttenuation = 0.09f,
                        .quadraticAttenuation = 0.032f
                    },
                    {
                        .position = {0.0f, 0.0f, -3.0f},
                        .color = {0.4f, 0.4f, 0.4f},
                        .linearAttenuation = 0.09f,
                        .quadraticAttenuation = 0.32f
                    }
                }},
                .spotlight =
                {
                    .color = {0.8f, 0.8f, 0.0f},
                    .cutOffAngles = {12.5f, 13.0f},
                    .linearAttenuation = 0.09f,
                    .quadraticAttenuation = 0.032f
                }
            };
        }
        case Type::Horror:
        {
            return Data
            {
                .background = {0.0f, 0.0f, 0.0f},
                .directionalLight =
                {
                    .ambient = {0.0f, 0.0f, 0.0f},
                    .diffuse = {0.05f, 0.05f, 0.05f},
                    .specular = {0.2f, 0.2f, 0.2f}
                },
                .pointLights =
                {{
                    {
                        .position = {0.7f, 0.2f, 2.0f},
                        .color = {0.1f, 0.1f, 0.1f},
                        .linearAttenuation = 0.14f,
                        .quadraticAttenuation = 0.07f
                    },
                    {
                        .position = {2.3f, -3.3f, -4.0f},
                        .color = {0.1f, 0.1f, 0.1f},
                        .linearAttenuation = 0.14f,
                        .quadraticAttenuation = 0.07f
                    },
                    {
                        .position = {-4.0f, 2.0f, -12.0f},
                        .color = {0.1f, 0.1f, 0.1f},
                        .linearAttenuation = 0.14f,
                        .quadraticAttenuation = 0.07f
                    },
                    {
                        .position = {0.0f, 0.0f, -3.0f},
                        .color = {0.5f, 0.1f, 0.1f},
                        .linearAttenuation = 0.10f,
                        .quadraticAttenuation = 0.05f
                    }
                }},
                .spotlight =
                {
                    .color = {1.0f, 1.0f, 1.0f},
                    .cutOffAngles = {10.0f, 15.0f},
                    .linearAttenuation = 0.09f,
                    .quadraticAttenuation = 0.032f
                }
            };
        }
        case Type::BiochemicalLab:
        {
            return Data
            {
                .background = {0.9f, 0.9f, 0.9f},
                .directionalLight =
                {
                    .ambient = {0.5f, 0.5f, 0.5f},
                    .diffuse = {1.0f, 1.0f, 1.0f},
                    .specular = {1.0f, 1.0f, 1.0f}
                },
                .pointLights =
                {{
                    {
                        .position = {0.7f, 0.2f, 2.0f},
                        .color = {0.3f, 0.8f, 0.1f},
                        .linearAttenuation = 0.07f,
                        .quadraticAttenuation = 0.017f
                    },
                    {
                        .position = {2.3f, -3.3f, -4.0f},
                        .color = {0.3f, 0.8f, 0.1f},
                        .linearAttenuation = 0.07f,
                        .quadraticAttenuation = 0.017f
                    },
                    {
                        .position = {-4.0f, 2.0f, -12.0f},
                        .color = {0.3f, 0.8f, 0.1f},
                        .linearAttenuation = 0.07f,
                        .quadraticAttenuation = 0.017f
                    },
                    {
                        .position = {0.0f, 0.0f, -3.0f},
                        .color = {0.3f, 0.8f, 0.1f},
                        .linearAttenuation = 0.07f,
                        .quadraticAttenuation = 0.017f
                    }
                }},
                .spotlight =
                {
                    .color = {0.0f, 1.0f, 0.0f},
                    .cutOffAngles = {7.0f, 10.0f},
                    .linearAttenuation = 0.07f,
                    .quadraticAttenuation = 0.017f
                }
            };
        }
        default:
        {
            return Data
            {
                .background = {0.1f, 0.1f, 0.1f},
                .directionalLight =
                {
                    .ambient = {0.05f, 0.05f, 0.05f},
                    .diffuse = {0.4f, 0.4f, 0.4f},
                    .specular = {0.5f, 0.5f, 0.5f}
                },
                .pointLights =
                {{
                    {
                        .position = {0.7f, 0.2f, 2.0f},
                        .color = {0.8f, 0.8f, 0.8f},
                        .linearAttenuation = 0.09f,
                        .quadraticAttenuation = 0.032f
                    },
                    {
                        .position = {2.3f, -3.3f, -4.0f},
                        .color = {0.8f, 0.8f, 0.8f},
                        .linearAttenuation = 0.09f,
                        .quadraticAttenuation = 0.032f
                    },
                    {
                        .position = {-4.0f, 2.0f, -12.0f},
                        .color = {0.8f, 0.8f, 0.8f},
                        .linearAttenuation = 0.09f,
                        .quadraticAttenuation = 0.032f
                    },
                    {
                        .position = {0.0f, 0.0f, -3.0f},
                        .color = {0.8f, 0.8f, 0.8f},
                        .linearAttenuation = 0.09f,
                        .quadraticAttenuation = 0.032f
                    }
                }},
                .spotlight =
                {
                    .color = {0.8f, 0.8f, 0.8f},
                    .cutOffAngles = {5.0f, 10.0f},
                    .linearAttenuation = 0.09f,
                    .quadraticAttenuation = 0.032f
                }
            };
        }
    }
}

Atmosphere::Atmosphere(Atmosphere::Data&& data)
    : _data{data}
{}

void Atmosphere::ClearBackground(CWindow& window)
{
    const auto& [colorR, colorG, colorB] = _data.background;
    window.ClearColor(colorR, colorG, colorB, 1.0f);
}

void Atmosphere::SetDirectionalLight(CShaderProgram& shaderProgram)
{
    const auto& directionalLight = _data.directionalLight;
    shaderProgram.SetUniform("directionalLight.direction", -0.2f,  -1.0f,  -0.3f);
    shaderProgram.SetUniform("directionalLight.ambient",  directionalLight.ambient);
    shaderProgram.SetUniform("directionalLight.diffuse",  directionalLight.diffuse);
    shaderProgram.SetUniform("directionalLight.specular", directionalLight.specular);
}

void Atmosphere::SetPointLights(CShaderProgram& shaderProgram)
{
    for (std::size_t i = 0; i < _data.pointLights.size(); ++i)
    {
        const auto& pointLight = _data.pointLights[i];
        std::string pointLightName{"pointLights[" + std::to_string(i) + "]"};
        shaderProgram.SetUniform(pointLightName + ".position",      pointLight.position);
        shaderProgram.SetUniform(pointLightName + ".ambient",       pointLight.color[0] * 0.01f,
                                                                    pointLight.color[1] * 0.01f,
                                                                    pointLight.color[2] * 0.01f);
        shaderProgram.SetUniform(pointLightName + ".diffuse",       pointLight.color);
        shaderProgram.SetUniform(pointLightName + ".specular",      pointLight.color);
        shaderProgram.SetUniform(pointLightName + ".constantAtt",   1.0f);
        shaderProgram.SetUniform(pointLightName + ".linearAtt",     pointLight.linearAttenuation);
        shaderProgram.SetUniform(pointLightName + ".quadraticAtt",  pointLight.quadraticAttenuation);
    }
}

void Atmosphere::SetSpotlight(CShaderProgram& shaderProgram)
{
    const auto& spotlight = _data.spotlight;
    shaderProgram.SetUniform("spotLight.cosCutOffAngle",       std::cos(ToRadians(spotlight.cutOffAngles[0])));
    shaderProgram.SetUniform("spotLight.cosOuterCutOffAngle",  std::cos(ToRadians(spotlight.cutOffAngles[1])));
    shaderProgram.SetUniform("spotLight.ambient",              0.0f, 0.0f, 0.0f);
    shaderProgram.SetUniform("spotLight.diffuse",              spotlight.color);
    shaderProgram.SetUniform("spotLight.specular",             spotlight.color);
    shaderProgram.SetUniform("spotLight.constantAtt",          1.0f);
    shaderProgram.SetUniform("spotLight.linearAtt",            spotlight.linearAttenuation);
    shaderProgram.SetUniform("spotLight.quadraticAtt",         spotlight.quadraticAttenuation);
}

std::size_t Atmosphere::PointLightsNumber()
{
    return _data.pointLights.size();
}

const std::array<float, 3>& Atmosphere::GetPointLightPosition(int i) const
{
    return _data.pointLights[i].position;
}

const std::array<float, 3>& Atmosphere::GetPointLightColor(int i) const
{
    return _data.pointLights[i].color;
}
