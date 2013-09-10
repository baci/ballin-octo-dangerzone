#include "CCamera.h"
#include "CEntity.h"

CCamera CCamera::CameraControl;

CCamera::CCamera()
{
	x = y = 0;
	target = NULL;
	targetMode = TARGET_MODE_FOLLOW;
	followThreshold = 0.8f;
}

void CCamera::OnMove(int moveX, int moveY)
{
	x += moveX;
	y += moveY;
}

int CCamera::GetX()
{
	if(target != NULL)
	{
		if(targetMode == TARGET_MODE_CENTER)
			return (int)(this->target->x - (WWIDTH / 2));
		else if(targetMode == TARGET_MODE_FOLLOW)
		{
			if(this->target->x > (x + (WWIDTH * followThreshold)))
				x++;
			else if(this->target->x < (x + (WWIDTH * (1-followThreshold))))
				x--;
			return x;
		}

		return (int)this->target->x;
	}
	
	return x;
}

int CCamera::GetY()
{
	if(target != NULL)
	{
		if(targetMode == TARGET_MODE_CENTER)
			return (int)(this->target->y - (WHEIGHT / 2));
		else if(targetMode == TARGET_MODE_FOLLOW)
		{
			if(this->target->y > (y + (WHEIGHT * followThreshold)))
				y++;
			else if(this->target->y < (y + (WHEIGHT * (1-followThreshold))))
				y--;
			return y;
		}

		return (int)this->target->y;
	}
	
	return y;
}

void CCamera::SetPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void CCamera::SetTarget(CEntity* _target)
{
	this->target = _target;
}