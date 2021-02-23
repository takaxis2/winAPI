#include "ObjectProto.h"
#include "Object.h"

ObjectProto::ObjectProto()
{

}

ObjectProto::~ObjectProto()
{
	Release();
}

//** 원형 객체를 키값으로 탐색하여 반환.
Object * ObjectProto::GetProtoObject(string _strKey)
{
	map<string, Object*>::iterator iter = m_mapObjectList.find(_strKey);
	
	if (iter == m_mapObjectList.end())
	{
		ERROR_MESSAGE("원형 객체가 없습니다.");
		return NULL;
	}

	return iter->second;
}

//** 모든 원형 객체를 제거.
void ObjectProto::Release()
{
	for (map<string, Object*>::iterator iter = m_mapObjectList.begin();
		iter != m_mapObjectList.end(); ++iter)
	{
		SAFE_RELEARE((*iter).second);
	}
	m_mapObjectList.clear();
}

