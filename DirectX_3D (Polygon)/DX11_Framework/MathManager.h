#pragma once
#include "Headers.h"


class MathManager
{
public:
	DECLARE_SINGLETON(MathManager)
public:
	float GetDistance(XMFLOAT3 _Dest, XMFLOAT3 _Sour)
	{
		float fX = _Dest.x - _Sour.x;
		float fY = _Dest.y - _Sour.y;
		float fZ = _Dest.z - _Sour.z;

		return sqrt((fX*fX) + (fY*fY) + (fZ*fZ));
	}
private:
	MathManager() {};
	~MathManager() {};
};