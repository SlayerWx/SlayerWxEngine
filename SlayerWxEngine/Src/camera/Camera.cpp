#include "Camera.h"


Camera::Camera()
{
	projection = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	cameraProjection = CameraProjection::perspective;
	yaw = YAW;
	pitch = PITCH;
	UpdateCameraVectors();
}

Camera::~Camera()
{
}
void Camera::UpdateProjection()
{

	switch (cameraProjection)
	{
	default:
	case CameraProjection::perspective:
		//degrees in radians, window resolution, near, far
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.001f, 100.0f);
		break;
	case CameraProjection::ortho:
		//x left, x right, y down, y up, near, far
		projection = glm::ortho(-1.5f, 1.5f, -1.0f, 1.0f, 0.1f, 100.0f);
		break;
	}
}
void Camera::UpdateView()
{
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}


void Camera::SetCameraPosition(float x, float y, float z)
{
	cameraPos.x = x;
	cameraPos.y = y;
	cameraPos.z = z;
}
/// <summary>
///  only work if the CameraType is FREE
/// </summary>
/// <param name="direction"></param>
/// <param name="speed"></param>
/// <param name="deltaTime"></param>
void Camera::CameraMove(CameraDirection direction, float speed, float deltaTime)
{
	if (cameraTypeState == CameraType::free)
	{
		switch (direction)
		{
		case CameraDirection::front:
			cameraPos += (speed * deltaTime) * cameraFront;
			break;
		case CameraDirection::back:
			cameraPos -= (speed * deltaTime) * cameraFront;
			break;
		case CameraDirection::up:
			cameraPos += (speed * deltaTime) * cameraUp;
			break;
		case CameraDirection::down:
			cameraPos -= (speed * deltaTime) * cameraUp;
			break;
		case CameraDirection::left:
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * (speed * deltaTime);
			break;
		case CameraDirection::right:
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * (speed * deltaTime);
			break;
		}
	}

}
void Camera::UpdateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
	// also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(cameraFront, cameraUp));  // normalize the vectors, because their length gets 
									//closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, cameraFront));
}
void Camera::CameraRotate(float speedX, float speedY)
{
	if (cameraTypeState == CameraType::ThridPerson)
	{
		//speedX *= -1;
		speedY *= -1;
	}
		yaw += speedX;
		pitch -= speedY;
		if (pitch >= 89.1f)
			pitch = -89.0f;
		if (pitch < -89.1f)
			pitch = 89.0f;
	
	UpdateCameraVectors();

}

/// <summary>
/// if want use the camera in free format then objPosReference dont is used and distanceFromReferene is used in thirdPerson and Isometric
/// </summary>
/// <param name="type"></param>
/// <param name="objPosReference"></param>
void Camera::CameraFollowObj(CameraType type, glm::vec3 objPosReference, float distanceFromReferene)
{
		cameraTypeState = type;
		switch (type)
		{
		case CameraType::free:
			break;
		case CameraType::FirstPerson:
			//objPosReference += glm::vec3(0,0,5);
			cameraPos = objPosReference;
			break;
		case CameraType::ThridPerson:
			glm::vec3 aux = cameraFront;
			aux.x *= -1;
			aux.y *= -1;
			aux.z *= -1;
			cameraPos = objPosReference + aux * distanceFromReferene;
			break;
		case CameraType::isometric:
			break;
		}
}
