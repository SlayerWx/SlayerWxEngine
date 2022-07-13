#include "Light.h"
std::list<PointLight*>  pointLights;
std::list<SpotLight*>  spotLights;
DirectionalLight DirectionalLightning::actualDirectionalLight;
SpotLight* spot0;
PointLight* Epoint0;
Light::Light(glm::vec3 colour, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular)
{
	enable = 1;
	color = colour;
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
}

void Light::SetColor(glm::vec3 _color)
{
	color = _color;
}

void Light::SetADS(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular)
{
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
}
PointLight::PointLight(glm::vec3 pos, glm::vec3 colour, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular) 
	:Light(colour,_ambient,_diffuse,_specular)
{
	position = pos;
	if (pointLights.size() < maxLenghtPoint)
	{
		pointLights.push_back(this);
	}
}

void PointLight::SetPosition(glm::vec3 pos)
{
	position = pos;
}

PointLight::~PointLight()
{
	pointLights.remove(this);
}

void PointLight::SetPointLight(PointLight* p)
{
	Epoint0 = p;
}

SpotLight::SpotLight(glm::vec3 pos, glm::vec3 dir,float _cutOff,float _outerCutOff, float _constant,float _linear,float _quadratic,
	glm::vec3 colour, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular)
	: Light(colour, _ambient, _diffuse, _specular)
{
	position = pos;
	direction = dir;
	cutOff = _cutOff;
	outerCutOff = _outerCutOff;
	constant = _constant;
	linear = _linear;
	quadratic = _quadratic;
	if (spotLights.size() < maxLenghtSpot)
	{
		spotLights.push_back(this);
	}
}

SpotLight::~SpotLight()
{
	spotLights.remove(this);
}

void SpotLight::SetPosition(glm::vec3 pos)
{
	position = pos;
}

void SpotLight::SetDirection(glm::vec3 dir)
{
	direction = dir;
}

void SpotLight::SetSpot(SpotLight* s)
{
	spot0 = s;
}

DirectionalLightning::DirectionalLightning()
{
}

DirectionalLightning::~DirectionalLightning()
{
}

void DirectionalLightning::SetNewActualLight(DirectionalLight newLight)
{
	actualDirectionalLight = newLight;
}

