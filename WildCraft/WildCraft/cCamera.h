#pragma once

class cCamera
{
private:
	D3DXVECTOR3				m_vUp;
	D3DXVECTOR3				m_vLook;
	D3DXVECTOR3				m_vPos;

	////////		ī�޶� ������ ����  /////////////
	float					m_fAngleX, m_fAngleY;			// �ƿ� �ʱ�ȭ �Ҷ� �ʿ��� ����
	float					m_fDistance;
	///////         ����  ///////////////////
	D3DXVECTOR3*			m_pTarget;

	SYNTHESIZE_S(bool, m_bEnable, Enable);					// �������� �ʰ� �Ѱ��� ��
	SYNTHESIZE_S(bool, m_bTracking, Tracking);
public:
	cCamera(void);
	~cCamera(void);

	void Init(D3DXVECTOR3 vPos, D3DXVECTOR3 vLook);			// ���� ī�޶�, ���� ī�޶� ����
	void SetTarget(D3DXVECTOR3* pTarget, bool bTracking);

	void Update();								// ������Ʈ �� �ش� ī�޶� View�� Set��
	void WndProc(HWND, UINT, WPARAM, LPARAM);	// ī�޶� �޽��� ���� ��� ȣ��
};
