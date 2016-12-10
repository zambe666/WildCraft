#pragma once

enum class eCameraType
{
	CT_RAND,
	CT_AIR
};

class cCamera
{
private:

	D3DXVECTOR3				m_vUp;			// ���� ���� ���� 
	D3DXVECTOR3				m_vRight;		
	D3DXVECTOR3				m_vLook;

	SYNTHESIZE_PASS_BY_REF_S(D3DXVECTOR3, m_vPos, Position);	// ��ġ
	SYNTHESIZE_S(eCameraType, m_eType, CameraType);			
private:
	POINT					m_ptPrevMouse;
	bool					m_isLButtonDown;

	float					m_fAngleX, m_fAngleY;		// �ƿ� �ʱ�ȭ �Ҷ� �ʿ��� ����
	float					m_fDistance;
	
	SYNTHESIZE_S(D3DXVECTOR3*, m_pTarget, TargetVector);	// ����ų ���
public:
	cCamera(void);
	~cCamera(void);

	void Init(eCameraType eType);
	void Update();								// ������Ʈ �� �ش� ī�޶� View�� Set��

	void WndProc(HWND, UINT, WPARAM, LPARAM);	// ī�޶� �޽��� ���� ��� ȣ��

private:
	void tStrafe(float fUnit);		// ���� �̵�
	void tFly(float fUnit);			// �� �̵�
	void tWalk(float fUnit);		// ȸ�� �̵�

	void rPitch(float fAngle);		// ���� ȸ��
	void rYaw(float fAngle);		// ���� ȸ��
	void rRoll(float fAngle);		// ���� ȸ��

	void AngleSet();				// ���� ������ ������
	void UpdateKey();
};
