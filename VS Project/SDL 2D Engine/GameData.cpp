#include "Entity.h"
#include "Player.h"
#include "GameData.h"

GameData GameData::Instance;

GameData::GameData()
{

}

Player* GameData::GetPlayer()
{
	return _player;
}

Entity* GameData::GetDieAnimation()
{
	return _dieAnimation;
}

bool GameData::IsFullMapCollision()
{
	return _fullMapCollision;
}

bool GameData::IsCenteredCameraMode()
{
	return _centeredCamera;
}

bool GameData::OnLoad(char* file)
{
	char ignoreComment[1000];

	FILE* fileHandle = NULL;
	fopen_s(&fileHandle, file, "r");
	if(fileHandle == NULL)
		return false;
	
	// load the player sprite file
	char playerSpriteFile[1000];
	int playerSpriteWidth = 0;
	int playerSpriteHeigth = 0;
	int playerSpriteFPS = 0;
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fscanf_s(fileHandle, "%s ", playerSpriteFile);
	fscanf_s(fileHandle, "%i:%i ", &playerSpriteWidth, &playerSpriteHeigth);
	fscanf_s(fileHandle, "%i ", &playerSpriteFPS);
	_player = new Player();
	if(_player->Load(playerSpriteFile, playerSpriteWidth, playerSpriteHeigth, playerSpriteFPS) == false)
		return false;

	// load the die animation sprite file
	// TODO: make a one-time-animation class
	char dieAnimSpriteFile[1000];
	int dieAnimSpriteWidth = 0;
	int dieAnimSpriteHeigth = 0;
	int dieAnimSpriteFPS = 0;
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fscanf_s(fileHandle, "%s ", dieAnimSpriteFile);
	fscanf_s(fileHandle, "%i:%i ", &dieAnimSpriteWidth, &dieAnimSpriteHeigth);
	fscanf_s(fileHandle, "%i ", &dieAnimSpriteFPS);
	_dieAnimation = new Entity();
	if(_dieAnimation->Load(dieAnimSpriteFile, dieAnimSpriteWidth, dieAnimSpriteHeigth, dieAnimSpriteFPS) == false)
		return false;

	// load the collision setting
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	int fullCollision = 0;
	fscanf_s(fileHandle, "%i ", &fullCollision);
	_fullMapCollision = (fullCollision == 1);

	// load the camera setting
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	int centeredCamera = 0;
	fscanf_s(fileHandle, "%i ", &centeredCamera);
	_centeredCamera = (centeredCamera == 1);
	
	fclose(fileHandle);

	return true;
}

void GameData::OnCleanup()
{

}