#include "TrainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>
#include "AudioRelated.h"
#include <time.h>


/* Creating transform variables for each game object */

Transform transform;
Transform playerTransform;
Transform envTransform;


/* Constructor */

TrainGame::TrainGame()
{
	trainGameState = GameState::PLAY;
	Display* gameRenderDisplay = new Display(); //pointing to display
	Shader fogshader();
    Mesh* playerModel();
	Mesh* envModel();
	Mesh* trackMidModel();
	Mesh* trainModel();

	AudioRelated audioManager();
}


/* Deconstructor */

TrainGame::~TrainGame()
{
	cout << "Deconstructing game....\n";
}


/* Public function called from main to start the game */

void TrainGame::Start() 
{
	cout << "__________________________\n\n W I K T O R   S U R F E R      \n\n   Starting the game... \n__________________________\n\n";
	InitialiseProcedures();
	StartGameLoop();
}

/* Function to start the systems and setting default variables */
void TrainGame::InitialiseProcedures()
{
	gameRenderDisplay.initialiseDisplay(); 

	/* Loading models */
	playerModel.LoadModelFromFile("..\\res\\Models\\PlayerUV.obj");
	envModel.LoadModelFromFile("..\\res\\Models\\Ground.obj");
	trackMidModel.LoadModelFromFile("..\\res\\Models\\Tracksf.obj");
	trainModel.LoadModelFromFile("..\\res\\Models\\Train.obj");
	
	/* Setting camera */
	myCamera.InitialiseCamera(glm::vec3(0, 10, -15), 70.0f, (float)gameRenderDisplay.getScreenWidth()/gameRenderDisplay.getScreenHeight(), 0.01f, 1000.0f);
	myCamera.Pitch(0.6f);
	fogshader.InitialiseShader("..\\res\\fog.vert", "..\\res\\fog.frag");


	/* Setting variables to default values */
	trainZ = 50.0f;
	xMovement = 0.0f;
	speedTrain = 0.6f;

	/* Randomising the train line */
	RandomiseLine();

	/* Loading audio tracks and playing bg music */
	audioManager.AddBGMusicTrack("..\\res\\Audio\\backgroundTrains.wav"); //https://www.youtube.com/watch?v=gKBAnBL4kmc
	audioManager.AddSoundEffect("..\\res\\Audio\\TrainHorn.wav"); //https://www.youtube.com/watch?v=0BcINnjrXbI
	audioManager.AddSoundEffect("..\\res\\Audio\\HitBoom.wav"); //https://www.youtube.com/watch?v=DKoSh6J44SE
	audioManager.PlayBGMusic();
}


/* Function that loops the functions of the game */

void TrainGame::StartGameLoop()
{
	while (trainGameState != GameState::EXIT)
	{
		RecieveInputs();
		RenderGame();
		if (!gameOver) {
			CheckCollision(playerModel.GetCollisionPosition(), playerModel.GetCollisionRadius(), trainModel.GetCollisionPosition(), trainModel.GetCollisionRadius());
		}
	}
}

void TrainGame::RecieveInputs()
{
	SDL_Event event; //calling out the events

	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		/* Keyboard inputs */
		case SDL_KEYDOWN:
			
			/* Movement keys inputs that check if player is in bounds and if so, moves the player accordingly */
			if ((event.key.keysym.sym == SDLK_a) || (event.key.keysym.sym == SDLK_LEFT)) {
				//std::cout << "'A' Key or Left Arrow has been pressed \n";
				if (xMovement < 4.5f) { 
					xMovement += 4.5; 
					myCamera.MoveCameraX(4.5f);
				}
			}

			if ((event.key.keysym.sym == SDLK_d) || (event.key.keysym.sym == SDLK_RIGHT)) {
				//std::cout << "'D' Key or Right Arrow has been pressed \n";
				if (xMovement > -4.5f){
					xMovement -= 4.5;
					myCamera.MoveCameraX(-4.5f);
				}
			}

			/* When player is in game over, once the player presses space the game restarts with ressetting the values aswell */
			if (event.key.keysym.sym == SDLK_SPACE) {
				//std::cout << "'Space' Key has been pressed \n";
				if (gameOver) {
					trainZ = 50.0f;
					
					speedTrain = 0.6f;
					RandomiseLine();
					gameOver = false;
					points = 0;
					audioManager.PlayBGMusic();
				}
			}

			/* Game can be closed by pressing escape as same as pressing the window quit button */
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				std::cout << "'ESC' Key has been pressed \n";
				SDL_Quit();
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			std::cout << "mouse button pressed \n";
			break;

		case SDL_QUIT:
				trainGameState = GameState::EXIT;
				break;
		}
	}
	
}


/* Function that checks spherical collision between two objects based on their position and given radius.
Theoritically the game could use cubical collisions but its more realistic to have it as a sphere as
getting close to train is dangerous enough so it is a educational state that the human beings shouldnt
get close to trains */

bool TrainGame::CheckCollision(glm::vec3 obj1Position, float Obj1Radius, glm::vec3 obj2Position, float obj2Radius)
{
	float objectsDistance = ((obj2Position.x - obj1Position.x)*(obj2Position.x - obj1Position.x) + (obj2Position.y - obj1Position.y)*(obj2Position.y - obj1Position.y) + (obj2Position.z - obj1Position.z)*(obj2Position.z - obj1Position.z));
	
	if (objectsDistance*objectsDistance < (Obj1Radius + obj2Radius))
	{
		// Setting the game to be in "Game Over" state.
		audioManager.PlaySoundEffect(1);
		audioManager.StopBGMusic();
		gameOver = true;
		cout << "__________________________\n\n     G A M E    O V E R    \n\n > Press Space to Retry < \n__________________________\n\n";
	

		// Setting window title as game over.
		std::string s = "WIKTOR SURFER | GAME OVER. FINISHED WITH " + std::to_string(points) + " POINTS. PRESS SPACE FOR RETRY.";
		char const* pchar = s.c_str();
		SDL_SetWindowTitle(gameRenderDisplay.window, pchar);

		return true;
	}
	else
	{
		return false;
	}
}


