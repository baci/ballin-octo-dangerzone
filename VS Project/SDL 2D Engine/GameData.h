/**
	class holding global game data read from a file
*/

#ifndef _GAMEDATA_H_
	#define _GAMEDATA_H_

#include <SDL.h>
#include <vector>

class Entity;
class Player;

class GameData {
public:
	static GameData	Instance;

private:
	Player				*_player;		// player sprite
	
	bool	_fullMapCollision; // true: full map collision detection, false: only check on underlying ground
	bool	_centeredCamera;   // true: centered camera mode, false: follow camera mode

	char	_dieAnimationFile[1000];
	int		_dieAnimationWidth;
	int		_dieAnimationHeigth;
	int		_dieAnimationFrames;

public:
	GameData();
	bool OnLoad(char* file);
	void OnCleanup();

	Player* GetPlayer();
	char*	GetDieAnimationFile();
	int		GetDieAnimationWidth();
	int		GetDieAnimationHeigth();
	int		GetDieAnimationFrames();
	bool	IsFullMapCollision();
	bool	IsCenteredCameraMode();
};

#endif