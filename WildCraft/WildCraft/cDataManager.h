#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 데이터 메니저
// SetSavePath로 경로 설정하고   Add한후,  SaveEnd하면 Path에 저장됨
// Path는 기본 "./Data/ 에 저장됨
// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class cDataManager
{
private:
	SINGLETONE(cDataManager);
private:
	std::string				m_currPath;	// 할당된 저장 주소
	
	struct ST_DATA
	{
		std::string _Section;
		std::string _Key;
		std::string _Value;
	};
	std::vector<ST_DATA>	m_saveData;
public:
	void SetSavePath(std::string savePath);
	void AddData(std::string szSection, std::string szKey, std::string szVal);
	void SaveEnd();

	std::string LoadStringData(std::string loadFileName, std::string szSection, std::string szKey);
	int LoadIntergerData(std::string loadFileName, std::string szSection, std::string szKey);

	void Destroy();
};
#define DATA_MANAGER cDataManager::GetInstance()
