#ifndef _CAREA_H_
    #define _CAREA_H_

#include <SDL.h>
#include <vector>
 
#include "CTile.h"
#include "CSurface.h"

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

public:
	CArea();
	bool OnLoad(char* file);
	void OnRender(SDL_Surface* surfDisplay, int cameraX, int cameraY);
	void OnCleanup();

	CTile* GetTile(int x, int y);
};

#endif