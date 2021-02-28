

#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include <stdio.h>
#include <string.h>
#include <string>


#include "ViewPort.h"

ViewPort::ViewPort()
{
	m_WorldX    = 0.0;
	m_WorldY    = 0.0;
}

ViewPort::~ViewPort()
{


}

void ViewPort::ClearViewPort()
{
	m_WorldX    = 0.0;
	m_WorldY    = 0.0;
}

void ViewPort::SetViewPortLocation(float worldX, float worldY)
{
	m_WorldX = worldX;
	m_WorldY = worldY;
}


float ViewPort::GetViewPortX()
{
	return m_WorldX;
}

float ViewPort::GetViewPortY()
{
	return m_WorldY;
}

void ViewPort::UpdateViewPort(float incrementX, float incrementY)
{
	m_WorldX += incrementX;
	m_WorldY += incrementY;
}



