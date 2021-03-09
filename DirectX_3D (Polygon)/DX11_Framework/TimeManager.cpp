#include "TimeManager.h"

TimeManager::TimeManager()
{

}

TimeManager::~TimeManager()
{

}

float TimeManager::TotalTime() const
{
	// Ÿ�̸Ӱ� ���� �����̸�, ������ �������� �帥 �ð��� ������� ���ƾ� �Ѵ�. 
	// ����, ������ �̹� �Ͻ� ������ ���� �ִٸ� �ð��� mStopTime - mBaseTime���� 
	// �Ͻ� ���� ���� �ð��� ���ԵǾ� �ִµ�, �� ���� �ð��� ��ü �ð��� �������� 
	// ���ƾ� �Ѵ�. �̸� �ٷ���� ����, mStopTime���� �Ͻ� ���� ���� �ð��� ����.
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mStopTime    mCurrTime
	if (m_Stopped)
		return (float)(((m_StopTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);


	// �ð��� mCurrTime - mBaseTime���� �Ͻ� ���� ���� �ð��� ���ԵǾ� �ִ�. �̸� 
	// ��ü �ð��� �����ϸ� �� �ǹǷ�, �� �ð��� mCurrTime���� ����. 
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

	//���� ���¿��� Ÿ�̸Ӹ� �����Ҷ�
	if (m_Stopped)
	{
		//�Ͻ� ������ �ð��� �����Ѵ�
		m_PausedTime += (startTime - m_StopTime);

		//Ÿ�̸Ӹ� �ٽ� ���� -> ������ prevTime�� ��ȿx -> ����ð����� �ʱ�ȭ
		m_PrevTime = startTime;

		//������ ����� ����
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

		//���� ���� �ð��� ����ð��̰�, �ð� ���� bool�� ����
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
	//�̹� �������� �ð�
	ULONGLONG currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_CurrTime = currTime;

	//�̹� �����Ӱ� ���� ������ �ð��� ����
	m_DeltaTime = (m_CurrTime - m_PrevTime)*m_SecondsPerCount;

	//���� �������� �غ��Ѵ�
	m_PrevTime = m_CurrTime;

	/*
	������ �����ʰ� �Ѵ�
	���μ����� �������� ���ų� ������ �ٸ� ���μ����� ��Ű�� ��� , deltaTime�� ������ �� ���ִ�
	*/
	if (m_DeltaTime < 0.0) { m_DeltaTime = 0.0; }
}
