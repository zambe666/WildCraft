#pragma once
class cGrid;
class cCameraEx;
class cTerrainObject;
class cSkyDome;

class cFrameworkTest : public iSceneNode
{
private:
	cGrid* m_pGrid;
	cCameraEx* m_pCamera;
	cTerrainObject* m_pTerrain;
	cSkyDome*	m_pSky;
public:
	const HRESULT Init(DWORD dwFlag) override;
	void Update() override;
	void Render() override;
	void Release() override;	// 전환되면 없애줘야 할것
	void WndProc(HWND, UINT, WPARAM, LPARAM) override;

	cFrameworkTest();
	virtual ~cFrameworkTest();
};

