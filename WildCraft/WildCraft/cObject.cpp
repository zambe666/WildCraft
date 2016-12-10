#include "stdafx.h"
#include "cObject.h"


cObject::cObject() : m_nRefCount(1)
{
	OBJECT_MANAGER->AddObject(this);
}

cObject::~cObject()
{
	assert(m_nRefCount == 0 && "�߸��� ������ �߻��߽��ϴ�.");
	OBJECT_MANAGER->RemoveObject(this);
}

void cObject::AddRef()
{
	assert(m_nRefCount != INT_MAX && "RefCount�� ��� ������ ������ �Ѿ�ϴ�.");
	++m_nRefCount;
}
void cObject::Release()
{
	assert(m_nRefCount > 0 && "�̹� ������ �޸��Դϴ�.");

	--m_nRefCount;
	if (m_nRefCount == 0)
	{
		delete this;
	}
}
void cObject::AutoRelease()
{
	AUTO_RELEASE_POOL->AddObject(this);
}


cObjectManager::cObjectManager() {}

cObjectManager::~cObjectManager() {}

void cObjectManager::AddObject(cObject* pObject)
{
	m_setObject.insert(pObject);
}
void cObjectManager::RemoveObject(cObject* pObject)
{
	m_setObject.erase(pObject);
}
void cObjectManager::Destroy()
{
	assert(m_setObject.empty() && "������ cObject�� ��ӹ��� ��ü �� �������� ���� ��ü�� �ֽ��ϴ�.");
}


cAutoReleasePool::cAutoReleasePool() {}

cAutoReleasePool::~cAutoReleasePool() {}

void cAutoReleasePool::AddObject(cObject* pObject)
{
	m_setObjectPool.insert(pObject);
}
void cAutoReleasePool::Drain()
{
	for each(auto p in m_setObjectPool)
	{
		SAFE_RELEASE(p);
	}
	m_setObjectPool.clear();
}