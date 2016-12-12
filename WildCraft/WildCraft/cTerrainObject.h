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
	bool SubDivide();		// �ɰ��� ����
	bool IsVisible() { return (m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL] <= 1); }
	int GenTriIndex(int nTriangles, LPVOID pIndex);	// �ε��� ����
	void Destroy();
public:
	zQuadTree(int cx, int cy);
	zQuadTree(zQuadTree* pParent);
	~zQuadTree();
	bool Build();		// ����
	int GenerateIndex(LPVOID pIB, std::vector<std::vector<TerrainCell>>* heightMap, int Size );
	int IsInFrusum(std::vector<std::vector<TerrainCell>>* heightMap, int Size);
	void FrustumCull(std::vector<std::vector<TerrainCell>>* heightMap, int Size);
};

class cTerrainObject
{
private:
	enum ��� { TEXTURE_NUM = 3 };
	
	std::vector<std::vector<TerrainCell>> m_vecTerrainCells;

	int					m_cxDIB;			// ���� �ȼ�
	int					m_czDIB;			// ���� �ȼ� 
	int					m_cyDIB;			// �ִ� ����
	D3DXVECTOR3			m_vfScale;			// �����ϰ�
	LPDIRECT3DTEXTURE9	m_pTex[TEXTURE_NUM];// �ؽ�ó
	LPD3DXMESH			m_pMesh;			// �׸� �޽�
	LPD3DXEFFECT		m_pShader;			// �׸� ���̴�
	int					m_nTriangles;		// �׸� �ﰢ��
	zQuadTree*			m_pQuadTree;		// ���� ������
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
	int GetCXDIB() { return m_cxDIB; } //���� �ȼ�
	int GetCZDIB() { return m_czDIB; } 
	float GetCXTerrain() { return m_cxDIB * m_vfScale.x; } // ���� ����
	float GetCYTerrain() { return m_cyDIB * m_vfScale.y; }
	float GetCZTerrain() { return m_czDIB * m_vfScale.z; }
	
	void Render();
};
