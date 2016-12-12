#include "stdafx.h"
#include "cTerrainObject.h"

zQuadTree::zQuadTree(int cx, int cy)
	: m_fRadius(0.0f), m_bCulled(false)
{
	int i;
	m_nCenter = 0;
	ZeroMemory(m_pChild, sizeof(zQuadTree*) * 4);
	m_nCorner[CORNER_TL] = 0;
	m_nCorner[CORNER_TR] = cx - 1;
	m_nCorner[CORNER_BL] = cx * (cy - 1);
	m_nCorner[CORNER_BR] = cx * cy - 1;
	m_nCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR]
		+ m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 4;
}
zQuadTree::zQuadTree(zQuadTree* pParent)
	: m_fRadius(0.0f), m_bCulled(false)
{
	m_nCenter = 0;
	ZeroMemory(m_pChild, sizeof(zQuadTree*) * 4);
	ZeroMemory(m_nCorner, sizeof(int) * 4);
}
zQuadTree::~zQuadTree()
{
	Destroy();
}

zQuadTree* zQuadTree::AddChild(int nCornerTL, int nCornerTR, int nCornerBR, int nCornerBL)
{
	auto pChild = new zQuadTree(this);
	pChild->SetCorners(nCornerTL, nCornerTR, nCornerBL, nCornerBR);
	return pChild;
}
bool zQuadTree::SetCorners(int nCornerTL, int nCornerTR, int nCornerBR, int nCornerBL)
{
	m_nCorner[CORNER_TL] = nCornerTL;
	m_nCorner[CORNER_TR] = nCornerTR;
	m_nCorner[CORNER_BL] = nCornerBR;
	m_nCorner[CORNER_BR] = nCornerBL;
	m_nCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR]
		+ m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 4;
	return true;
}
bool zQuadTree::SubDivide()
{
	auto nTopEdgeCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR]) / 2;
	auto nBottomEdgeCenter = (m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 2;
	auto nLeftEdgeCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_BL]) / 2;
	auto nRightEdgeCenter = (m_nCorner[CORNER_TR] + m_nCorner[CORNER_BR]) / 2;
	auto nCentralPoint = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR]
		+ m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 4;
	
	if (m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL] <= 1)
	{
		return false;
	}
	m_pChild[CORNER_TL] = AddChild(m_nCorner[CORNER_TL], nTopEdgeCenter, nLeftEdgeCenter, nCentralPoint);
	m_pChild[CORNER_TR] = AddChild(nTopEdgeCenter, m_nCorner[CORNER_TR], nCentralPoint,nRightEdgeCenter);
	m_pChild[CORNER_BL] = AddChild(nLeftEdgeCenter, nCentralPoint, m_nCorner[CORNER_BL], nBottomEdgeCenter);
	m_pChild[CORNER_BR] = AddChild(nCentralPoint, nRightEdgeCenter, nBottomEdgeCenter, m_nCorner[CORNER_BR]);

	return true;
}
int zQuadTree::GenTriIndex(int nTriangles, LPVOID pIndex)
{
	if (m_bCulled)
	{
		m_bCulled = false;
		return nTriangles;
	}
	if (IsVisible())
	{
		LPDWORD p = (LPDWORD)pIndex + nTriangles * 3;
		*p++ = m_nCorner[0];
		*p++ = m_nCorner[1];
		*p++ = m_nCorner[2];
		nTriangles++;
		*p++ = m_nCorner[2];
		*p++ = m_nCorner[1];
		*p++ = m_nCorner[3];
		nTriangles++;
	}
	if (m_pChild[CORNER_TL]) nTriangles = m_pChild[CORNER_TL]->GenTriIndex(nTriangles, pIndex);
	if (m_pChild[CORNER_TR]) nTriangles = m_pChild[CORNER_TR]->GenTriIndex(nTriangles, pIndex);
	if (m_pChild[CORNER_BL]) nTriangles = m_pChild[CORNER_BL]->GenTriIndex(nTriangles, pIndex);
	if (m_pChild[CORNER_BR]) nTriangles = m_pChild[CORNER_BR]->GenTriIndex(nTriangles, pIndex);
	
	return nTriangles;
}
	void zQuadTree::Destroy()
{
	for (int i = 0; i < 4; i++)
	{
		SAFE_DELETE(m_pChild[i]);
	}
}
bool zQuadTree::Build()
{
	if (SubDivide())
	{
		m_pChild[CORNER_TL]->Build();
		m_pChild[CORNER_TR]->Build();
		m_pChild[CORNER_BL]->Build();
		m_pChild[CORNER_BR]->Build();
	}
	return true;
}
int zQuadTree::GenerateIndex(LPVOID pIB, std::vector<std::vector<TerrainCell>>* heightMap, int Size)
{
	FrustumCull(heightMap, Size);
	return GenTriIndex(0, pIB);
}
int zQuadTree::IsInFrusum(std::vector<std::vector<TerrainCell>>* heightMap, int Size)
{
	bool b[4];
	bool bInSphere;
	ST_SPHERE sphere((*heightMap)[m_nCenter / Size][m_nCenter % Size].vPos, m_fRadius, false);
	if (!FRUSTUM_CULLING->Intersect(&sphere)) return FRUSTUM_OUT;

	sphere.vCenter = (*heightMap)[m_nCorner[0] / Size][m_nCorner[0] % Size].vPos;
	b[0] = FRUSTUM_CULLING->Intersect(&sphere);
	sphere.vCenter = (*heightMap)[m_nCorner[1] / Size][m_nCorner[1] % Size].vPos;
	b[1] = FRUSTUM_CULLING->Intersect(&sphere);
	sphere.vCenter = (*heightMap)[m_nCorner[2] / Size][m_nCorner[2] % Size].vPos;
	b[2] = FRUSTUM_CULLING->Intersect(&sphere);
	sphere.vCenter = (*heightMap)[m_nCorner[3] / Size][m_nCorner[3] % Size].vPos;
	b[3] = FRUSTUM_CULLING->Intersect(&sphere);

	if (b[0] && b[1] && b[2] && b[3]) return FRUSTUM_COMPLETELY_IN;
	return FRUSTUM_PARTIALLY_IN;
}
void zQuadTree::FrustumCull(std::vector<std::vector<TerrainCell>>* heightMap, int Size)
{
	int ret;
	ret = IsInFrusum(heightMap, Size);
	switch (ret)
	{
	case FRUSTUM_COMPLETELY_IN:
		m_bCulled = false;	return;
	case FRUSTUM_PARTIALLY_IN:
		m_bCulled = false; break;
	case FRUSTUM_OUT:
		m_bCulled = true;	return;
	}
	if (m_pChild[0]) m_pChild[0]->FrustumCull(heightMap, Size);
	if (m_pChild[1]) m_pChild[1]->FrustumCull(heightMap, Size);
	if (m_pChild[2]) m_pChild[2]->FrustumCull(heightMap, Size);
	if (m_pChild[3]) m_pChild[3]->FrustumCull(heightMap, Size);
}

