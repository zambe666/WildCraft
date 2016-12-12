#pragma once
class cUIButton;
class cUIImageView;

class cTitleScene : public iSceneNode
{
private:
	LPD3DXSPRITE	m_pSprite;
	cUIButton* m_pButton[2];
	cUIImageView* m_pTitleImage;
public:
	const HRESULT Init(DWORD dwFlag) override;
	void Update() override;
	void Render() override;
	void Release() override;	// 전환되면 없애줘야 할것
	void WndProc(HWND, UINT, WPARAM, LPARAM) override;

	cTitleScene();
	virtual ~cTitleScene();
};

