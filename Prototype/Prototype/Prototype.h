#pragma once
#include "Headers.h"

class Prototype
{
public:
	virtual int InitProtoInstance()PURE;
	virtual void Release()PURE;
public:
	Prototype();
	virtual ~Prototype();
};

