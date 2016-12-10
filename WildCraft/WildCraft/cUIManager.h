#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// UI�� �ս��� ȣ���ϱ� ���� Ŭ����
// ������ �ҽ� �⺻���� �صξ����� �ʿ��ϸ� �����ϰ� ���� �޾��� ��
// 
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class cUIObject;

enum Element
{
	MAIN,
	EX,
	BUTTON
};

class cUIManager
{
private:
	SINGLETONE(cUIManager);
public:
	enum class eUIType
	{
		UT_State
	};
private:
	std::map<eUIType, cUIObject*> m_mapUIObject;

	LPD3DXSPRITE				m_pSprite;
	LPD3DXSPRITE				m_pSprite2;

	LPDIRECT3DTEXTURE9			m_pTexture;
	D3DXIMAGE_INFO				m_stImageInfo;

	LPDIRECT3DTEXTURE9			m_pTexture2;
	D3DXIMAGE_INFO				m_stImageInfo2;

	bool		m_isLButtonDown;	//���콺Ŭ�� ����
	POINT		m_ptPrevMouse;		//���콺Ŭ���� ��ǥ����
	bool		isClicked;
	
	RECT UI;
	cUIManager* m_Parent;
	Element e_type;
	SYNTHESIZE(bool, isActive, Actived);
	SYNTHESIZE(float, m_MoveX, MoveX);
	SYNTHESIZE(int, m_MoveY, MoveY);
	SYNTHESIZE(bool, isMove, DragAble);
	SYNTHESIZE(bool, isAble, ClickAble);
	SYNTHESIZE(int, isSelected, Selected);
	float pos_x, pos_y;
	std::vector<cUIManager*> v_mChild;
public:
	//�θ���, �Ӽ�, �Ϲ�ui, ���콺 ������ ui, ��ġ
	void Init(cUIManager* root, Element element, const char* name, const char* name2, POINT pos);
	void Update();
	void render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void setChild(cUIManager *_child);
	cUIObject* GetUI(eUIType e);

	void Destroy();
};
#define UI_MANAGER cUIManager::GetInstance()