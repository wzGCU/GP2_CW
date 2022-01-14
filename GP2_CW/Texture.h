#pragma once
#include <string>
#include <GL\glew.h>

class Texture
{
public:

	Texture(const std::string& fileName);
	~Texture();

	void BindTexture(unsigned int unit); 

protected:
private:

	GLuint textureHandle;
};

