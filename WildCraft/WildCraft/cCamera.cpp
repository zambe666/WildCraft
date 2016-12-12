#include "stdafx.h"
#include "cCamera.h"

cCamera::cCamera(void)
	: m_vLook(0, 0, 1)
	, m_vUp(0, 1, 0)
	, m_vPos(0, 0, 0)

	, m_pTarget(nullptr)
	, m_bEnable(false)
	, m_bTracking(false)

	, m_fAngleX(0.0f), m_fAngleY(0.0f)
	, m_fDistance(-10.0f)
{
}

cCamera::~cCamera(void)
{
}

void cCamera::Init(D3DXVECTOR3 pos, D3DXVECTOR3 vLook)
{
	m_vPos = pos;
	D3DXVec3Normalize(&m_vLook, &vLook);
	m_vLook = m_vPos + m_vLook;
	Update();
}
void cCamera::SetTarget(D3DXVECTOR3* pTarget, bool bTracking)
{
	if (pTarget)
	{
		m_pTarget = pTarget;
		m_vLook = *m_pTarget;
		m_bTracking = bTracking;
	}
}
void cCamera::Update()
{
	if (m_bEnable)
	{
		POINT pt;
		GetCursorPos(&pt);
		RECT rc;
		GetWindowRect(g_hWnd, &rc);
		int nDeltaX = pt.x - (rc.left + WIN_SIZE_WIDTH / 2);
		int nDeltaY = pt.y - (rc.top + WIN_SIZE_HEIGHT / 2);
		if (abs(nDeltaX) < 50) nDeltaX = 0;
		if (abs(nDeltaY) < 50) nDeltaY = 0;

		auto AngleMax = D3DX_PI / 2.0f - EPSILON;
		m_fAngleX += nDeltaY * 0.00001f;
		if (m_fAngleX > AngleMax)	m_fAngleX = AngleMax;
		else if (m_fAngleX < -AngleMax)	m_fAngleX = -AngleMax;
		m_fAngleY -= nDeltaX * 0.00001f;
		if (m_fAngleY > AngleMax)	m_fAngleY = AngleMax;
		else if (m_fAngleY < -AngleMax)	m_fAngleY = -AngleMax;
	}
	else
	{
		m_fAngleX = m_fAngleY = 0;
	}
	D3DXMATRIXA16 matRX, matRY, mat;
	D3DXMatrixRotationX(&matRX, m_fAngleX);
	D3DXMatrixRotationY(&matRY, -m_fAngleY);
	mat = matRX * matRY;
	
	if (m_pTarget)
	{
		m_vLook = *m_pTarget;
		if (m_bTracking)
		{		
			D3DXVec3TransformCoord(&m_vPos, &D3DXVECTOR3(0, 0, m_fDistance), &mat);
			m_vPos = m_vPos + *m_pTarget;
		}
	}
	else
	{
		//D3DXVec3TransformCoord(&m_vLook, &D3DXVECTOR3(0, 0, 1), &mat);
		//m_vLook = m_vPos + m_vLook;
	}
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vPos, &m_vLook, &m_vUp);
	DEVICE->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
	{
	}
	break;
	case WM_MOUSEWHEEL:
	{
		if (m_bEnable)
		{
			int n = GET_WHEEL_DELTA_WPARAM(wParam);
			m_fDistance -= n / 100.f;
		}
	}
	break;
	}
}
