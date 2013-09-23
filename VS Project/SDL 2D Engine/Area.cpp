#include "Area.h"
#include "Enemy.h"
#include "Player.h"

Area Area::Instance;

Area::Area()
{
	//Instance = this;
	areaSizeX = 0;
	areaSizeY = 0;
	surfTileset = NULL;
	areaBackground = NULL;
}

Player* Area::GetPlayer()
{
	return player;
}

/*
parsing the map data from the specified file.
return true on success
*/
bool Area::OnLoad(char* file)
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
	if((surfTileset = ExtendedSurface::OnLoad(tilesetFile)) == false)
	{
		fclose(fileHandle);
		return false;
	}
	ExtendedSurface::Transparent(surfTileset, 255, 255, 255, false);

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
			Tile tempTile;
			fscanf_s(fileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);
			tileList.push_back(tempTile);
		}
		fscanf_s(fileHandle, "\n");
	}

	// load the background file
	char backgroundFile[1000];
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fscanf_s(fileHandle, "%s\n", backgroundFile);
	if((areaBackground = ExtendedSurface::OnLoad(backgroundFile)) == NULL)
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
	player = new Player();
	if(player->Load(playerSpriteFile, playerSpriteWidth, playerSpriteHeigth, playerSpriteFPS) == false)
		return false;
	player->Spawn((float)playerPosX, (float)playerPosY);
	Entity::currentEntities.push_back(player);
	
	// set camera target to player
	Camera::Instance.targetMode = TARGET_MODE_FOLLOW;
	Camera::Instance.SetTarget(player);

	// load the enemy sprite files and initialize enemies
	int enemyAmount = 0;
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fscanf_s(fileHandle, "%i\n", &enemyAmount);
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	for(int i=0; i<enemyAmount; i++)
	{
		Enemy* enemy;
		enemy = new Enemy();
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
		if(enemy->Load(enemySpriteFile, enemySpriteWidth, enemySpriteHeight, enemySpriteFPS) == false)
			return false;

		enemy->x = (float)enemyPosX;
		enemy->y = (float)enemyPosY;
		Enemy::currentEntities.push_back(enemy);
	}
	
	fclose(fileHandle);

	return true;
}

void Area::OnRender(SDL_Surface* surfDisplay, int cameraX, int cameraY)
{
	// draw the background
	ExtendedSurface::OnDraw(surfDisplay, areaBackground, 0, 0, 0, 0, WWIDTH, WHEIGHT);
	
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

			ExtendedSurface::OnDraw(surfDisplay, surfTileset, tX, tY, tilesetX, tilesetY, TILE_SIZE, TILE_SIZE);

			id++;
		}
	}
}

void Area::OnCleanup()
{
	if(surfTileset)
		SDL_FreeSurface(surfTileset);

	tileList.clear();

	SDL_FreeSurface(areaBackground);
}

Tile* Area::GetTile(int x, int y)
{
	int tileX = x / TILE_SIZE;
	int tileY = y / TILE_SIZE;

	// TODO so there is the fucking bug
	if(tileX >= areaSizeX || tileX < 0 || tileY >= areaSizeY || tileY < 0)
		return NULL;
	
	uint16_t ID = tileX + (areaSizeX * tileY);

	if(ID < 0 || ID >= tileList.size()) 
		return NULL;

	return &tileList[ID];
}