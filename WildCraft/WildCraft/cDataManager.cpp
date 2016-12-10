#include "stdafx.h"
#include "cDataManager.h"


cDataManager::cDataManager()
{
}


cDataManager::~cDataManager()
{
}

void cDataManager::SetSavePath(std::string saveFileName)
{
	m_currPath = "./Data/" + saveFileName;
}
void cDataManager::AddData(std::string szSection, std::string szKey, std::string szVal)
{
	m_saveData.push_back(ST_DATA{ szSection,szKey,szVal });
}
void cDataManager::SaveEnd()
{
	assert(!m_currPath.empty() && "파일 경로 지정하지 않음");
	for (int i = 0; i < m_saveData.size(); i++)
	{
		WritePrivateProfileStringA(m_saveData[i]._Section.c_str(), m_saveData[i]._Key.c_str(), m_saveData[i]._Value.c_str(), m_currPath.c_str());
	}
	m_saveData.clear();
	m_currPath.clear();
}

std::string cDataManager::LoadStringData(std::string loadFileName, std::string szSection, std::string szKey)
{
	char ch[1024];
	std::string szLoadPath = "./Data/" + loadFileName;
	GetPrivateProfileStringA(szSection.c_str(), szKey.c_str(), "", ch, 1024, szLoadPath.c_str());
	return std::string(ch);
}
int cDataManager::LoadIntergerData(std::string loadFileName, std::string szSection, std::string szKey)
{
	int data = 0;
	std::string szLoadPath = "./Data/" + loadFileName;
	GetPrivateProfileIntA(szSection.c_str(), szKey.c_str(), data, szLoadPath.c_str());
	return data;
}

void cDataManager::Destroy()
{
}