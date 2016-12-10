#pragma once

class cStaticObject;

class cStaticObjectManager
{
private:
	SINGLETONE(cStaticObjectManager);
private:
	std::map<std::string, cStaticObject*> m_mapStaticObject;
public:
	cStaticObject* GetStaticObject(std::string szFileName);
	void Destroy();
private:
	std::map<std::string, cMTLnTEX*>	m_mapMtlTex;
	std::vector<cMTLnTEX*>				m_vecMtlTex;
	void LoadFile(std::string szFileName);
	void LoadMtlLib(std::string szMtlPath);

	bool isMatch(LPSTR str1, LPSTR str2);
};
#define STATIC_OBJECT_MANAGER cStaticObjectManager::GetInstance()
