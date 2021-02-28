
#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include "stdafx.h"
#include <stdio.h>
#include <string>
#include "GameRegion.h"
#include "GameObject.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "ViewPort.h"



#ifndef GAMEMAP_H
#define GAMEMAP_H


/*****************************************************************/
/*                                                               */
/*  A GameMap object is a container for the background images    */
/*  that represent the game world playing surface.  All of the   */
/*  images in a game map that are background images are held in  */
/*  the m_Regions structure, which is a 2 dimensional array of   */
/*  structures that define the size and image map index of the   */
/*  background image for that portion of the playable map.  The  */
/*  m_Regions object also has an array of objects that can be    */
/*  interacted with (ie: bumped into, etc.) which are GameObject */
/*  class objects.  The area to be rendered is determined by the */
/*  location of the ViewPort variable, which defines the upper   */
/*  left hand corner of the viewable area, which is delimited by */
/*  the actual size of the screen.                               */
/*                                                               */
/*****************************************************************/
class GameMap
{
public:

	// Constructors and destructors.
	GameMap();
	~GameMap();


	// Public interface member functions.
	bool    SetRegions(int rows, int columns);

	bool    SetRegionDimensions(int width, int height);

	void    SetViewPort(int x, int y);

	float   GetViewPortX();
	
	float   GetViewPortY();

	int     GetRegionRows();

	int     GetRegionCols();

	int     GetRegionWidth();

	int     GetRegionHeight();

	int     GetMapWidth();

	int     GetMapHeight();

	float   Round(float v);

	void    UpdateViewPort(float incrementX, float incrementY);

	bool    LoadBackgroundImage(int row, int column, string path, 
		                        const LPDIRECTDRAW7 lpDD, DDCOLORKEY key);
	void    ClearGameMap();

	int     GetRegionImageIndex(int row, int col);

	HRESULT RenderGameMap(LPDIRECTDRAWSURFACE7 backBuffer);


	// Public member variables.
	SpriteManager                 m_SpriteManager;  // each map has a sprite manager.

private:

	// Member variables.
	int                           m_WorldWidth;		// width of the world in pixels
	int                           m_WorldHeight;	// height of the world in pixels
	bool                          m_WrapX;          // does this map wrap from left to right
	bool                          m_WrapY;          // does this map wrap from top to bottom
	ViewPort                      m_ViewPort;		// currently visible area
	vector<vector<GameRegion> >   m_Regions;		// array of game regions.
	

	
};

#endif