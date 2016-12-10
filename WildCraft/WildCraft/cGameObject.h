#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 
// 
// 
// 
// 
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class cAction;

class cGameObject : public cObject
{
private:
	//SYNTHESIZE_ADD_REF(cAction*, m_pAction, Action);
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vDirection, Direction);
	
public:
	cGameObject();
	virtual ~cGameObject();

	virtual void Update() PURE;
	virtual void Render() PURE;
};
