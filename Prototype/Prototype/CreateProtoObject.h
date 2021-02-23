#pragma once
#include "ObjectProto.h"

class CreateProtoObject : public ObjectProto
{
public:
	virtual int InitProtoInstance()override;
public:
	CreateProtoObject();
	virtual ~CreateProtoObject();
};

