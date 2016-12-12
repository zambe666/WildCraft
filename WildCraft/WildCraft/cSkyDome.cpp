#include "stdafx.h"
#include "cSkyDome.h"


cSkyDome::cSkyDome()
	: m_pSkyTex(nullptr), m_pMesh(nullptr), m_pShader(nullptr)
	, m_fRadius(1.0f)
	, m_nDtheta(15), m_nDphi(15), m_nNumVertices(0)
{
}


cSkyDome::~cSkyDome()
{
	SAFE_RELEASE(m_pMesh);
}

HRESULT cSkyDome::InitSkyDome(std::string strTexName, int dtheta, int dphi, int radius)
{
	m_nDphi = dphi;
	m_nDtheta = dtheta;
	m_fRadius = radius;

	SetupVertex();
	m_pSkyTex = TEXTURE_MANAGER->GetTexture(strTexName);
	m_pShader = SHADER_MANAGER->GetShader(eShaderType::ST_SKY);
	return S_OK;
}
void cSkyDome::Render()
{
	D3DXMATRIXA16 matView, matProj;
	D3DXMATRIXA16 mat;
	DEVICE->GetTransform(D3DTS_VIEW, &matView);
	matView._41 = matView._42 = matView._43 = 0.0f;
	DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);
	mat = matView * matProj;
	m_pShader->SetMatrix("matViewProjection", &mat);

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//컬링은 양면
	DEVICE->SetRenderState(D3DRS_ZENABLE, FALSE);			//Z버퍼 끄기

	D3DXMatrixIdentity(&mat);
	m_pShader->SetMatrix("matWorld", &mat);

	m_pShader->SetTexture("DiffuseMap_Tex", m_pSkyTex);

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
	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//컬링은 양면
	DEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);
}
HRESULT cSkyDome::SetupVertex()
{
	m_nNumVertices = static_cast<int>(360.0f/m_nDtheta * 90.0f/m_nDphi * 4);
	assert(SUCCEEDED(CreateMyMesh()) && "매쉬 생성 실패");
	

	void* vertexData = nullptr;

	m_pMesh->LockVertexBuffer(D3DUSAGE_WRITEONLY, &vertexData);
	{
		auto data = static_cast<float*>(vertexData);
		int pos = -50;
		for (int phi = 0; phi < 90; phi += m_nDphi)
		{
			for (int theta = 0; theta < 360; theta += m_nDtheta)
			{
				*data++ = m_fRadius * sin(DegToRad(phi)) * cos(DegToRad(theta));
				*data++ = m_fRadius * cos(DegToRad(phi)) + pos;
				*data++ = m_fRadius * sin(DegToRad(phi)) * sin(DegToRad(theta));
				*data++ = DegToRad(phi);
				*data++ = DegToRad(theta);
		
				// 위도 증가
				*data++ = m_fRadius * sin(DegToRad(phi + m_nDphi)) * cos(DegToRad(theta));
				*data++ = m_fRadius * cos(DegToRad(phi + m_nDphi)) + pos;
				*data++ = m_fRadius * sin(DegToRad(phi + m_nDphi)) * sin(DegToRad(theta));
				*data++ = DegToRad(phi + m_nDphi);
				*data++ = DegToRad(theta);
		

				// 경도 증가
				*data++ = m_fRadius * sin(DegToRad(phi)) * cos(DegToRad(theta + m_nDtheta));
				*data++ = m_fRadius * cos(DegToRad(phi)) + pos;
				*data++ = m_fRadius * sin(DegToRad(phi)) * sin(DegToRad(theta + m_nDtheta));
				*data++ = DegToRad(phi);
				*data++ = DegToRad(theta + m_nDtheta);

				if (phi > -90 && phi < 90)
				{
					*data++ = m_fRadius * sin(DegToRad(phi + m_nDphi)) * cos(DegToRad(theta + m_nDtheta));
					*data++ = m_fRadius * cos(DegToRad(phi + m_nDphi)) + pos;
					*data++ = m_fRadius * sin(DegToRad(phi + m_nDphi)) * sin(DegToRad(theta + m_nDtheta));

					*data++ = DegToRad(phi + m_nDphi);
					*data++ = DegToRad(theta + m_nDtheta);
				}
			}
		}
	}
	m_pMesh->UnlockVertexBuffer();

	void* indexData = nullptr;
	m_pMesh->LockIndexBuffer(0, &indexData);
	{
		auto ind = static_cast<WORD*>(indexData);
		for (int i = 0; i < m_nNumVertices; i++)
		{
				*ind++ = i;
		}
	}
	m_pMesh->UnlockIndexBuffer();

	DWORD* pA = nullptr;
	m_pMesh->LockAttributeBuffer(0, &pA);
	{
		memset(pA, 0, (m_nNumVertices-2) * sizeof(DWORD));
	}
	m_pMesh->UnlockAttributeBuffer();

	DWORD* adjacencyInfo = new DWORD[m_pMesh->GetNumFaces() * 3];
	m_pMesh->GenerateAdjacency(0.0f, adjacencyInfo);

	m_pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE | D3DXMESHOPT_COMPACT, adjacencyInfo, NULL, NULL, NULL);
	return S_OK;
}

HRESULT cSkyDome::CreateMyMesh()
{
	SAFE_RELEASE(m_pMesh);

	D3DVERTEXELEMENT9 descVert[3];
	int offset = 0; int i = 0;
	descVert[i].Stream = 0;
	descVert[i].Offset = offset;
	descVert[i].Type = D3DDECLTYPE_FLOAT3;
	descVert[i].Method = D3DDECLMETHOD_DEFAULT;
	descVert[i].Usage = D3DDECLUSAGE_POSITION;
	descVert[i].UsageIndex = 0;

	offset += sizeof(float) * 3; ++i;
	descVert[i].Stream = 0;
	descVert[i].Offset = offset;
	descVert[i].Type = D3DDECLTYPE_FLOAT2;
	descVert[i].Method = D3DDECLMETHOD_DEFAULT;
	descVert[i].Usage = D3DDECLUSAGE_TEXCOORD;
	descVert[i].UsageIndex = 0;

	descVert[i + 1] = D3DDECL_END();

	D3DXCreateMesh(m_nNumVertices - 2, m_nNumVertices, D3DXMESH_MANAGED, descVert, DEVICE, &m_pMesh);
	return S_OK;
}