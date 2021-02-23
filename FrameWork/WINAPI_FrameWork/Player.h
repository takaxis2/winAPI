#pragma once
#include "Object.h"


class Bridge;
class Player : public Object
{
private:
	float m_fSpeed;
	float m_fAngle;
	ULONGLONG m_BulletTime;
public:
	virtual void Initialize(void)override;
	virtual int Update(void)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release(void)override;

public:
	template <typename T>
	void CreateNomalBullet(string _strKey);

	template <typename T>
	void CreateRotateBullet();
public:
	Player();
	virtual ~Player();
};