#include "ObjectProto.h"
#include "Object.h"

ObjectProto::ObjectProto()
{

}

ObjectProto::~ObjectProto()
{
	Release();
}

//** ���� ��ü�� Ű������ Ž���Ͽ� ��ȯ.
Object * ObjectProto::GetProtoObject(string _strKey)
{
	map<string, Object*>::iterator iter = m_mapObjectList.find(_strKey);
	
	if (iter == m_mapObjectList.end())
	{
		ERROR_MESSAGE("���� ��ü�� �����ϴ�.");
		return NULL;
	}

	return iter->second;
}

//** ��� ���� ��ü�� ����.
void ObjectProto::Release()
{
	for (map<string, Object*>::iterator iter = m_mapObjectList.begin();
		iter != m_mapObjectList.end(); ++iter)
	{
		SAFE_RELEARE((*iter).second);
	}
	m_mapObjectList.clear();
}

