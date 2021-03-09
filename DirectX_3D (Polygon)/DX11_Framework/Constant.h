#pragma once

/***********
 * GLOBALS *
 ***********/
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;



namespace INPUTID
{
	const ULONG UP		= 0x00000001;
	const ULONG DOWN	= 0x00000002;
	const ULONG LEFT	= 0x00000004;
	const ULONG RIGHT	= 0x00000008;
	const ULONG SPACE	= 0x00000010;
	const ULONG ESCAPE	= 0x00000020;
	const ULONG RETURN	= 0x00000040;

	const ULONG MOUSE_LBOTTON = 0x00000080;
	const ULONG MOUSE_RBOTTON = 0x00000100;
}










/*
namespace Colors 
{
	XMGLOBALCONST XMFLOAT4 White		= { 1.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMFLOAT4 Black		= { 0.0f, 0.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMFLOAT4 Red			= { 1.0f, 0.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMFLOAT4 Green		= { 0.0f, 1.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMFLOAT4 Blue			= { 0.0f, 0.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMFLOAT4 Yellow		= { 1.0f, 1.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMFLOAT4 Cyan			= { 0.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMFLOAT4 Magenta		= { 1.0f, 0.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMFLOAT4 Silver		= { 0.75f, 0.75f, 0.75f, 1.0f };
	XMGLOBALCONST XMFLOAT4 LightSteelBlue = { 0.69f, 0.77f, 0.87f, 1.0f };
}
*/