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
		//주된 임무는 성능 타이머의 주파수를 조회해서 틱당 초 수를 설정하는 것이다.
		ULONGLONG CountsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&CountsPerSec);
		return ULONGLONG(1.0f / CountsPerSec);
	}
public:
	float TotalTime()const;
	float DeltaTime()const { return (float)m_DeltaTime; }

	void Reset(); //메세지 루프 이전에 호출해야함
	void Start();//타이머를 시작 또는 재개할 때 호출해야함
	void Stop();//타이머를 정지할때 호출
	void Tick();//매 프래임 호출
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

