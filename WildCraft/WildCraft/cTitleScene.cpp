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
	if (KEY_MANAGER->isOnceKeyDown('1'))	// test 화면
	{
		SCENE_MANAGER->ChangeScene("TestScene");
	}
	if (KEY_MANAGER->isOnceKeyDown('2'))	// Create 화면
	{
		SCENE_MANAGER->ChangeScene("MapCreateScene");
	}
	if (KEY_MANAGER->isOnceKeyDown('3'))	// play 화면
	{
		SCENE_MANAGER->ChangeScene("PlayScene");
	}
}
void cTitleScene::Render()
{

}
void cTitleScene::Release()
{
	// 전환 시점에 삭제할 것들
}
void cTitleScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}