#include "CArea.h"

CArea CArea::areaControl;

CArea::CArea()
{
	areaSizeX = 0;
	areaSizeY = 0;
	surfTileset = NULL;
}

/*
parsing the map from the file...
*/
bool CArea::OnLoad(char* file)
{
	tileList.clear();

	FILE* fileHandle = fopen(file, "r");
	if(fileHandle == NULL)
		return false;

	// load the tileset
	char tilesetFile[1000];
	fscanf(fileHandle, "%s\n", tilesetFile);

	if((surfTileset = CSurface::OnLoad(tilesetFile)) == false)
	{
		fclose(fileHandle);
		return false;
	}

	// load area size
	fscanf(fileHandle, "%d %d\n", &areaSizeX, &areaSizeY);

	// parse the tiles
	for(int y=0; y < areaSizeY; y++)
	{
		for(int x=0; x < areaSizeX; x++)
		{
			CTile tempTile;
			fscanf(fileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);
			tileList.push_back(tempTile);
		}
		fscanf(fileHandle, "\n");
	}

	fclose(fileHandle);

	return true;
}

void CArea::OnRender(SDL_Surface* surfDisplay, int cameraX, int cameraY)
{
	// render the tiles of the map
	if(surfTileset == NULL) return;

	int tilesetWidth = surfTileset->w / TILE_SIZE;
	int tilesetHeight = surfTileset->h / TILE_SIZE;
	int id = 0;

	for(int y=0; y < areaSizeY; y++)
	{
		for(int x=0; x < areaSizeX; x++)
		{
			if(tileList[id].TypeID == TILE_TYPE_NONE)
			{
				id++;
				continue;
			}

			int tX = cameraX + (x * TILE_SIZE);
			int tY = cameraY + (y * TILE_SIZE);

			int tilesetX = (tileList[id].TileID % tilesetWidth) * TILE_SIZE;
			int tilesetY = (tileList[id].TileID % tilesetWidth) / TILE_SIZE;

			CSurface::OnDraw(surfDisplay, surfTileset, tX, tY, tilesetX, tilesetY, TILE_SIZE, TILE_SIZE);

			id++;
		}
	}
}

void CArea::OnCleanup()
{
	if(surfTileset)
		SDL_FreeSurface(surfTileset);

	tileList.clear();
}

CTile* CArea::GetTile(int x, int y)
{
	int ID = x / TILE_SIZE;
	ID = ID + (areaSizeX * (y / TILE_SIZE));

	if(ID < 0 || ID >= tileList.size()) return NULL;

	return &tileList[ID];
}