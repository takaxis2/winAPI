#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <dxgi.h>
#include <wrl.h>


#include <Windows.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;
using namespace DirectX;


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "dxgi.lib")


#include "Macro.h"
#include "Struct.h"


extern HWND g_hWnd;


#define SCREENHEIGHT 720
#define SCREENWIDTH 1280