/* Function to randomise the train track on which the trains 
will appear so they are not always on the same line. */

void TrainGame::RandomiseLine() {
	int a;
	srand(time(NULL)); //professional C++ technique to get proper random instead of always the same random
	a = rand()%3;
	switch (a)
	{
	case 0:
		//cout << "Incoming: Right Line \n";
		trainLine = -4.5f;
		break;
	case 1:
		//cout << "Incoming: Middle Line \n";
		trainLine = 0.0f;
		break;
	case 2:
		//cout << "Incoming: Left Line \n";
		trainLine = 4.5f;
		break;
	default:
		cout << "Unknown randomise line value! \n"; //in case something went wrong used for testing always for to keep in case of future expansion
		break;
	}
}

void TrainGame::linkFogShader() 
{
	fogshader.setFloat("maxDist", 20.0f);
	fogshader.setFloat("minDist", 0.0f);
	fogshader.setVec3("fogColor", glm::vec3(0.0f, 0.0f, 0.0f));
}

/* Big function that renders whole game and makes it work as intended */
void TrainGame::RenderGame()
{
	/* Setting green as bg because grass*/
	gameRenderDisplay.resetDisplay(0.0f, 0.5f, 0.0f, 1.0f); 

	linkFogShader();

	/* Loading textures used in game */
	Texture texturePlayer("..\\res\\Textures\\humanText.png"); 
	Texture textureTrain("..\\res\\Textures\\TextureTrain.jpg"); 
	Texture textureTrack("..\\res\\Textures\\track.jpg");
	Texture textureGround("..\\res\\Textures\\dirt.jpg");

	/* Train track Object*/
	envTransform.SetPos(glm::vec3(0, -30, 10.0));
	envTransform.SetRot(glm::vec3(0.0, 0.0, 0));
	envTransform.SetScale(glm::vec3(1.0, 1.0, 2.0));

	fogshader.BindTexture();
	fogshader.Update(envTransform, myCamera);
	textureTrack.BindTexture(0);
	trackMidModel.RenderMesh();
	
	/* Dirt model Object */
	envTransform.SetScale(glm::vec3(0.8, 1.0, 1.5));
	fogshader.BindTexture();
	fogshader.Update(envTransform, myCamera);
	textureGround.BindTexture(0);
	envModel.RenderMesh();
	
	/* Rendering the rest only if the game is not over */
	if (!gameOver) {

		/* Player Object */
		playerTransform.SetPos(glm::vec3(xMovement, 0, -3));
		playerTransform.SetRot(glm::vec3(0.0, 0.0, 0));
		playerTransform.SetScale(glm::vec3(1.0, 1.0, 1.0));

		fogshader.BindTexture();
		fogshader.Update(playerTransform, myCamera);
		texturePlayer.BindTexture(0);
		playerModel.RenderMesh();
		playerModel.UpdateCollisionData(*playerTransform.GetPos(), 10.0f); // for collisions (environment didnt need that)

		/* Train Object */
		transform.SetPos(glm::vec3(trainLine, -2, trainZ));
		transform.SetRot(glm::vec3(0.0, 0, 0));
		transform.SetScale(glm::vec3(1, 1, 1));

		fogshader.BindTexture();
		fogshader.Update(transform, myCamera);
		textureTrain.BindTexture(0);
		trainModel.RenderMesh();
		trainModel.UpdateCollisionData(*transform.GetPos(), 240.0f);

		/* Moving the train */
		trainZ -= speedTrain;

		/* If train is over the screen reset it to top of the window and randomise line (giving impression of next train) */
		if (trainZ < -15.0f) {

			trainZ = 55.0f;
			RandomiseLine();
			if (points < 200) { //just for safety as from playtest, when the train is super fast then the sound effect can be very annoying
				audioManager.PlaySoundEffect(0);
			}
			else {
				cout << "Imagine train sound effect :)";
			}
		}

		currentTick = SDL_GetTicks();
		/* Function that runs every second if game is not over that adds points and speed of train. */
		if (currentTick > prevTick + 1000) {
			points += 1;
			speedTrain += 0.01f;
			cout << "POINTS: " << points << '\n';

			std::string a = "WIKTOR SURFER | CURRENT POINTS: ";
			std::string s = std::to_string(points);
			std::string b = a + s;
			char const* pchar = b.c_str();
			SDL_SetWindowTitle(gameRenderDisplay.window, pchar); //Setting the points in the title of the windows as I could not get the SDL to render the text :(

			prevTick = currentTick; //setting the current time tick as the previous tick so it waits another second
		}
	}

	/* 
	* if (gameOver) {
		std::string s = "WIKTOR SURFER | GAME OVER. FINISHED WITH " + std::to_string(points) + " POINTS. PRESS SPACE FOR RETRY.";
		char const* pchar = s.c_str();
		SDL_SetWindowTitle(gameRenderDisplay.window, pchar);
	}
	*/
				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	gameRenderDisplay.bufferOpenGL();
} 