#ifndef _Area_H_
    #define _Area_H_

#include <SDL.h>
#include <vector>

#include "GameData.h"
#include "Tile.h"
#include "Camera.h"
#include "SurfaceWrapper.h"

class Enemy;
class Player;

/**
	A single area level, containing a list of tiles.
*/
class Area{
public:
	static Area		Instance;

private:
	SDL_Surface*	_tileset;
	std::vector<Tile> _tileList;
	SDL_Surface*	_areaBackground;

	int				_areaSizeX;
	int				_areaSizeY;

public:
	Area();
	bool Load(char* file);
	void Render(SDL_Surface* surfDisplay, int cameraX, int cameraY);
	void Cleanup();

	Tile* GetTile(int x, int y);
	int GetAreaSizeX();
	int GetAreaSizeY();
};

#endif