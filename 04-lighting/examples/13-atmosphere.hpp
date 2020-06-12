#ifndef ATMOSPHERE_HPP
#define ATMOSPHERE_HPP

#include <array>

class CWindow;
class CShaderProgram;

class Atmosphere
{
public:
    enum class Type
    {
        Desert, Factory, Horror, BiochemicalLab, Default
    };

    struct Data
    {
        struct DirectionalLight
        {
            std::array<float, 3> ambient;
            std::array<float, 3> diffuse;
            std::array<float, 3> specular;
            float linearAttenuation;
            float quadraticAttenuation;
        };

        struct PointLight
        {
            std::array<float, 3> position;
            std::array<float, 3> color;
            float linearAttenuation;
            float quadraticAttenuation;
        };

        struct Spotlight
        {
            std::array<float, 3> color;
            std::array<float, 2> cutOffAngles;
            float linearAttenuation;
            float quadraticAttenuation;
        };

        std::array<float, 3>       background;
        DirectionalLight           directionalLight;
        std::array<PointLight, 4>  pointLights;
        Spotlight                  spotlight;
    };

    static Data GetAtmosphereData(Type type);

    Atmosphere(Data&& data);

    void ClearBackground(CWindow& window);
    void SetDirectionalLight(CShaderProgram& shaderProgram);
    void SetPointLights(CShaderProgram& shaderProgram);
    void SetSpotlight(CShaderProgram& shaderProgram);

    std::size_t PointLightsNumber();
    const std::array<float, 3>& GetPointLightPosition(int i) const;
    const std::array<float, 3>& GetPointLightColor(int i) const;

private:
    Data _data;
};

#endif // ATMOSPHERE_HPP
