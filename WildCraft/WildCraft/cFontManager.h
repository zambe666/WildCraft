#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Font 관리 클래스
// 외부에서 세팅 안되니 필요한 폰트는 Type 추가하고 내부에서 세팅해줄 것
// 
// NORMAL : 일반 글씨
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum class eFontType
{
	FT_NORMAL
};

class cFontManager
{
private:
	SINGLETONE(cFontManager);
private:
	std::map<eFontType, LPD3DXFONT> m_mapFont;
public:
	LPD3DXFONT GetFont(eFontType e);
	void Destroy();
};
