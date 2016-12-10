#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 충돌 구조체.  
// isPick 은 Ray에서 충돌 판정할때 서로 다른 계산 할 수 있게 함
// isInsect 는  Culling 이나 효과 적용할때 해당 평면에 대해서 판정할때 씀
//
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ST_BOUNDOBJECT {
	D3DXVECTOR3 vCenter;
	bool		isPicked;
	ST_BOUNDOBJECT()
		: vCenter{ 0,0,0 }, isPicked(false) {}
	ST_BOUNDOBJECT(D3DXVECTOR3 _vCenter, bool _isPicked)
		: vCenter(_vCenter), isPicked(_isPicked) {}
	virtual const bool IsPick(const D3DXVECTOR3& rayPos, const D3DXVECTOR3& rayDir) { return false; };
	virtual const bool IsInsect(const D3DXPLANE& plane) const { return false; };
};


struct ST_SPHERE : public ST_BOUNDOBJECT
{
	float fRadius;
	ST_SPHERE()
		: ST_BOUNDOBJECT::ST_BOUNDOBJECT()
		, fRadius(0) {}
	ST_SPHERE(D3DXVECTOR3 _vCenter, float _fRadius, bool _isPicked)
		: ST_BOUNDOBJECT::ST_BOUNDOBJECT(_vCenter, _isPicked)
		, fRadius(_fRadius) {}

	const bool IsPick(const D3DXVECTOR3& rayPos, const D3DXVECTOR3& rayDir) override
	{
		auto vLocalRayPos = rayPos - vCenter;
		auto qv = D3DXVec3Dot(&vLocalRayPos, &rayDir);
		auto qq = D3DXVec3Dot(&vLocalRayPos, &vLocalRayPos);
		auto vv = D3DXVec3Dot(&rayDir, &rayDir);
		auto rr = fRadius*fRadius;
		return (qv*qv - vv*(qq - rr)) > 0.0f;
	}
	const bool IsInsect(const D3DXPLANE& plane) const override
	{
		if (D3DXPlaneDotCoord(&plane, &vCenter) + fRadius < 0)
		{
			return false;
		}
		return true;
	}
};