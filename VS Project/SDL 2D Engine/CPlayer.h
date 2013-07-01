#ifndef _CPLAYER_H_
    #define _CPLAYER_H_
 
#include "CEntity.h"
 
class CPlayer : public CEntity {
    public:
        CPlayer();
 
        bool OnLoad(char* file, int width, int height, int maxFrames);
 
        void OnLoop();
 
        void OnRender(SDL_Surface* surfDisplay);
 
        void OnCleanup();
 
        void OnAnimate();
 
        bool OnCollision(CEntity* entity);
};
 
#endif