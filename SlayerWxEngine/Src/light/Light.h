#ifndef LIGHT_H
#define LIGHT_H
#include "export/export.h"
#include "glm/glm.hpp"
#include <list>

const int maxLenghtSpot = 8;
const int maxLenghtPoint = 15;

class SlayerWxEngine_API Light
{
public:
    int enable = 0;
    glm::vec3 color;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

	Light(glm::vec3 colour, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular);

    void SetColor(glm::vec3 _color);

    void SetADS(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular);
};

class SlayerWxEngine_API PointLight : public Light
{
public:
	glm::vec3 position;
    PointLight(glm::vec3 pos, glm::vec3 colour, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular);
    void SetPosition(glm::vec3 pos);
    ~PointLight();
};
extern std::list<PointLight*>  pointLights;
extern PointLight* Epoint0;

class SlayerWxEngine_API SpotLight : public Light
{
public:
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    SpotLight(glm::vec3 pos, glm::vec3 dir, float _cutOff, float _outerCutOff, float _constant, float _linear, float _quadratic, glm::vec3 colour, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular);
    ~SpotLight();
    void SetPosition(glm::vec3 pos);
    void SetDirection(glm::vec3 dir);
    void SetSpot(SpotLight * s);
};
extern std::list<SpotLight*>  spotLights;
extern SpotLight* spot0;

struct SlayerWxEngine_API DirectionalLight
{
    glm::vec3 direction = glm::vec3(0, 0, 0);
    int enable = 0;
    glm::vec3 color = glm::vec3(0, 0, 0);
    glm::vec3 ambient = glm::vec3(0, 0, 0);
    glm::vec3 diffuse = glm::vec3(0, 0, 0);
    glm::vec3 specular = glm::vec3(0, 0, 0);
};
class SlayerWxEngine_API DirectionalLightning
{

public:
    DirectionalLightning();
    ~DirectionalLightning();
    static DirectionalLight actualDirectionalLight;
    static void SetNewActualLight(DirectionalLight newLight);
};
#endif