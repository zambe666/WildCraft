#pragma once
#include "cGameObject.h"

class cSurfaceObject : public cGameObject
{
private:
	struct TerrainCell
	{
		POINT	pos;
		bool	bBlock;
	};
	LPD3DXMESH			m_pMesh;		// 위치와 방향은 상속 받음
	LPDIRECT3DTEXTURE9  m_pTex;
	LPD3DXEFFECT		m_pShader;
public:
	cSurfaceObject(std::string szHeightMapPath, std::string szTexturePath
	, int numVertsPerRow, int numVertsPerCol, int cellSpacing, float heightScale);
	~cSurfaceObject();


	virtual void Update() override;
	virtual void Render() override;
private:
	void CreateMyMesh(int numFace, int numVer);
};

