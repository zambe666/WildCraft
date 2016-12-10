#include "stdafx.h"
#include "cStaticObject.h"
#include "cStaticObjectManager.h"

cStaticObject::cStaticObject()
	: cGameObject::cGameObject(),
	m_pShader(nullptr), m_pMesh(nullptr)
{
}


cStaticObject::~cStaticObject()
{
	
}


cStaticObject::cStaticObject(std::string szFile)
	: cGameObject::cGameObject(),
	m_pShader(nullptr), m_pMesh(nullptr)
{
	//auto origObject = STATIC_OBJECT_MANAGER->Get
}

void cStaticObject::Update()
{

}

void cStaticObject::Render()
{

}

void cStaticObject::Destroy()
{

}