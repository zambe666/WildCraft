#include "stdafx.h"
#include "cFrameworkTest.h"
#include "cCamera.h"
#include "cSurfaceObject.h"
#include "cStaticObject.h"

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

	m_pMainCamera = new cCamera;
	m_pMainCamera->Init(eCameraType::CT_AIR);
	m_pMainCamera->SetPosition(D3DXVECTOR3(0, 0, -10));
	D3DXVECTOR3 center(0, 0, 0);
	m_pMainCamera->SetTargetVector(&center);
	
	m_pSurface = new cSurfaceObject("Map1.raw","Map1.jpg",257,257,10,0.1f);
	m_pSurface->SetPosition(D3DXVECTOR3(100,0,0));

	//m_pStatic = new cStaticObject()
	return S_OK;
}
void cFrameworkTest::Update()
{
	m_pMainCamera->Update();
	m_pSurface->Update();
}
void cFrameworkTest::Render()
{
	m_pGrid->Render();
	m_pSurface->Render();
}
void cFrameworkTest::Release()
{
	// 전환 시점에 삭제할 것들
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pMainCamera);
	SAFE_RELEASE(m_pSurface);
}
void cFrameworkTest::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pMainCamera->WndProc(hWnd, message, wParam, lParam);
}