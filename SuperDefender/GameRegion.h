
#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include "stdafx.h"
#include <stdio.h>
#include <vector>
#include "GameObject.h"



#ifndef GAMEREGION_H
#define GAMEREGION_H


class GameRegion
{
public:

	// Constructors and destructors.
	GameRegion();
	~GameRegion();

	void  SetRegionDimensions(int width, int height);

	void  SetImageIndex(int index);

	int   GetImageIndex();

	int   GetRegionWidth();

	int   GetRegionHeight();

private:
	
	// Member variables
	int  m_Width;		// each region has a width in pixels
	int  m_Height;		// each region has a height in pixels

	int  m_ImageIndex;  // each region has an background image 
						// map index in the map's sprite manager.

	bool m_Passable;    // is this region a portion of the map that
						// can be traveled on


	vector<GameObject>  m_GameObjects;	// each GameRegion has an 
										// array of GameObjects in it.

};

#endif