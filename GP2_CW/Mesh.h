#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

struct Vertex
{
public:
	// Constructor of vertexes
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	// Getters
	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

struct Sphere
{
public:

	Sphere() { }

	/* Getters */
	glm::vec3 GetPos() { return pos; }
	float GetRadius() { return radius; }

	/* Setters */
	void SetPos(glm::vec3 pos) { this->pos = pos; }
	void SetRadius(float radius) { this->radius = radius; }

private:
	glm::vec3 pos;
	float radius;
};

class Mesh
{
public:

	/* Constructor and deconstructor */
	Mesh();
	~Mesh();

	void InitialiseModel(const IndexedModel& model); //Initialise a model
	void LoadModelFromFile(const std::string& filename); //Load model from file
	void RenderMesh(); //render mesh
	void UpdateCollisionData(glm::vec3 pos, float radius); //update data used for collision

	/* Getters for collisions */
	glm::vec3 GetCollisionPosition() { return meshCollisionSphere.GetPos(); }
	float GetCollisionRadius() { return meshCollisionSphere.GetRadius(); }

private:

	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	Sphere meshCollisionSphere;
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; 
	unsigned int drawCount; 
};