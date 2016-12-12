#include "stdafx.h"
#include "cStaticObject.h"
#include "cStaticObjectManager.h"

cStaticObject::cStaticObject()
	: cGameObject::cGameObject(),
	m_pShader(nullptr), m_pMesh(nullptr)
{
}


cStaticObject::~cStaticObject()
{

}


cStaticObject::cStaticObject(std::string szFile)
	: cGameObject::cGameObject(),
	m_pShader(nullptr), m_pMesh(nullptr)
{
	//auto origObject = STATIC_OBJECT_MANAGER->Get
}

void cStaticObject::Update()
{

}

void cStaticObject::Render()
{
	/*D3DXMATRIX mat, matView, matProj;
	DEVICE->GetTransform(D3DTS_VIEW, &matView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);
	mat = matView * matProj;
	m_pShader->SetMatrix("matViewProjection", &mat);

	D3DXMATRIX matT, matR;
	D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &m_vDirection, &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&matR, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	mat = matR * matT;
	m_pShader->SetMatrix("matWorld", &mat);
	m_pShader->SetTexture("DiffuseMap_Tex", m_pTex);*/

	UINT numPasses = 0;
	m_pShader->Begin(&numPasses, NULL);
	{
		for (auto i = 0; i < numPasses; i++)
		{
			m_pShader->BeginPass(i);
			{
				m_pMesh->DrawSubset(0);
			}
			m_pShader->EndPass();
		}
	}
	m_pShader->End();
}

void cStaticObject::Destroy()
{
	for each(auto it in m_vecMtlTex)
	{
		SAFE_RELEASE(it);
	}
	m_vecMtlTex.clear();
}