#include "stdafx.h"
#include "cSurfaceObject.h"


cSurfaceObject::cSurfaceObject() : cGameObject::cGameObject()
{

}

void cSurfaceObject::Load(std::string szHeightMapPath, std::string szTexturePath
	, int numVertsPerRow, int numVertsPerCol, float cellSpacing, float heightScale)
{
	std::string szTexPath = "./Objects/Surface/" + szTexturePath;
	m_pTex = TEXTURE_MANAGER->GetTexture(szTexPath);

	m_pShader = SHADER_MANAGER->GetShader(eShaderType::ST_NORMAL);



	auto _numVertsPerRow = numVertsPerRow;
	auto _numVertsPerCol = numVertsPerCol;
	auto _cellSpacing = cellSpacing;
	auto _numCellsPerRow = _numVertsPerRow - 1;
	auto _numCellsPerCol = _numVertsPerCol - 1;
	auto _width = _numCellsPerRow * _cellSpacing;
	auto _depth = _numCellsPerCol * _cellSpacing;
	auto _numVertices = _numVertsPerRow * _numVertsPerCol;
	auto _numTriangles = _numCellsPerRow * _numCellsPerCol * 2;

	std::vector<BYTE> vecHeight(_numVertices);
	FILE* _fp = nullptr;
	std::string szHeightPath = "./Objects/Surface/" + szHeightMapPath;
	fopen_s(&_fp, szHeightPath.c_str(), "rb");
	fread_s(&vecHeight[0], sizeof(BYTE) * _numVertices, sizeof(BYTE), _numVertices, _fp);
	fclose(_fp);

	m_vecTerrainCells.resize(_numVertsPerCol);
	for (int i = 0; i < _numVertsPerCol; i++)
	{
		std::vector<TerrainCell> vecCell(_numVertsPerRow);
		for (int j = 0; j < _numVertsPerRow; j++)
		{
			vecCell[j] = TerrainCell{ 
				D3DXVECTOR3{static_cast<float>(j), 
				static_cast<float>(vecHeight[i * _numVertsPerRow + j]) * heightScale , static_cast<float>(i) },
				false };
		}
		m_vecTerrainCells[i] = vecCell;
	}


	CreateMyMesh(_numTriangles, _numVertices);

	auto startX = -_width / 2;
	auto startZ = _depth / 2;
	auto endX = _width / 2;
	auto endZ = - _depth / 2;
	m_vSize[0] = { startX, 0, startZ};
	m_vSize[1] = {endX, 0, endZ};

	auto uCoordIncrementSize = 1.0f / static_cast<float>(_numCellsPerRow);
	auto vCoordIncrementSize = 1.0f / static_cast<float>(_numCellsPerCol);

	void* vertexData = nullptr;
	m_pMesh->LockVertexBuffer(D3DUSAGE_WRITEONLY, &vertexData);
	{
		auto data = static_cast<float*>(vertexData);
		int i = 0;
		for (float z = startZ; z >= endZ; z -= _cellSpacing)
		{
			int j = 0;
			for (float x = startX; x <= endX; x += _cellSpacing)
			{			
				*data++ = x;
				*data++ = m_vecTerrainCells[i][j].vPos.y;
				*data++ = z;
				*data++ = j* uCoordIncrementSize;
				*data++ = i* vCoordIncrementSize;
				j++;
			}
			i++;
		}
	}
	m_pMesh->UnlockVertexBuffer();

	void* indexData = nullptr;
	m_pMesh->LockIndexBuffer(0, &indexData);
	{
		auto ind = static_cast<DWORD*>(indexData);
		for (int i = 0; i < _numCellsPerCol; i++)
		{
			for (int j = 0; j < _numCellsPerRow; j++)
			{
				*ind++ = i * _numVertsPerRow + j;
				*ind++ = i * _numVertsPerRow + j + 1;
				*ind++ = (i + 1) * _numVertsPerRow + j;
				*ind++ = (i + 1) * _numVertsPerRow + j;
				*ind++ = i * _numVertsPerRow + j + 1;
				*ind++ = (i + 1) * _numVertsPerRow + j + 1;
				
			}
		}
	}
	m_pMesh->UnlockIndexBuffer();

	DWORD* pA = nullptr;
	m_pMesh->LockAttributeBuffer(0, &pA);
	{
		memset(pA, 0, _numTriangles * sizeof(DWORD));
	}
	m_pMesh->UnlockAttributeBuffer();

	DWORD* adjacencyInfo = new DWORD[m_pMesh->GetNumFaces() * 3];
	m_pMesh->GenerateAdjacency(0.0f, adjacencyInfo);

	m_pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE | D3DXMESHOPT_COMPACT, adjacencyInfo, NULL, NULL, NULL);
}
void cSurfaceObject::CreateMyMesh(int numFace, int numVer)
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

	D3DXCreateMesh(numFace, numVer, D3DXMESH_MANAGED | D3DXMESH_32BIT,descVert, DEVICE, &m_pMesh);
}

cSurfaceObject::~cSurfaceObject()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pTex);
}


void cSurfaceObject::Update()
{
	
}
void cSurfaceObject::Render()
{
	D3DXMATRIX mat, matView, matProj;
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
	m_pShader->SetTexture("DiffuseMap_Tex", m_pTex);

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


bool cSurfaceObject::GetHeight(float x, float& y, float z)
{
	float _x = x - m_vPosition.x;
	float _z = z - m_vPosition.z;
	if (m_vSize[0].x < _x && m_vSize[1].x > _x && m_vSize[0].z < _z && m_vSize[1].z > _z)
	{
		
	}
	return false;
}