#pragma once


#define WINSIZEX 720
#define WINSIZEY 1000

#define MonsterMax 4

#define PURE =0

#define PI 3.141592f


template <typename T>
inline void Safe_Delete(T& _pObj)
{
	if (_pObj)
	{
		delete _pObj;
		_pObj = NULL;
	}
}


#define SAFE_DELETE(_pObj) Safe_Delete(_pObj)


extern HWND g_hWnd;
