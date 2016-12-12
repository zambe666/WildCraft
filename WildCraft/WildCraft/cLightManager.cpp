#include "stdafx.h"
#include "cLightManager.h"


cLightManager::cLightManager()
{
}


cLightManager::~cLightManager()
{
}
void cLightManager::AddLight(std::string szLight, eLightType e, D3DXVECTOR3* pos, D3DXVECTOR3* dir, float power)
{
	if (m_mapLight.find(szLight) != m_mapLight.end())	return;
	
	ST_LIGHT stLight;
	stLight.type = e;
	if (pos) stLight.pos = *pos;
	if (dir) stLight.dir = *dir;
	stLight.power = power;

	m_mapLight[szLight] = stLight;
}