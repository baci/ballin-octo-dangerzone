#include "CPlayer.h"

CPlayer::CPlayer(){}

bool CPlayer::OnLoad(char* file, int width, int height, int maxFrames)
{
	if(CEntity::OnLoad(file, width, height, maxFrames) == false) {
        return false;
    }
 
    return true;
}

void CPlayer::OnLoop() {
    CEntity::OnLoop();
}
 
void CPlayer::OnRender(SDL_Surface* Surf_Display) {
    CEntity::OnRender(Surf_Display);
}
 
void CPlayer::OnCleanup() {
    CEntity::OnCleanup();
}

void CPlayer::OnAnimate()
{
	if(speedX != 0) {
        animControl.maxFrames = 8;
    }else{
        animControl.maxFrames = 0;
    }
 
    CEntity::OnAnimate();
}
 
bool CPlayer::OnCollision(CEntity* Entity) 
{
	Jump();
	return true;
}