#include "CArea.h"
#include "CEnemy.h"
#include "CPlayer.h"

CArea CArea::areaControl;

CArea::CArea()
{
	areaSizeX = 0;
	areaSizeY = 0;
	surfTileset = NULL;
	areaBackground = NULL;
}

CPlayer* CArea::GetPlayer()
{
	return player;
}

/*
parsing the map data from the specified file.
return true on success
*/
bool CArea::OnLoad(char* file)
{
	char ignoreComment[1000];

	tileList.clear();

	FILE* fileHandle = NULL;
	fopen_s(&fileHandle, file, "r");
	if(fileHandle == NULL)
		return false;

	// load the area tileset file
	char tilesetFile[1000];
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fscanf_s(fileHandle, "%s\n", tilesetFile);
	if((surfTileset = CSurface::OnLoad(tilesetFile)) == false)
	{
		fclose(fileHandle);
		return false;
	}

	// load area size
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fscanf_s(fileHandle, "%d:%d\n", &areaSizeX, &areaSizeY);
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	// parse the tiles
	for(int y=0; y < areaSizeY; y++)
	{
		for(int x=0; x < areaSizeX; x++)
		{
			CTile tempTile;
			fscanf_s(fileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);
			tileList.push_back(tempTile);
		}
		fscanf_s(fileHandle, "\n");
	}

	// load the background file
	char backgroundFile[1000];
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fscanf_s(fileHandle, "%s\n", backgroundFile);
	if((areaBackground = CSurface::OnLoad(backgroundFile)) == NULL)
		return false;

	// load the player sprite file and initialize player
	char playerSpriteFile[1000];
	int playerSpriteWidth = 0;
	int playerSpriteHeigth = 0;
	int playerSpriteFPS = 0;
	int playerPosX = 0;
	int playerPosY = 0;
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fscanf_s(fileHandle, "%s ", playerSpriteFile);
	fscanf_s(fileHandle, "%i:%i ", &playerSpriteWidth, &playerSpriteHeigth);
	fscanf_s(fileHandle, "%i ", &playerSpriteFPS);
	fscanf_s(fileHandle, "%i:%i\n", &playerPosX, &playerPosY);
	player = new CPlayer();
	if(player->OnLoad(playerSpriteFile, playerSpriteWidth, playerSpriteHeigth, playerSpriteFPS) == false)
		return false;
	player->x = (float)playerPosX;
	player->y = (float)playerPosY;
	CEntity::EntityList.push_back(player);
	
	// set camera target to player
	CCamera::CameraControl.targetMode = TARGET_MODE_FOLLOW;
	CCamera::CameraControl.SetTarget(player);

	// load the enemy sprite files and initialize enemies
	int enemyAmount = 0;
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fscanf_s(fileHandle, "%i\n", &enemyAmount);
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	for(int i=0; i<enemyAmount; i++)
	{
		CEnemy* enemy;
		enemy = new CEnemy();
		char enemySpriteFile[1000];
		int enemySpriteWidth = 0;
		int enemySpriteHeight = 0;
		int enemySpriteFPS = 0;
		int enemyPosX = 0;
		int enemyPosY = 0;
		fscanf_s(fileHandle, "%s ", enemySpriteFile);
		fscanf_s(fileHandle, "%i:%i ", &enemySpriteWidth, &enemySpriteHeight);
		fscanf_s(fileHandle, "%i ", &enemySpriteFPS);
		fscanf_s(fileHandle, "%i:%i\n", &enemyPosX, &enemyPosY);
		if(enemy->OnLoad(enemySpriteFile, enemySpriteWidth, enemySpriteHeight, enemySpriteFPS) == false)
			return false;

		enemy->x = (float)enemyPosX;
		enemy->y = (float)enemyPosY;
		CEnemy::EntityList.push_back(enemy);
	}
	
	fclose(fileHandle);

	return true;
}

void CArea::OnRender(SDL_Surface* surfDisplay, int cameraX, int cameraY)
{
	// draw the background
	CSurface::OnDraw(surfDisplay, areaBackground, 0, 0, 0, 0, 600, 600);
	
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

	SDL_FreeSurface(areaBackground);
}

CTile* CArea::GetTile(int x, int y)
{
	uint8_t ID = x / TILE_SIZE;
	ID = ID + (areaSizeX * (y / TILE_SIZE));

	if(ID < 0 || ID >= tileList.size()) 
		return NULL;

	return &tileList[ID];
}