#ifndef _CAREA_H_
    #define _CAREA_H_

#include <SDL.h>
#include <vector>

#include "CTile.h"
#include "CCamera.h"
#include "CSurface.h"

class CEnemy;
class CPlayer;

/**
	A single area level, containing a list of tiles.
*/
class CArea{
public:
	static CArea		areaControl;

private:
	int				areaSizeX;
	int				areaSizeY;
	SDL_Surface*	surfTileset;
	std::vector<CTile> tileList;
	SDL_Surface*	areaBackground;

	CPlayer* player;

public:
	CArea();
	bool OnLoad(char* file);
	void OnRender(SDL_Surface* surfDisplay, int cameraX, int cameraY);
	void OnCleanup();

	CPlayer* GetPlayer();

	CTile* GetTile(int x, int y);
};

#endif