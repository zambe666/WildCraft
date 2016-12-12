#include "stdafx.h"
#include "cFrameworkTest.h"
#include "cCameraEx.h"
#include "cController.h"

#include "cTerrainObject.h"
#include "cSkyDome.h"
#include "cGrid.h"


cFrameworkTest::cFrameworkTest()
{
}


cFrameworkTest::~cFrameworkTest()
{
}

const HRESULT cFrameworkTest::Init(DWORD dwFlag)
{
	m_pGrid = new cGrid;
	m_pGrid->Init(30);

	m_pCamera = new cCameraEx;
	D3DXVECTOR3 vEye{ 0,100,-400 };
	D3DXVECTOR3 vLook{ 0,0,10 };
	D3DXVECTOR3 vUp{ 0,1,0 };
	m_pCamera->SetView(&vEye, &vLook, &vUp);


	m_pSky = new cSkyDome;
	m_pSky->InitSkyDome("./Objects/Sky/skyTex2.jpg",15,15,100);
	m_pTerrain = new cTerrainObject;
	std::string texArray[3] = {
		"./Objects/Surface/ground01.tga", "./Objects/Surface/ground02.tga", "./Objects/Surface/ground03.tga"};
	m_pTerrain->Load("Map.raw", texArray, 1024, &D3DXVECTOR3(1, 1, 1));

	return S_OK;
}
void cFrameworkTest::Update()
{
	POINT pt; 
	float fDelta = 0.0001f; 
	GetCursorPos(&pt);
	RECT rc;

	GetWindowRect(g_hWnd, &rc);
	int nDeltaX = pt.x - (rc.left + WIN_SIZE_WIDTH / 2);
	int nDeltaY = pt.y - (rc.top + WIN_SIZE_HEIGHT / 2);
	if (abs(nDeltaX) < 50) nDeltaX = 0;
	if (abs(nDeltaY) < 50) nDeltaY = 0;
	m_pCamera->RotateLocalX(nDeltaY * fDelta);
	m_pCamera->RotateLocalY(nDeltaX * fDelta);

	if (KEY_MANAGER->isStayKeyDown('W'))
	{
		m_pCamera->MoveLocalZ(20.0f);
	}
	if (KEY_MANAGER->isStayKeyDown('S'))
	{
		m_pCamera->MoveLocalZ(-20.0f);
	}
	if (KEY_MANAGER->isStayKeyDown('A'))
	{
		m_pCamera->MoveLocalX(-0.5f);
	}
	if (KEY_MANAGER->isStayKeyDown('D'))
	{
		m_pCamera->MoveLocalX(0.5f);
	}
	if (KEY_MANAGER->isOnceKeyDown('1'))
	{
		DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);
	}
	if (KEY_MANAGER->isOnceKeyUp('1'))
	{
		DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	m_pCamera->Update();
	if (!KEY_MANAGER->isStayKeyDown(VK_SPACE))
	{
      		FRUSTUM_CULLING->Update();
	}
}
void cFrameworkTest::Render()
{
	m_pGrid->Render();
	m_pSky->Render();
	m_pTerrain->Render();
}
void cFrameworkTest::Release()
{
	// 전환 시점에 삭제할 것들
	SAFE_DELETE(m_pSky);
	SAFE_DELETE(m_pTerrain);
}
void cFrameworkTest::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//m_pCamera->WndProc(hWnd, message, wParam, lParam);
}