#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �ð� ������
// �ʱ�ȭ �Ҷ�  bAccurate �� ��Ȯ�ϰ� ��꿩��,  �����ϸ� ������ �������� ����� ��Ȯ����
// bFPScouning �� TRUE �ϸ� GetFPS �Լ��� ���� DWORD FPS �� ���� �� ���� 
// ��Ȯ�� Ÿ�̸� ���� �۵� �ȵ�, ����
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class cTimeManager
{
private:
	SINGLETONE(cTimeManager);
private:
	void(cTimeManager::*m_Update)();	// Ÿ�� �¿� ���� ���� �Լ� �޶���
	float m_fTimeScale;

	DWORD m_dwLastTimeStamp;
	DWORD m_dwDeltaTime;

	__int64 m_AccurateLastTimeStamp;
private:
	DWORD m_dwFPSTime;
	DWORD m_dwFPS;
	SYNTHESIZE_G(DWORD, m_dwFPScurr, FPS);
	SYNTHESIZE(bool, m_bFPScounting, FpsEnabled);	// fps ���ų� ���ų�

public:
	const HRESULT Init(bool bAccurate = false);	// ��Ȯ�ϰ� �ҰŸ� true ����
	void Update();
	float GetDeltaTime();

private:
	void UpdateQuery();
	void UpdateTimeGet();
	void UpdateTick();
};
#define TIME_MANAGER cTimeManager::GetInstance()