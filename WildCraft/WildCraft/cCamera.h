#pragma once

class cCamera
{
private:
	D3DXVECTOR3				m_vUp;
	D3DXVECTOR3				m_vLook;
	D3DXVECTOR3				m_vPos;

	////////		카메라 움직임 제어  /////////////
	float					m_fAngleX, m_fAngleY;			// 아예 초기화 할때 필요한 변수
	float					m_fDistance;
	///////         추적  ///////////////////
	D3DXVECTOR3*			m_pTarget;

	SYNTHESIZE_S(bool, m_bEnable, Enable);					// 갱신하지 않고 한곳만 봄
	SYNTHESIZE_S(bool, m_bTracking, Tracking);
public:
	cCamera(void);
	~cCamera(void);

	void Init(D3DXVECTOR3 vPos, D3DXVECTOR3 vLook);			// 자유 카메라, 추적 카메라 설정
	void SetTarget(D3DXVECTOR3* pTarget, bool bTracking);

	void Update();								// 업데이트 시 해당 카메라 View로 Set됨
	void WndProc(HWND, UINT, WPARAM, LPARAM);	// 카메라가 메시지 받을 경우 호출
};
