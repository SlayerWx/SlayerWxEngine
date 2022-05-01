#ifndef CAMERA_H
#define CAMERA_H
#include "export/export.h"
#include "glm/glm.hpp"
#include"glm/gtc/type_ptr.hpp"
enum class CameraDirection
{
	left, right, up, down, front, back
};
enum class CameraProjection
{
	perspective, ortho
};
class SlayerWxEngine_API Camera
{
public:
	Camera();
	~Camera();

	void UpdateProjection();
	void UpdateView();
	void SetCameraPosition(float x, float y, float z);
	void CameraMove(CameraDirection direction, float speed, float deltaTime);
	glm::mat4 projection; //size/count of pixel inside the viewport
	glm::mat4 view; //move the "camera" but really move all object in the inverse
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	CameraProjection cameraProjection;
	void UpdateCameraVectors();
	void CameraRotate(float speedX, float speedY);
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	float yaw = 0.0f;
	float pitch = 0.0f;
	glm::vec3 up = glm::vec3();
	glm::vec3 right = glm::vec3();

private:

};
#endif 