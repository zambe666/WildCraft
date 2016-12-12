#pragma once
class cCameraEx
{
private:
	D3DXVECTOR3 m_vView;
	D3DXVECTOR3 m_vCross;
	D3DXMATRIXA16 m_matView;

	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vEye, Eye);
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vLooat, LookAt);
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vUp, Up);
public:
	cCameraEx();
	~cCameraEx();
	D3DXMATRIXA16* SetView(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvLookat, D3DXVECTOR3* pvUp);
	void Update();
	D3DXMATRIXA16* RotateLocalX(float angle);
	D3DXMATRIXA16* RotateLocalY(float angle);
	D3DXMATRIXA16* RotateLocalZ(float angle);

	D3DXMATRIXA16* MoveTo(D3DXVECTOR3* pv);
	D3DXMATRIXA16* MoveLocalX(float dist);
	D3DXMATRIXA16* MoveLocalY(float dist);
	D3DXMATRIXA16* MoveLocalZ(float dist);
};

