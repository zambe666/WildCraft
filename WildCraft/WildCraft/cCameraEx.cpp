#include "stdafx.h"
#include "cCameraEx.h"


cCameraEx::cCameraEx()
	:m_vEye(0, 0, 0), m_vLooat(0,0,-1.0f), m_vUp(0, 1.0f, 0)
	, m_vView(0,0,0), m_vCross(0, 0, 0)
{
}


cCameraEx::~cCameraEx()
{
}
D3DXMATRIXA16* cCameraEx::SetView(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvLookat, D3DXVECTOR3* pvUp)
{
	m_vEye = *pvEye;
	m_vLooat = *pvLookat;
	m_vUp = *pvUp;
	D3DXVec3Normalize(&m_vView, &(m_vLooat - m_vEye));
	D3DXVec3Cross(&m_vCross, &m_vUp, &m_vView);
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLooat, &m_vUp);
	return &m_matView;
}
void cCameraEx::Update()
{
	DEVICE->SetTransform(D3DTS_VIEW, &m_matView);
}
D3DXMATRIXA16* cCameraEx::RotateLocalX(float angle)
{
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationAxis(&matRot, &m_vCross, angle);
	D3DXVECTOR3 vNewDst;
	D3DXVec3TransformCoord(&vNewDst, &m_vView, &matRot);
	vNewDst += m_vEye;
	return SetView(&m_vEye, &vNewDst, &m_vUp);
}
D3DXMATRIXA16* cCameraEx::RotateLocalY(float angle)
{
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationAxis(&matRot, &m_vUp, angle);
	D3DXVECTOR3 vNewDst;
	D3DXVec3TransformCoord(&vNewDst, &m_vView, &matRot);
	vNewDst += m_vEye;
	return SetView(&m_vEye, &vNewDst, &m_vUp);
}
D3DXMATRIXA16* cCameraEx::RotateLocalZ(float angle)
{
	
	return &m_matView;
}

D3DXMATRIXA16*  cCameraEx::MoveTo(D3DXVECTOR3* pv)
{
	D3DXVECTOR3 dv = *pv - m_vEye;
	m_vEye = *pv;
	m_vLooat += dv;
	return SetView(&m_vEye, &m_vLooat, &m_vUp);
}
D3DXMATRIXA16*  cCameraEx::MoveLocalX(float dist)
{
	D3DXVECTOR3 vNewEye = m_vEye;
	D3DXVECTOR3 vNewDst = m_vLooat;
	D3DXVECTOR3	vMove;

	D3DXVec3Normalize(&vMove, &m_vCross);
	vMove *= dist;
	vNewEye += vMove;
	vNewDst += vMove;
	return SetView(&vNewEye, &vNewDst, &m_vUp);
}
D3DXMATRIXA16*  cCameraEx::MoveLocalY(float dist)
{
	D3DXVECTOR3 vNewEye = m_vEye;
	D3DXVECTOR3 vNewDst = m_vLooat;
	D3DXVECTOR3	vMove;

	D3DXVec3Normalize(&vMove, &m_vUp);
	vMove *= dist;
	vNewEye += vMove;
	vNewDst += vMove;
	return SetView(&vNewEye, &vNewDst, &m_vUp);
}
D3DXMATRIXA16*  cCameraEx::MoveLocalZ(float dist)
{
	D3DXVECTOR3 vNewEye = m_vEye;
	D3DXVECTOR3 vNewDst = m_vLooat;
	D3DXVECTOR3	vMove;

	D3DXVec3Normalize(&vMove, &m_vView);
	vMove *= dist;
	vNewEye += vMove;
	vNewDst += vMove;
	return SetView(&vNewEye, &vNewDst, &m_vUp);
}