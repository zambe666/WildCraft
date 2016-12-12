#include "stdafx.h"
#include "cMainGame.h"
#include "cTitleScene.h"
#include "cMapCreateScene.h"
#include "cPlayScene.h"
#include "cFrameworkTest.h"

cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
	TEXTURE_MANAGER->Destroy();
	SHADER_MANAGER->Destroy();
	SCENE_MANAGER->Destroy();
	OBJECT_MANAGER->Destroy();
	DEVICE_MANAGER->Destroy();
}


const HRESULT cMainGame::Init()
{
#pragma region �⺻ ����, �մ� �� ����
	DEVICE_MANAGER->Init();
	TIME_MANAGER->Init(false);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1, 1000);
	DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);

	D3DVIEWPORT9 matViewport = { 0, 0, rc.right, rc.bottom, 0.0f, 1.0f };
	DEVICE->SetViewport(&matViewport);

#pragma endregion
//
	// SCENE �ʱ�ȭ �ؼ� �ִ� ��
	LPSCENENODE scene = new cMapCreateScene;
	SCENE_MANAGER->AddScene("MapCreateScene", scene);
	scene = new cPlayScene;
	SCENE_MANAGER->AddScene("PlayScene", scene);
	scene = new cTitleScene;
	SCENE_MANAGER->AddScene("TitleScene", scene);
	scene = new cFrameworkTest;
	SCENE_MANAGER->AddScene("TestScene", scene);

	SCENE_MANAGER->ChangeScene("TestScene");

	return S_OK;
}
void cMainGame::Update()
{
	TIME_MANAGER->Update();
	SCENE_MANAGER->Update();
}
void cMainGame::Render()
{
	DEVICE->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200, 200, 200), 1.0f, 0);
	DEVICE->BeginScene();
	SCENE_MANAGER->Render();
	DEVICE->EndScene();
	DEVICE->Present(NULL, NULL, NULL, NULL);
}
void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SCENE_MANAGER->WndProc(hWnd, message, wParam, lParam);
}
