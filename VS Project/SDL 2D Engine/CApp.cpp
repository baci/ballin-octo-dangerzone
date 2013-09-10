#include "CApp.h"

CApp::CApp() {
    _surfDisplay = NULL;

    Running = true;
}

int CApp::OnExecute() {
    if(OnInit()==false)
        return -1;

    SDL_Event event;

    while(Running)
    {
        while(SDL_PollEvent(&event)){
            OnEvent(&event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

int main(int argc, char* argv[]) {
    CApp theApp;

    return theApp.OnExecute();
}
