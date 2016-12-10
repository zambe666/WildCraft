#pragma once

struct ST_SIZE
{
	float fWidth;
	float fHeight;
	ST_SIZE() : fWidth(0.0f), fHeight(0.0f) {}
	ST_SIZE(float w, float h) : fWidth(w), fHeight(h) {}
};

class cUIObject : public cObject
{
protected:
	std::vector<cUIObject*> m_vecChild;
	SYNTHESIZE(D3DXVECTOR3, m_vLocalPos, LocalPos);
	SYNTHESIZE(ST_SIZE, m_stSize, Size);
	SYNTHESIZE(cUIObject*, m_pParent, Parent);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorld, World);
	SYNTHESIZE(int, m_nTag, Tag);

public:
	cUIObject(void);
	virtual ~cUIObject(void);

	virtual void AddChild(cUIObject* pChild);
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual cUIObject* GetChildByTag(int nTag);
};

