#ifndef _Area_H_
    #define _Area_H_

#include <SDL.h>
#include <vector>

#include "GameData.h"
#include "Tile.h"
#include "Camera.h"
#include "ExtendedSurface.h"

class Enemy;
class Player;

/**
	A single area level, containing a list of tiles.
*/
class Area{
public:
	static Area		Instance;

private:
	int				areaSizeX;
	int				areaSizeY;
	SDL_Surface*	surfTileset;
	std::vector<Tile> tileList;
	SDL_Surface*	areaBackground;

public:
	Area();
	bool OnLoad(char* file);
	void OnRender(SDL_Surface* surfDisplay, int cameraX, int cameraY);
	void OnCleanup();

	Tile* GetTile(int x, int y);
};

#endif