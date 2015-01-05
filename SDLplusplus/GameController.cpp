#include "GameController.h"

namespace SDL {

GameController::~GameController()
{
	Close();
}
	
void GameController::Open(int p_joystickIndex)
{
	gameController = SDL_GameControllerOpen(p_joystickIndex);
	if (gameController == nullptr) {
		// error
	}
}
	
void GameController::Close()
{
	SDL_GameControllerClose(gameController);
	
	gameController = nullptr;
}
	
bool GameController::GetButton(Button p_button) const
{
	return SDL_GameControllerGetButton(gameController, (SDL_GameControllerButton)p_button);
}
	
}