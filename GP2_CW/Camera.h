#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
public:

	Camera()
	{
	}


	/* Function to set thecamera properites, takes in a vector 3 postion, 
	a float for the field of view, a float for the aspect ratio, and 
	floats for the near and far clipping planes.  */

	void InitialiseCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->pos = pos;
		this->zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
		this->yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}
	
	glm::vec3 GetCameraPosition()
	{
		return this->pos;
	}


	/* Function for projection matrix */

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + zAxis, yAxis);
	}


	/* Functions for moving camera on X and Z axis */

	void MoveCameraZ(float amount)
	{
		pos += zAxis * amount;
	}

	void MoveCameraX(float amount)
	{
		pos += glm::cross(yAxis, zAxis) * amount;
	}

	/* Function to angle the camera from more top down to give the 3D view */
	void Pitch(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(yAxis, zAxis));

		zAxis = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(zAxis, 0.0)));
		yAxis = glm::normalize(glm::cross(zAxis, right));
	}

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 zAxis;
	glm::vec3 yAxis;
};


