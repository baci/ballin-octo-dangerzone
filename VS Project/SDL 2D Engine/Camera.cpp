#include "Camera.h"
#include "Entity.h"

Camera Camera::Instance;

Camera::Camera()
{
	_x = _y = 0;
	target = NULL;
	targetMode = TARGET_MODE_NORMAL;
	followThreshold = 0.8f;
}

void Camera::MoveRelative(int moveX, int moveY)
{
	_x += moveX;
	_y += moveY;
}

int Camera::GetX()
{
	return _x;
}

int Camera::GetY()
{
	return _y;
}

void Camera::CenterOnTarget()
{
	_x = (int)(this->target->x - (WWIDTH / 2));
	_y = (int)(this->target->y - (WHEIGHT / 2));
}

void Camera::Update()
{
	if(target != NULL)
	{
		if(targetMode == TARGET_MODE_CENTER)
		{
			_x = (int)(this->target->x - (WWIDTH / 2));
			_y = (int)(this->target->y - (WHEIGHT / 2));
		}
		else if(targetMode == TARGET_MODE_FOLLOW)
		{
			if(this->target->x > (_x + (WWIDTH * followThreshold)))
				_x++;
			else if(this->target->x < (_x + (WWIDTH * (1-followThreshold))))
				_x--;

			if(this->target->y > (_y + (WHEIGHT * followThreshold)))
				_y++;
			else if(this->target->y < (_y + (WHEIGHT * (1-followThreshold))))
				_y--;
		}
	}
}

void Camera::SetPos(int x, int y)
{
	_x = x;
	_y = y;
}

void Camera::SetTarget(Entity* _target)
{
	target = _target;
}