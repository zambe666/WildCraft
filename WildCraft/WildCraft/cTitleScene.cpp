#include "stdafx.h"
#include "cTitleScene.h"


cTitleScene::cTitleScene()
{
}


cTitleScene::~cTitleScene()
{
}

const HRESULT cTitleScene::Init(DWORD dwFlag)
{
	return S_OK;
}
void cTitleScene::Update()
{
	if (KEY_MANAGER->isOnceKeyDown('1'))	// test ȭ��
	{
		SCENE_MANAGER->ChangeScene("TestScene");
	}
	if (KEY_MANAGER->isOnceKeyDown('2'))	// Create ȭ��
	{
		SCENE_MANAGER->ChangeScene("MapCreateScene");
	}
	if (KEY_MANAGER->isOnceKeyDown('3'))	// play ȭ��
	{
		SCENE_MANAGER->ChangeScene("PlayScene");
	}
}
void cTitleScene::Render()
{

}
void cTitleScene::Release()
{
	// ��ȯ ������ ������ �͵�
}
void cTitleScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}