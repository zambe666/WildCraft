#pragma once

class cSkyDome
{
private:
	LPDIRECT3DTEXTURE9		m_pSkyTex;
	LPD3DXMESH				m_pMesh;
	LPD3DXEFFECT			m_pShader;

	std::string				m_szTex;		// 텍스쳐 이름
	float					m_fRadius;		// 정점 간격
	int						m_nNumVertices;	// 버텍스 수
	int						m_nDtheta;		// 경도 0 - 360
	int						m_nDphi;		// 위도 반구 0 -90, 구 -90 - 90

public:
	HRESULT InitSkyDome(std::string strTexName, int dtheta = 15, int dphi = 15, int radius = 1.0f);
	void Render();

	cSkyDome();
	~cSkyDome();
private:
	HRESULT CreateMyMesh();
	HRESULT SetupVertex();
	float RadToDeg(int radian) { return radian * 57.29577951f; }
	float DegToRad(int degress) { return degress * 0.017453293f;}
};
