#pragma once
#include "cGameObject.h"


// 이건 속성별로 안만들어도 됨

class cSurfaceObject : public cGameObject
{
private:
	struct TerrainCell
	{
		D3DXVECTOR3 vPos;
		bool	bBlock;
	};
	LPD3DXMESH			m_pMesh;				// 위치와 방향은 상속 받음
	LPDIRECT3DTEXTURE9  m_pTex;
	LPD3DXEFFECT		m_pShader;

	D3DXVECTOR3			m_vSize[2];
	std::vector<std::vector<TerrainCell>> m_vecTerrainCells;

public:
	cSurfaceObject();
	~cSurfaceObject();

	void Load(std::string szHeightMapPath, std::string szTexturePath
		, int numVertsPerRow, int numVertsPerCol, float cellSpacing, float heightScale);
	
	virtual void Update() override;
	virtual void Render() override;

	bool GetHeight(float x, float& y, float z);

private:
	void CreateMyMesh(int numFace, int numVer);
};

