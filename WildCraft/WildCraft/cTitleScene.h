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
	void Release() override;	// ��ȯ�Ǹ� ������� �Ұ�
	void WndProc(HWND, UINT, WPARAM, LPARAM) override;

	cTitleScene();
	virtual ~cTitleScene();
};

