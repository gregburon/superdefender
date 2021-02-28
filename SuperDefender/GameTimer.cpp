

#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <string>


#include "GameTimer.h"

GameTimer::GameTimer()
{

	m_CurTime		= 0;
	m_TimeCount		= 0;
	m_PerfCnt		= 0;
	m_NextTime		= 0;
	m_LastTime		= 0;
	m_TimeElapsed	= 0.0;
	m_TimeScale		= 0.0;

	m_PerfFlag		= FALSE;
}

GameTimer::~GameTimer()
{


}

void GameTimer::InitializeGameTimer(int FrameRate)
{
	// Determine if a performance counter is available.
	if(QueryPerformanceFrequency((LARGE_INTEGER *) &m_PerfCnt)) 
	{ 
		// If so, set time_count and timer choice flag 
		m_PerfFlag=TRUE;
		m_TimeCount = m_PerfCnt/FrameRate;
		QueryPerformanceCounter((LARGE_INTEGER *) &m_NextTime); 
		m_TimeScale=1.0/m_PerfCnt;
	} // end if
	else 
	{ 
		string message;
		message.append("Your system does not support a high performance counter.\n");
		message.append("The performance of this application on this computer will\n");
		message.append("most likely be reduced.");

		MessageBox(NULL, message.c_str(), 
			       "No performance counter detected.", 
				   MB_ICONEXCLAMATION|MB_OK);

		timeBeginPeriod(1);
		m_NextTime  =  timeGetTime(); 
		m_TimeScale =  0.001;
		timeEndPeriod(1);
	}// end else if
}

bool GameTimer::IsTimeUp()
{
	// Use the appropriate method to get time 
	// and calculate elapsed time since last frame
	if(m_PerfFlag) 
	{
		QueryPerformanceCounter((LARGE_INTEGER *) &m_CurTime);
	}// end if
	else 
	{
		timeBeginPeriod(1);
		m_CurTime = timeGetTime(); 
		timeEndPeriod(1);
	}// end else

	if( m_CurTime > m_NextTime )
	{
		return true;
	}// end if

	return false;
}


void GameTimer::CalculateElapsedTime()
{
	// calculate elapsed time
	m_TimeElapsed = (m_CurTime - m_LastTime) * m_TimeScale;

	// save frame time
	m_LastTime = m_CurTime;
}

void GameTimer::SetNextFrameTime()
{
	// set time for next frame 
	m_NextTime = m_CurTime + m_TimeCount; 
}


