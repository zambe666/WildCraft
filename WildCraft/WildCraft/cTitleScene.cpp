#include "stdafx.h"
#include "cTitleScene.h"
#include "cUIImageView.h"
#include "cUIButton.h"

cTitleScene::cTitleScene()
	: m_pTitleImage(nullptr), m_pSprite(nullptr)
{
	m_pButton[0] = m_pButton[1] = nullptr;
}


cTitleScene::~cTitleScene()
{
}

const HRESULT cTitleScene::Init(DWORD dwFlag)
{
	D3DXCreateSprite(DEVICE, &m_pSprite);

	m_pTitleImage = new cUIImageView;
	m_pTitleImage->SetLocalPos(D3DXVECTOR3(0, 0, 0));
	m_pTitleImage->SetTexture(TEXTURE_MANAGER->GetTexture("./System/Title.png"));
	
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
	m_pTitleImage->Render(m_pSprite);
}
void cTitleScene::Release()
{
	SAFE_RELEASE(m_pTitleImage);
	// 전환 시점에 삭제할 것들
}
void cTitleScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}