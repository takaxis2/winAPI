#pragma once
#include "Object.h"

class Bridge;
class Bullet : public Object
{
private:
	Bridge* m_pBridge;
public:
	virtual void Initialize(void)override;
	virtual int Update(void)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release(void)override;
public:
	Bridge* GetBridge() { return m_pBridge; }
	void SetBridge(Bridge* _pBridge) { m_pBridge = _pBridge; }
public:
	Bullet();
	virtual ~Bullet();
};