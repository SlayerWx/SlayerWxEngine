#include "BspPlane.h"

BSPPlane::BSPPlane() :Cube()
{
}
BSPPlane::BSPPlane(glm::vec3 inNormal) : Cube("plane","")
{
	normal = inNormal;
	distance = -glm::dot(normal, GetPosition());
}

BSPPlane::~BSPPlane()
{
}

float BSPPlane::GetDistanceToPoint(glm::vec3 point)
{
    // distancia positiva si el punto esta frente al plano
    // distancia negativa si el punto esta espaldas al plano

    glm::vec3 aux;
    aux.x = normal.x * 2;
    aux.y = normal.y * 2;
    aux.z = normal.z * 2;

    return  (glm::dot(point - GetPosition(), normal) + distance) / (aux.x + aux.y + aux.z);
   
}

bool BSPPlane::FrontPlane(glm::vec3 point)
{
    if (GetDistanceToPoint(point) > 0.0f)
        return true;
    return false;
}
