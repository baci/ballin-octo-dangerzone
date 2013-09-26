#include "Camera.h"
#include "Entity.h"

Camera Camera::Instance;

Camera::Camera()
{
	_x = _y = 0;
	_target = NULL;
	targetMode = TARGET_MODE_NORMAL;
	_followThreshold = 0.8f;
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
	_x = (int)(this->_target->GetX() - (WWIDTH / 2));
	_y = (int)(this->_target->GetY() + (WHEIGHT / 2));
}

void Camera::Update()
{
	if(_target != NULL)
	{
		if(targetMode == TARGET_MODE_CENTER)
		{
			_x = (int)(this->_target->GetX() - (WWIDTH / 2));
			_y = (int)(this->_target->GetY() - (WHEIGHT / 2));
		}
		else if(targetMode == TARGET_MODE_FOLLOW)
		{
			if(this->_target->GetX() > (_x + (WWIDTH * _followThreshold)))
				_x++;
			else if(this->_target->GetX() < (_x + (WWIDTH * (1-_followThreshold))))
				_x--;

			if(this->_target->GetY() > (_y + (WHEIGHT * _followThreshold)))
				_y++;
			else if(this->_target->GetY() < (_y + (WHEIGHT * (1-_followThreshold))))
				_y--;
		}
	}
}

void Camera::SetPos(int x, int y)
{
	_x = x;
	_y = y;
}

void Camera::SetTarget(Entity* target)
{
	_target = target;
}