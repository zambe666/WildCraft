#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���̴� �޴���
// �ٸ� ��ó�� �̸� ������ �ΰ� ������
// ���� ���� �Ǵ� �� ST_XFILE
// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum class eShaderType
{
	ST_NORMAL,			// �Ϲݿ�
	ST_WATER,			// ��
	ST_XFILE,			// Xfile��
	ST_SKY
};

class cShaderManager
{
private:
	SINGLETONE(cShaderManager);
private:
	std::map<eShaderType, LPD3DXEFFECT> m_mapEffect;
public:
	LPD3DXEFFECT GetShader(eShaderType e);
	void Destroy();

private:
	LPD3DXEFFECT LoadShader(std::string sPath);
	//LPD3DXEFFECT LoadShader(std::string sPath);
	// ���ð��� �޶��� �� ����
};
#define SHADER_MANAGER cShaderManager::GetInstance()
