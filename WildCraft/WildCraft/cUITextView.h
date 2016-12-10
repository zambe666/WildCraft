#pragma once
#include "cUIObject.h"

class cUITextView : public cUIObject
{
protected:
	SYNTHESIZE(std::string, m_sText, Text);
	SYNTHESIZE_ADD_REF(LPD3DXFONT, m_pFont, Font);
	SYNTHESIZE(DWORD, m_dwDrawTextFormat, DrawTextFormat);
	SYNTHESIZE(D3DCOLOR, m_dwColor, TextColor);
public:
	cUITextView(void);
	virtual ~cUITextView(void);

	// cUIObject override
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

