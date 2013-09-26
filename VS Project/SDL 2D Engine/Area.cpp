#include "Area.h"
#include "Enemy.h"
#include "Player.h"

Area Area::Instance;

Area::Area()
{
	_areaSizeX = 0;
	_areaSizeY = 0;
	_tileset = NULL;
	_areaBackground = NULL;
}

/*
parsing the map data from the specified file.
return true on success
*/
bool Area::Load(char* file)
{
	char ignoreComment[1000];

	_tileList.clear();

	FILE* fileHandle = NULL;
	fopen_s(&fileHandle, file, "r");
	if(fileHandle == NULL)
		return false;

	// load the area tileset file
	char tilesetFile[1000];
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fscanf_s(fileHandle, "%s\n", tilesetFile);
	if((_tileset = SurfaceWrapper::Load(tilesetFile)) == false)
	{
		fclose(fileHandle);
		return false;
	}
	SurfaceWrapper::SetTransparency(_tileset, 255, 255, 255, false);

	// load area size
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fscanf_s(fileHandle, "%d:%d\n", &_areaSizeX, &_areaSizeY);
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	// parse the tiles
	for(int y=0; y < _areaSizeY; y++)
	{
		for(int x=0; x < _areaSizeX; x++)
		{
			Tile tempTile;
			fscanf_s(fileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);
			_tileList.push_back(tempTile);
		}
		fscanf_s(fileHandle, "\n");
	}

	// load the background file
	char backgroundFile[1000];
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fscanf_s(fileHandle, "%s\n", backgroundFile);
	if((_areaBackground = SurfaceWrapper::Load(backgroundFile)) == NULL)
		return false;

	// initialize player
	int playerPosX = 0;
	int playerPosY = 0;
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fscanf_s(fileHandle, "%i:%i\n", &playerPosX, &playerPosY);
	GameData::Instance.GetPlayer()->Spawn((float)playerPosX, (float)playerPosY);
	Entity::currentEntities.push_back(GameData::Instance.GetPlayer());
	
	// set camera mode and target
	Camera::Instance.targetMode = GameData::Instance.IsCenteredCameraMode() ? TARGET_MODE_CENTER : TARGET_MODE_FOLLOW;
	Camera::Instance.SetTarget(GameData::Instance.GetPlayer());

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

		enemy->Spawn((float)enemyPosX, (float)enemyPosY);
		Enemy::currentEntities.push_back(enemy);
	}

	for(uint16_t i=0; i<Entity::currentEntities.size(); i++)
	{
		Entity *curEntity = Entity::currentEntities.at(i);
		if(!curEntity) continue;

		curEntity->deathAnimation = new OneTimeAnimation();
		curEntity->deathAnimation->Load(GameData::Instance.GetDieAnimationFile(), GameData::Instance.GetDieAnimationWidth(), 
			GameData::Instance.GetDieAnimationHeigth(), GameData::Instance.GetDieAnimationFrames());
	}
	
	fclose(fileHandle);

	return true;
}

void Area::Render(SDL_Surface* surfDisplay, int cameraX, int cameraY)
{
	// draw the background
	SurfaceWrapper::Draw(surfDisplay, _areaBackground, 0, 0, 0, 0, WWIDTH, WHEIGHT);
	
	// render the tiles of the map
	if(_tileset == NULL) return;

	int tilesetWidth = _tileset->w / TILE_SIZE;
	int tilesetHeight = _tileset->h / TILE_SIZE;
	int id = 0;

	for(int y=0; y < _areaSizeY; y++)
	{
		for(int x=0; x < _areaSizeX; x++)
		{
			if(_tileList[id].TypeID == NONE)
			{
				id++;
				continue;
			}

			int tX = cameraX + (x * TILE_SIZE);
			int tY = cameraY + (y * TILE_SIZE);

			int tilesetX = (_tileList[id].TileID % tilesetWidth) * TILE_SIZE;
			int tilesetY = (_tileList[id].TileID % tilesetWidth) / TILE_SIZE;

			SurfaceWrapper::Draw(surfDisplay, _tileset, tX, tY, tilesetX, tilesetY, TILE_SIZE, TILE_SIZE);

			id++;
		}
	}
}

void Area::Cleanup()
{
	if(_tileset)
		SDL_FreeSurface(_tileset);

	_tileList.clear();

	SDL_FreeSurface(_areaBackground);
}

Tile* Area::GetTile(int x, int y)
{
	int tileX = x / TILE_SIZE;
	int tileY = y / TILE_SIZE;

	if(tileX >= _areaSizeX || tileX < 0 || tileY >= _areaSizeY || tileY < 0)
		return NULL;
	
	uint16_t ID = tileX + (_areaSizeX * tileY);

	if(ID < 0 || ID >= _tileList.size()) 
		return NULL;

	return &_tileList[ID];
}

int Area::GetAreaSizeX()
{
	return _areaSizeX;
}

int Area::GetAreaSizeY()
{
	return _areaSizeY;
}