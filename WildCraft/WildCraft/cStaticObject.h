#pragma once
#include "cGameObject.h"

class cStaticObject : public cGameObject
{
	friend class cStaticObjectManager;
private:
	LPD3DXEFFECT				m_pShader;
	LPD3DXMESH					m_pMesh;
	std::vector<cMTLnTEX*>		m_vecMtlTex;
public:
	cStaticObject(std::string szFile);
	virtual ~cStaticObject();

	virtual void Update() override;
	virtual void Render() override;
private:
	cStaticObject();
	void Destroy();
};

