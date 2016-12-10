#include "stdafx.h"
#include "cKeyManager.h"


cKeyManager::cKeyManager()
{
	for (int i = 0; i < 256; i++)
	{
		_keyUp.set(i, false);
		_keyDown.set(i, false);
	}
}
cKeyManager::~cKeyManager()
{}

const bool cKeyManager::isOnceKeyDown(const int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!_keyDown[key])
		{
			_keyDown.set(key, true);
			return true;
		}
	}
	else	_keyDown.set(key, false);
	return false;
}

const bool cKeyManager::isOnceKeyUp(const int key)
{
	if (GetAsyncKeyState(key) & 0x8000)	_keyUp.set(key, true);
	else
	{
		if (_keyUp[key])
		{
			_keyUp.set(key, false);
			return true;
		}
	}
	return false;
}

const bool cKeyManager::isStayKeyDown(const int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

const bool cKeyManager::isToggleKey(const int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}