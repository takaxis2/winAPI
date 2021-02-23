#pragma once
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#define PURE =0


template <typename T>
void Safe_Delete(T* _Obj)
{
	if (_Obj)
	{
		delete _Obj;
		_Obj = NULL;
	}
}