#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ������ �޴���
// SetSavePath�� ��� �����ϰ�   Add����,  SaveEnd�ϸ� Path�� �����
// Path�� �⺻ "./Data/ �� �����
// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class cDataManager
{
private:
	SINGLETONE(cDataManager);
private:
	std::string				m_currPath;	// �Ҵ�� ���� �ּ�
	
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
