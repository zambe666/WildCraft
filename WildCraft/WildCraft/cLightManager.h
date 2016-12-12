#pragma once
class cLightManager
{
private:
	SINGLETONE(cLightManager);
	enum class eLightType
	{
		LT_DIR, LT_POINT, LT_SPOT
	};
	struct ST_LIGHT
	{
		eLightType type;
		D3DXVECTOR3 pos;		// 빛의 위치, dir은 없음
		D3DXVECTOR3 dir;		// 빛의 방향, point는 없음
		float		power;		// 빛이 영향을 미치는 최대 거리
		bool isReach(D3DXVECTOR3 v)
		{
			if (type == eLightType::LT_POINT)
			{
				if (D3DXVec3Length(&(v - pos)) < power)	return true;
				return false;
			}
			return true;
		}
	};
private:
	std::map<std::string, ST_LIGHT> m_mapLight;
public:
	void AddLight(std::string szLight, eLightType e, D3DXVECTOR3* pos, D3DXVECTOR3* dir, float power = 0);

};
#define LIGHT_MANAGER cLightManager::GetInstance()

