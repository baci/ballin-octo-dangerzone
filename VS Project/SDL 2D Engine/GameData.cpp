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

char* GameData::GetDieAnimationFile()
{
	return _dieAnimationFile;
}

int	GameData::GetDieAnimationWidth()
{
	return _dieAnimationWidth;
}

int	GameData::GetDieAnimationHeigth()
{
	return _dieAnimationHeigth;
}

int	GameData::GetDieAnimationFrames()
{
	return _dieAnimationFrames;
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

	// parse the die animation sprite data
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	fscanf_s(fileHandle, "%s ", _dieAnimationFile);
	fscanf_s(fileHandle, "%i:%i ", &_dieAnimationWidth, &_dieAnimationHeigth);
	fscanf_s(fileHandle, "%i ", &_dieAnimationFrames);

	// parse the collision setting
	fgets(ignoreComment, sizeof ignoreComment, fileHandle); // comment
	int fullCollision = 0;
	fscanf_s(fileHandle, "%i ", &fullCollision);
	_fullMapCollision = (fullCollision == 1);

	// parse the camera setting
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