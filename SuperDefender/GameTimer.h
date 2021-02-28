
#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include "stdafx.h"
#include <stdio.h>



#ifndef GAMETIMER_H
#define GAMETIMER_H


class GameTimer
{
public:

	// Constructors and destructors.
	GameTimer();

	~GameTimer();


	// Member functions
	void InitializeGameTimer(int FrameRate);

	bool IsTimeUp();

	void CalculateElapsedTime();

	void SetNextFrameTime();


private:


	// Member variables.
	LONGLONG	m_CurTime;		// current time
	DWORD		m_TimeCount;	// ms per frame, default if no performance counter
	LONGLONG	m_PerfCnt;		// performance timer frequency
	BOOL		m_PerfFlag;		// flag determining which timer to use
	LONGLONG	m_NextTime;		// time to render next frame
	LONGLONG	m_LastTime;		// time of previous frame
	double		m_TimeElapsed;	// time since previous frame
	double		m_TimeScale;	// scaling factor for time
};

#endif