cTerrainObject::cTerrainObject()
	: m_cxDIB(0), m_cyDIB(0), m_czDIB(0)
	, m_vfScale(1.0f,1.0f,1.0f)
	, m_pMesh(nullptr), m_pShader(nullptr)
	, m_nTriangles(0), m_pQuadTree(nullptr)
{
	ZeroMemory(m_pTex, TEXTURE_NUM * sizeof(LPDIRECT3DTEXTURE9));
}


cTerrainObject::~cTerrainObject()
{
	Destroy();
}

void cTerrainObject::Load(std::string szHeightMapPath, std::string szTexturePath[4], int nSize, D3DXVECTOR3* pvfScale)
{
	m_vfScale = *pvfScale;
	m_cxDIB = m_czDIB = nSize;
	assert(SUCCEEDED(BuildHeightMap(szHeightMapPath)) && "높이 맵 읽기 실패");
	
	for (int i = 0; i < TEXTURE_NUM; i++)
	{
		m_pTex[i] = TEXTURE_MANAGER->GetTexture(szTexturePath[i]);
	}
	m_pShader = SHADER_MANAGER->GetShader(eShaderType::ST_NORMAL);

	assert(SUCCEEDED(CreateMesh()) && "매쉬 만들기 실패");
	m_pQuadTree = new zQuadTree(m_cxDIB, m_czDIB);
	assert(SUCCEEDED(BuildQuadTree()) && "쿼드 트리 만들기 실패");
}
void cTerrainObject::Destroy()
{
	SAFE_DELETE(m_pQuadTree);
	SAFE_RELEASE(m_pMesh);
}
HRESULT cTerrainObject::BuildHeightMap(std::string szHeightMapPath)
{
	auto _numVertices = m_cxDIB * m_czDIB;

	std::vector<BYTE> vecHeight(_numVertices);
	FILE* _fp = nullptr;
	std::string szHeightPath = "./Objects/Surface/" + szHeightMapPath;
	
	fopen_s(&_fp, szHeightPath.c_str(), "rb");
	fread_s(&vecHeight[0], sizeof(BYTE) * _numVertices, sizeof(BYTE), _numVertices, _fp);
	fclose(_fp);

	m_vecTerrainCells.resize(m_czDIB);
	for (int z = 0; z < m_czDIB; z++)
	{
		std::vector<TerrainCell> vecCell(m_cxDIB);
		for (int x = 0; x < m_cxDIB; x++)
		{
			vecCell[x] = TerrainCell{
				D3DXVECTOR3{ static_cast<float>(x - m_cxDIB / 2) * m_vfScale.x
				, static_cast<float>(vecHeight[z * m_cxDIB + x]) * m_vfScale.y
				, -static_cast<float>(z - m_czDIB / 2)* m_vfScale.z }
			,D3DXVECTOR2{static_cast<float>(x) / (m_cxDIB - 1), static_cast<float>(z) / (m_czDIB - 1)}};
		}
		m_vecTerrainCells[z] = vecCell;
	}
	return S_OK;
}
HRESULT cTerrainObject::BuildQuadTree()
{
	m_pQuadTree->Build();
	return S_OK;
}
HRESULT cTerrainObject::CreateMesh()
{
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


	auto _numCellsPerRow = m_cxDIB - 1;
	auto _numCellsPerCol = m_czDIB - 1;
	auto _numVertices = m_cxDIB * m_czDIB;
	auto _numTriangles = _numCellsPerRow * _numCellsPerCol * 2;
	D3DXCreateMesh(_numCellsPerRow * _numCellsPerCol * 2, _numVertices, D3DXMESH_MANAGED | D3DXMESH_32BIT, descVert, DEVICE, &m_pMesh);

	void* vertexData = nullptr;
	m_pMesh->LockVertexBuffer(D3DUSAGE_WRITEONLY, &vertexData);
	{
		auto data = static_cast<float*>(vertexData);
		int i = 0;
		for (int z = 0; z < m_czDIB; z++)
		{
			for (int x = 0; x < m_cxDIB; x++)
			{
				*data++ = m_vecTerrainCells[z][x].vPos.x;
				*data++ = m_vecTerrainCells[z][x].vPos.y;
				*data++ = m_vecTerrainCells[z][x].vPos.z;
				*data++ = m_vecTerrainCells[z][x].vUV.x;
				*data++ = m_vecTerrainCells[z][x].vUV.y;
			}
		}
	}
	m_pMesh->UnlockVertexBuffer();

	DWORD* pA = nullptr;
	m_pMesh->LockAttributeBuffer(0, &pA);
	{
		memset(pA, 0, _numTriangles * sizeof(DWORD));
	}
	m_pMesh->UnlockAttributeBuffer();
	return S_OK;
}
void cTerrainObject::Render()
{
	LPDIRECT3DINDEXBUFFER9 lp;
	LPDWORD pl;
	m_pMesh->GetIndexBuffer(&lp);
	lp->Lock(0, (m_cxDIB - 1)* (m_czDIB - 1) * 2 * sizeof(DWORD), (void**)&pl, 0);
	m_nTriangles = m_pQuadTree->GenerateIndex(pl, &m_vecTerrainCells, m_cxDIB);
	lp->Unlock();
	
	//DWORD* adjacencyInfo = new DWORD[m_pMesh->GetNumFaces() * 3];
	//m_pMesh->GenerateAdjacency(0.0f, adjacencyInfo);
	//m_pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE | D3DXMESHOPT_COMPACT, adjacencyInfo, NULL, NULL, NULL);


	D3DXMATRIX mat, matView, matProj;
	DEVICE->GetTransform(D3DTS_VIEW, &matView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);
	mat = matView * matProj;
	m_pShader->SetMatrix("matViewProjection", &mat);

	D3DXMatrixIdentity(&mat);
	m_pShader->SetMatrix("matWorld", &mat);
	m_pShader->SetTexture("DiffuseMap_Tex", m_pTex[0]);

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
	SAFE_RELEASE(lp);
}
