#pragma once


typedef struct tagVector3
{
	float fX, fY, fZ;

	tagVector3() {};

	tagVector3(float _fX, float _fY) 
		: fX(_fX), fY(_fY), fZ(0) {};

	tagVector3(float _fX, float _fY, float _fZ)
		: fX(_fX), fY(_fY), fZ(_fZ) {};

}Vector3;


typedef struct tagTransform
{
	Vector3 Position;
	Vector3 Rotation;
	Vector3 Scale;

}Transform;
