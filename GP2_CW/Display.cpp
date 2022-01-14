#include "Display.h"


/* Constructor */

Display::Display()
{
	/* Setting the window to equal to a nullpointer for case of debugging (null access violation) */
	window = nullptr; 

	/* Setting the resolution of the application window, set it to 800x600 for the purpose of nostalgia :) */
	width = 800.0f;
	height = 600.0f; 
}


/* Deconstructor */

Display::~Display()
{
	/* Clearing commands for the deconstructor */
	SDL_GL_DeleteContext(oglContext); // Deleting OpenGL Context
	SDL_DestroyWindow(window); // Deleting the window
	SDL_Quit(); 
}


/* Defined getters */

float Display::getScreenWidth() { return width; } 
float Display::getScreenHeight() { return height; }


/* A function displaying error that takes in a string as argument, 
prints to the screen the text to press a key and takes a key stroke */

void Display::outError(std::string error)
{
	std::cout << error << std::endl; //getting the error
	std::cout << "Press a key to Quit";
	int a;
	std::cin >> a;
	SDL_Quit();
}


/* Function that swaps the buffer of the window to the OpenGL render */

void Display::bufferOpenGL()
{
	SDL_GL_SwapWindow(window); 
}


/* Function that clears the display to set colour.
the passed floats should be between 0 and 1 (256 -> 1.0f) */

void Display::resetDisplay(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a); //defines the colour to clear the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the buffers
}


/* Function to initialize SDL Library */

void Display::initialiseDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); 

	/* Setting minimum number of bits to generate colours */
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); 
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

	/* Setting up the double and depth buffer (for z axis)*/
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);   

	window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)width, (int)height, SDL_WINDOW_OPENGL);
	oglContext = SDL_GL_CreateContext(window);
	GLenum glStatus = glewInit();

	/* Functions to out the proper error at each stage */
	if (window == nullptr)
	{
		outError("Failed to create the window.");
	}

	if (oglContext == nullptr)
	{
		outError("Failed to create the OpemGL context.");
	}

	if (glStatus != GLEW_OK)
	{
		outError("Failed to initialize the GLEW. GLEW is not OK :(");
	}

	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}