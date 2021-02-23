#pragma once
#include "Headers.h"
#include "Object.h"


class CollisionManager
{
public:
	static bool Collision(Object* _pTemp, Object* _pDest)
	{
		float fX = _pTemp->GetPosition().fX - _pDest->GetPosition().fX;
		float fY = _pTemp->GetPosition().fY - _pDest->GetPosition().fY;

		float fSum = (_pTemp->GetScale().fX / 2) + (_pDest->GetScale().fX / 2);

		float fLength = sqrt((fX * fX) + (fY * fY));

		if (fLength < fSum)
			return true;

		return false;
	}

	static float GetDistance(Vector3 _pTemp, Vector3 _pDest)
	{
		float fX = _pTemp.fX - _pDest.fX;
		float fY = _pTemp.fY - _pDest.fY;

		float fLength = sqrt((fX * fX) + (fY * fY));

		fX /= fLength;
		fY /= fLength;

		return fLength;
	}
};