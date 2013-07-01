#include "CCamera.h"

CCamera CCamera::CameraControl;

CCamera::CCamera()
{
	x = y = 0;
	targetX = targetY = NULL;
	targetMode = TARGET_MODE_NORMAL;
}

void CCamera::OnMove(int moveX, int moveY)
{
	x += moveX;
	y += moveY;
}

int CCamera::GetX()
{
	if(targetX != NULL)
	{
		if(targetMode == TARGET_MODE_CENTER)
			return *targetX - (WWIDTH / 2);

		return *targetX;
	}
	
	return x;
}

int CCamera::GetY()
{
	if(targetY != NULL)
	{
		if(targetMode == TARGET_MODE_CENTER)
			return *targetY - (WHEIGHT / 2);

		return *targetY;
	}
	
	return y;
}

void CCamera::SetPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void CCamera::SetTarget(float* x, float* y)
{
	targetX = x;
	targetY = y;
}