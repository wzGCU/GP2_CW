#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class Display
{
public:
	/* Constructor and deconstructor */
	Display();
	~Display();

	/* SDL Functions */
	void bufferOpenGL(); //function to call the window to update with openGL rendering
	void resetDisplay(float r, float g, float b, float a); //function that clears the display to set colour
	void initialiseDisplay(); //initialise the SDL library

	/* A pointer to the SDL WINDOW */
	SDL_Window* window; 

	/* Functions to get the Screen Width and Height (that will be passed with the width and height floats */
	float getScreenWidth();
	float getScreenHeight();

private:

	/* Function for error if there is a cause for it to appear */
	void outError(std::string error);
	
	/* A variable that helds the OpenGL context */
	SDL_GLContext oglContext; 
	
	/* Two floats used for screen width and height */
	float width;
	float height;
};

