#pragma once

class cGrid;
class cCamera;
class cSurfaceObject;

class cFrameworkTest : public iSceneNode
{
private:
	cGrid*			m_pGrid;
	cCamera*		m_pMainCamera;
	cSurfaceObject* m_pSurface;
public:
	const HRESULT Init(DWORD dwFlag) override;
	void Update() override;
	void Render() override;
	void Release() override;	// 전환되면 없애줘야 할것
	void WndProc(HWND, UINT, WPARAM, LPARAM) override;

	cFrameworkTest();
	virtual ~cFrameworkTest();
};

