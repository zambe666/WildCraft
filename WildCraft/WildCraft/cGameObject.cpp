#include "stdafx.h"
#include "cGameObject.h"

cGameObject::cGameObject(void)
	: m_vPosition(0, 0, 0)
	, m_vDirection(0, 0, 1)
	//, m_pAction(nullptr)
{
}


cGameObject::~cGameObject(void)
{
	//SAFE_RELEASE(m_pAction);
}