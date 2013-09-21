#include "MainGame.h"

MainGame* MainGame::_instance = NULL;

MainGame::MainGame() {
    _surfDisplay = NULL;

	_debugMessage = NULL;
	_debugFont = NULL;
	_debugMode = true;

    _running = true;
}

MainGame* MainGame::GetInstance()
{
	if (_instance == NULL) {
		_instance = new MainGame();
	}
	return _instance;
}

int MainGame::Execute() {
    if(Init()==false)
        return -1;

    SDL_Event event;

    while(_running)
    {
        while(SDL_PollEvent(&event)){
            _eventHandler->HandleEvent(&event);
        }

        Update();
        Render();
    }

    Cleanup();

    return 0;
}

int main(int argc, char* argv[]) {
    return MainGame::GetInstance()->Execute();
}
