#pragma once
#include "Prototype.h"

class Object;
class ObjectProto : public Prototype
{
protected:
	//** ���� ��ü�� ����
	map<string, Object*> m_mapObjectList;
public:
	Object* GetProtoObject(string _strKey);
public:
	virtual int InitProtoInstance()PURE;
	virtual void Release()override;
public:
	ObjectProto();
	virtual ~ObjectProto();
};

