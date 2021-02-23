#include "ObjectPool.h"
#include "Player.h"
#include "ObjectManager.h"
#include "CreateProtoObject.h"
#include "Object.h"


ObjectPool::ObjectPool() : m_pPrototype(NULL)
{

}

ObjectPool::~ObjectPool()
{

}

void ObjectPool::Intialize()
{
	m_pPrototype = new CreateProtoObject;
	m_pPrototype->InitProtoInstance();
}


Object* ObjectPool::Findobject(string _strKey)
{
	map<string, list<Object*>>*  m_pDisableList = GET_SINGLE(ObjectManager)->GetDisableList();

	map<string, list<Object*>>::iterator iter = m_pDisableList->find(_strKey);

	//** ���� ��ü�� Ž����
	Object* pObject = ((ObjectProto*)m_pPrototype)->GetProtoObject(_strKey);

	//** ���� ��ü�� ���ٸ�
	if (pObject == NULL)
		return NULL;

	//** ���� ��ü�� �ִٸ� ������ü�� ���� Ŭ���� ��ȯ.
	Object* pResultObj = pObject->Clone();
	pResultObj->Initialize();
	pResultObj->SetActive(true);

	if (iter == m_pDisableList->end())
	{
		list<Object*> TempList;
		TempList.push_back(pResultObj);

		m_pDisableList->insert(make_pair(_strKey, TempList));
	}
	else
	{
		iter->second.push_back(pResultObj);
	}

	return pResultObj;
}