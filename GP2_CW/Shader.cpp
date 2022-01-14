#include "Shader.h"
#include <iostream>
#include <fstream>


/* Constructor */
Shader::Shader() {}


/* Deconstructor , which detatches and deletes each shader and then deletes the program*/

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(shaderProgram, shaders[i]); 
		glDeleteShader(shaders[i]); 
	}
	glDeleteProgram(shaderProgram); 
}


/* Function that installs the program object as part of rendering state */

void Shader::BindTexture()
{
	glUseProgram(shaderProgram);
}


/* Function that initialises shaders - creating program, vertex and frament shaders */

void Shader::InitialiseShader(const std::string& filename)
{
	shaderProgram = glCreateProgram(); 
	shaders[0] = CreateShader(LoadShaderFromFile("..\\res\\shader.vert"), GL_VERTEX_SHADER); 
	shaders[1] = CreateShader(LoadShaderFromFile("..\\res\\shader.frag"), GL_FRAGMENT_SHADER); 

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(shaderProgram, shaders[i]);  
	}

	glBindAttribLocation(shaderProgram, 0, "position"); 
	glBindAttribLocation(shaderProgram, 1, "texCoord");
	glBindAttribLocation(shaderProgram, 2, "normals");

	// Try Linking program
	glLinkProgram(shaderProgram); 
	CheckShaderError(shaderProgram, GL_LINK_STATUS, true, "Failed to link shader program."); 

	// Check if program is valid
	glValidateProgram(shaderProgram); 
	CheckShaderError(shaderProgram, GL_VALIDATE_STATUS, true, "Shader program is not valid.");

	uniforms[TRANSFORM_U] = glGetUniformLocation(shaderProgram, "transform"); 
}


/* Update the shader view */

void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}


/* Function that creates shader based on specified type */

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type); 

	if (shader == 0) 
		std::cerr << "Failed to create " << type << std::endl;

	const GLchar* stringSource[1]; 
	stringSource[0] = text.c_str(); // Convert strings into list of c-strings
	GLint lengths[1];
	lengths[0] = text.length();

	/* Send source code to OpenGL and get it to compile code of shader */
	glShaderSource(shader, 1, stringSource, lengths); 
	glCompileShader(shader); 

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Failed compiling shader."); 

	return shader;
}


/* Function to load the shader from file */

std::string Shader::LoadShaderFromFile(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}


/* Function to check if shaders are working as they should if not then outs the error */

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

