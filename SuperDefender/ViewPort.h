
#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include "stdafx.h"
#include <stdio.h>
#include <string>



#ifndef VIEWPORT_H
#define VIEWPORT_H


class ViewPort
{
public:

	// Constructors and destructors.
	ViewPort();
	~ViewPort();


	// Public interface member functions.
	void  SetViewPortLocation(float worldX, float worldY);
	
	float GetViewPortX();

	float GetViewPortY();

	void  UpdateViewPort(float incrementX, float incrementY);

	void  ClearViewPort();


private:

	// Member variables.
	float m_WorldX;
	float m_WorldY;

};

#endif