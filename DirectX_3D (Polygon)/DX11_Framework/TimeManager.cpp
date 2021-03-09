#include "TimeManager.h"

TimeManager::TimeManager()
{

}

TimeManager::~TimeManager()
{

}

float TimeManager::TotalTime() const
{
	// 타이머가 정지 상태이면, 정지된 시점부터 흐른 시간은 계산하지 말아야 한다. 
	// 또한, 이전에 이미 일시 정지된 적이 있다면 시간차 mStopTime - mBaseTime에는 
	// 일시 정지 누적 시간이 포함되어 있는데, 그 누적 시간을 전체 시간에 포함하지 
	// 말아야 한다. 이를 바로잡기 위해, mStopTime에서 일시 정지 누적 시간을 뺀다.
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mStopTime    mCurrTime
	if (m_Stopped)
		return (float)(((m_StopTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);


	// 시간차 mCurrTime - mBaseTime에는 일시 정지 누적 시간이 포함되어 있다. 이를 
	// 전체 시간에 포함하면 안 되므로, 그 시간을 mCurrTime에서 뺀다. 
	// // // (mCurrTime - mPausedTime) - mBaseTime 
	// 
	//						|<--paused time-->| 
	// ----*---------------*-----------------*------------*------> time 
	// mBaseTime mStopTime startTime mCurrTime


	return (float)(((m_CurrTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);
}

void TimeManager::Reset()
{
	ULONGLONG currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_BaseTime = currTime;
	m_PrevTime = currTime;
	m_StopTime = 0;
	m_Stopped = false;
}

void TimeManager::Start()
{
	ULONGLONG startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	//정지 상태에서 타이머를 시작할때
	if (m_Stopped)
	{
		//일시 정지된 시간을 누적한다
		m_PausedTime += (startTime - m_StopTime);

		//타이머를 다시 시작 -> 현재의 prevTime은 유효x -> 현재시간으로 초기화
		m_PrevTime = startTime;

		//나머지 멤버들 갱신
		m_StopTime = 0;
		m_Stopped = false;
	}
}

void TimeManager::Stop()
{
	if (!m_Stopped)
	{
		ULONGLONG currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		//정지 시점 시간은 현재시간이고, 시간 정지 bool값 설정
		m_StopTime = currTime;
		m_Stopped = true;
	}
}

void TimeManager::Tick()
{
	if (m_Stopped)
	{
		m_DeltaTime = 0.0;
		return;
	}
	//이번 프레임의 시간
	ULONGLONG currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_CurrTime = currTime;

	//이번 프레임과 이전 프레임 시간의 차이
	m_DeltaTime = (m_CurrTime - m_PrevTime)*m_SecondsPerCount;

	//다음 프레임을 준비한다
	m_PrevTime = m_CurrTime;

	/*
	음수가 되지않게 한다
	프로세서가 절전모드로 들어가거나 실행이 다른 프로세서와 엉키는 경우 , deltaTime이 음수가 될 수있다
	*/
	if (m_DeltaTime < 0.0) { m_DeltaTime = 0.0; }
}
