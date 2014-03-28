#include <stdio.h>
#include "Game.h"
#include "Logger.h"
#include <stdio.h>
#include "Sprite.h"
#include "Input.h"
#include "Player.h"

Game::Game(Window *lGameWindow){
	if(lGameWindow != nullptr){
		this->gameWindow = lGameWindow;
		this->isRunning = true;
		
		const int DESIRED_FPS = 60;

		// TODO: extract this to a method. Possibly a framerate wrapper, to work with dt.
		// Initializes the SDL2_GFX framerate control.
		SDL_initFramerate(&this->fpsManager);
		int framerateSet = SDL_setFramerate(&this->fpsManager, DESIRED_FPS);
		if(framerateSet == 0){
			Logger::log("Successfully started the framerate manager.");
		}
		else{
			Logger::warning("Failed to start the framerate manager.");
		}
	}
	else{
		this->gameWindow = nullptr;
		this->isRunning = false;
		Logger::warning("Game window is null. Game will not run.");
	}
}

Game::~Game(){
	// Destroys the Window.
	this->gameWindow->destroy();
}

void Game::runGame(){
	// Just an example of Sprite loading, delete this later.
	Sprite *sprite = nullptr;
	sprite = new Sprite(this->gameWindow->renderer);
	bool loadedSprite = sprite->loadFrom("res/hdimg.png");
	if(!loadedSprite){
		Logger::error("Couldn't load sprite.");
	}

	// Creating the input handler	
	Input *gameInput = nullptr;
	gameInput = new Input(this);
	
	// Get the first game time.
	double lLastTime = SDL_GetTicks();
	
	// Main game loop.
	while(this->isRunning){

		// Sets the draw color and clears the screen.
		gameWindow->clear();
		
		// Gets the inputs.
		gameInput->handleInput();
	
		// get the current time. 
		double lNow = SDL_GetTicks();
		// Diff of last time and current time.
		double lDt = (lNow - lLastTime)/1000.0;
		// update the last time.
		lLastTime = lNow;
		// Updating the game.	
		printf("\n%lf",lDt);
		this->update(lDt);

		// Render the example sprite.
		sprite->render(x, 0, nullptr);

		// Renders the gameWindow.
		gameWindow->render();

		// Renders the player.
		player->render();

		// Delays the framerate, if necessary.
		SDL_framerateDelay(&this->fpsManager);

	}

}

void Game::update(double lDt){
	// Call players update.

}

void Game::setPlayer(Player *player){
	// Sets the player.
	if(this->player == nullptr){
		this->player = player;
	}
	else{
		// We do not have two player in this game.
	}
}
