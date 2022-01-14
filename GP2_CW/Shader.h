#pragma once
#include <string>
#include <GL\glew.h>
#include "transform.h"
#include "Camera.h"

class Shader
{
public:

	/* Constructor and deconstrucor */
	Shader();
	~Shader();

	void BindTexture(); //Program as part of rendering state
	void InitialiseShader(const std::string& filename); //Create program, vertex and frament shaders
	void Update(const Transform& transform, const Camera& camera); //Update the shader view

	GLuint Shader::CreateShader(const std::string& text, unsigned int type); //Create shader based on specified type
	std::string Shader::LoadShaderFromFile(const std::string& fileName); //Load shader from file
	void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage); //Out error

private:

	static const unsigned int NUM_SHADERS = 2; 

	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	GLuint shaderProgram; //Helds the shader program
	GLuint shaders[NUM_SHADERS]; //Shaders Array
	GLuint uniforms[NUM_UNIFORMS]; //Uniform Variables
};
