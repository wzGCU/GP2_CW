#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <SDL/SDL_mixer.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "AudioRelated.h"


enum class GameState{PLAY, EXIT};

class TrainGame
{
public:

	/* Constructor and deconstructor */
	TrainGame();
	~TrainGame();

	/* Public start function used only to run the game */
	void Start();

private:

	/* Functions */

	void InitialiseProcedures(); // initializes systems
	void StartGameLoop(); //starts processing the gameloop
	void RecieveInputs(); //recieves the events
	bool CheckCollision(glm::vec3 o1Pos, float o1Rad, glm::vec3 o2Pos, float o2Rad); //function checking spherical collision between said objects
	void RandomiseLine(); //function to randomise the train track on which the train will appear
	void RenderGame(); //rendering everything
	void linkFogShader(); //linking the fog

	/* Component Variables */

	Display gameRenderDisplay;
	GameState trainGameState;
	Mesh playerModel;
	Mesh envModel;
	Mesh trackMidModel;
	Mesh trainModel;
	Camera myCamera;
	Shader fogshader;
	AudioRelated audioManager;

	/* Game Variables */
	float trainZ, xMovement, speedTrain, trainLine;
	bool gameOver=false;
	int points = 0;
	unsigned int prevTick = 0, currentTick;
};

