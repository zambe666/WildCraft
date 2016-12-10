#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Object ���ҽ� ���� Ŭ���� ��� ��������
// Main �Լ����� OBJECT_MANAGER->Destroy �ʿ�
// AutoRelese�� �ٸ� ��ƾ���� ���簡 �ʿ� �Ҷ� ��, ������ Drain �ʿ�
//
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class cObject
{
private:
	DWORD m_nRefCount;
public:
	cObject();
	virtual ~cObject();

	void AddRef();
	void Release();
	void AutoRelease();
};

class cObjectManager
{
private:
	SINGLETONE(cObjectManager);
private:
	std::set<cObject*> m_setObject;
public:
	void AddObject(cObject* pObject);
	void RemoveObject(cObject* pObject);
	void Destroy();
};
#define OBJECT_MANAGER cObjectManager::GetInstance()


class cAutoReleasePool
{
private:
	SINGLETONE(cAutoReleasePool);
private:
	std::set<cObject*> m_setObjectPool;
public:
	void AddObject(cObject* pObject);
	void Drain();
};
#define AUTO_RELEASE_POOL cAutoReleasePool::GetInstance()