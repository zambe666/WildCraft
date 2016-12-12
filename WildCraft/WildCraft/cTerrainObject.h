#pragma once
struct TerrainCell
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR2 vUV;
};

class zQuadTree
{
	enum eCornerType { CORNER_TL, CORNER_TR, CORNER_BL, CORNER_BR };
	enum eQuadLocation { FRUSTUM_OUT = 0, FRUSTUM_PARTIALLY_IN = 1, FRUSTUM_COMPLETELY_IN = 2, FRUSTUM_UNKOWN = -1};
private:
	zQuadTree*	m_pChild[4];
	int			m_nCenter;
	int			m_nCorner[4];
	bool		m_bCulled;
	float		m_fRadius;
private:
	zQuadTree* AddChild(int nCornerTL, int nCornerTR, int nCornerBR, int nCornerBL);
	bool SetCorners(int nCornerTL, int nCornerTR, int nCornerBR, int nCornerBL);
	bool SubDivide();		// 쪼개기 수행
	bool IsVisible() { return (m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL] <= 1); }
	int GenTriIndex(int nTriangles, LPVOID pIndex);	// 인덱스 생성
	void Destroy();
public:
	zQuadTree(int cx, int cy);
	zQuadTree(zQuadTree* pParent);
	~zQuadTree();
	bool Build();		// 구축
	int GenerateIndex(LPVOID pIB, std::vector<std::vector<TerrainCell>>* heightMap, int Size );
	int IsInFrusum(std::vector<std::vector<TerrainCell>>* heightMap, int Size);
	void FrustumCull(std::vector<std::vector<TerrainCell>>* heightMap, int Size);
};

class cTerrainObject
{
private:
	enum 상수 { TEXTURE_NUM = 3 };
	
	std::vector<std::vector<TerrainCell>> m_vecTerrainCells;

	int					m_cxDIB;			// 가로 픽셀
	int					m_czDIB;			// 세로 픽셀 
	int					m_cyDIB;			// 최대 높이
	D3DXVECTOR3			m_vfScale;			// 스케일값
	LPDIRECT3DTEXTURE9	m_pTex[TEXTURE_NUM];// 텍스처
	LPD3DXMESH			m_pMesh;			// 그릴 메쉬
	LPD3DXEFFECT		m_pShader;			// 그릴 쉐이더
	int					m_nTriangles;		// 그릴 삼각형
	zQuadTree*			m_pQuadTree;		// 쿼드 포인터
public:
	cTerrainObject();
	~cTerrainObject();
	void Load(std::string szHeightMapPath, std::string szTexturePath[TEXTURE_NUM],int nSize, D3DXVECTOR3* pvfScale);
private:
	void Destroy();
	HRESULT BuildHeightMap(std::string szHeightMapPath);
	HRESULT BuildQuadTree();
	HRESULT CreateMesh();
	
public:
	TerrainCell* GetVertex(int x, int z) { return &m_vecTerrainCells[x][z]; };
	float GetHeight(int x, int z) { return GetVertex(x, z)->vPos.y; };
	int GetCXDIB() { return m_cxDIB; } //가로 픽셀
	int GetCZDIB() { return m_czDIB; } 
	float GetCXTerrain() { return m_cxDIB * m_vfScale.x; } // 실제 높이
	float GetCYTerrain() { return m_cyDIB * m_vfScale.y; }
	float GetCZTerrain() { return m_czDIB * m_vfScale.z; }
	
	void Render();
};
