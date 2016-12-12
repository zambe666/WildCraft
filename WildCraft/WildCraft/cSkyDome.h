#pragma once

class cSkyDome
{
private:
	LPDIRECT3DTEXTURE9		m_pSkyTex;
	LPD3DXMESH				m_pMesh;
	LPD3DXEFFECT			m_pShader;

	std::string				m_szTex;		// �ؽ��� �̸�
	float					m_fRadius;		// ���� ����
	int						m_nNumVertices;	// ���ؽ� ��
	int						m_nDtheta;		// �浵 0 - 360
	int						m_nDphi;		// ���� �ݱ� 0 -90, �� -90 - 90

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
