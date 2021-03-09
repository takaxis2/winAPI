#pragma once
#include <Headers.h>

class TimeManager
{
public:
	DECLARE_SINGLETON(TimeManager)

private:
	ULONGLONG m_BaseTime;
	ULONGLONG m_PausedTime;
	ULONGLONG m_StopTime;
	ULONGLONG m_PrevTime;
	ULONGLONG m_CurrTime;

	double m_SecondsPerCount;
	double m_DeltaTime;
	bool m_Stopped;

private:
	ULONGLONG GetTime()
	{
		//�ֵ� �ӹ��� ���� Ÿ�̸��� ���ļ��� ��ȸ�ؼ� ƽ�� �� ���� �����ϴ� ���̴�.
		ULONGLONG CountsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&CountsPerSec);
		return ULONGLONG(1.0f / CountsPerSec);
	}
public:
	float TotalTime()const;
	float DeltaTime()const { return (float)m_DeltaTime; }

	void Reset(); //�޼��� ���� ������ ȣ���ؾ���
	void Start();//Ÿ�̸Ӹ� ���� �Ǵ� �簳�� �� ȣ���ؾ���
	void Stop();//Ÿ�̸Ӹ� �����Ҷ� ȣ��
	void Tick();//�� ������ ȣ��
public:
	ULONGLONG GetBaseTime() { return m_BaseTime; }
	ULONGLONG GetPausedTime() { return m_PausedTime; }
	ULONGLONG GetStopTime() { return m_StopTime; }
	ULONGLONG GetPrevTime() { return m_PrevTime; }
	ULONGLONG GetCurrTime() { return m_CurrTime; }

private:
	TimeManager();
	~TimeManager();
};

