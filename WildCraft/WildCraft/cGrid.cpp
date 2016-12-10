#include "stdafx.h"
#include "cGrid.h"


cGrid::cGrid()
{
}


cGrid::~cGrid()
{
}

void cGrid::Init(int nNumLine)
{
	float fWidth = 1.0f;
	int nHalf = nNumLine / 2;
	float fMax = nHalf * fWidth;

	D3DCOLOR c = D3DCOLOR_XRGB(128, 128, 128);
	for (int i = 1; i <= nHalf; ++i)
	{
		c = D3DCOLOR_XRGB(128, 128, 128);
		if (i % 5 == 0)
		{
			c = D3DCOLOR_XRGB(255, 255, 255);
		}
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-fMax, 0, i * fWidth), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(fMax, 0, i * fWidth), c));

		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-fMax, 0, -i * fWidth), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(fMax, 0, -i * fWidth), c));

		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(i * fWidth, 0, -fMax), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(i * fWidth, 0, fMax), c));

		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-i * fWidth, 0, -fMax), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-i * fWidth, 0, fMax), c));
	}

	c = D3DCOLOR_XRGB(255, 0, 0);
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-fMax, 0, 0), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(fMax, 0, 0), c));

	c = D3DCOLOR_XRGB(0, 255, 0);
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(0, -fMax, 0), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(0, fMax, 0), c));

	c = D3DCOLOR_XRGB(0, 0, 255);
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(0, 0, -fMax), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(0, 0, fMax), c));

}

void cGrid::Render()
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetTexture(0, NULL);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	DEVICE->SetTransform(D3DTS_WORLD, &matWorld);
	DEVICE->SetFVF(ST_PC_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertex.size() / 2,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));
}
