#include "CApp.h"

CApp* CApp::_instance = NULL;

CApp::CApp() {
    _surfDisplay = NULL;

	_debugMessage = NULL;
	_debugFont = NULL;
	_debugMode = true;

    _running = true;
}

CApp* CApp::GetInstance()
{
	if (_instance == NULL) {
		_instance = new CApp();
	}
	return _instance;
}

int CApp::OnExecute() {
    if(OnInit()==false)
        return -1;

    SDL_Event event;

    while(_running)
    {
        while(SDL_PollEvent(&event)){
            _eventHandler->OnEvent(&event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

int main(int argc, char* argv[]) {
    return CApp::GetInstance()->OnExecute();
}
