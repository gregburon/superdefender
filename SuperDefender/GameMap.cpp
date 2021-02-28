

#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>

#include "GameMap.h"

GameMap::GameMap()
{
	m_WorldWidth	= 0;
	m_WorldHeight	= 0;
	m_WrapX			= false; 
	m_WrapY			= false;
}

GameMap::~GameMap()
{
	ClearGameMap();
}

void GameMap::ClearGameMap()
{
	m_WorldWidth	= 0;
	m_WorldHeight	= 0;

	m_ViewPort.ClearViewPort();

	m_SpriteManager.ClearManager();

	m_Regions.clear();
}

bool GameMap::SetRegions(int rows, int columns)
{
	this->m_Regions.resize(rows);
	
	for(int i=0; i<rows; ++i)
	{
		this->m_Regions[i].resize(columns);
	}// end for

	return true;
}

bool GameMap::SetRegionDimensions(int width, int height)
{
	if(this->m_Regions.size() < 1)
	{
		return false;
	}

	for(int i=0; i<m_Regions.size(); ++i)
	{
		for(int j=0; j<m_Regions[i].size(); ++j)
		{
			m_Regions[i][j].SetRegionDimensions(width, height);
		}// end for
	}// end for

	// Recalculate the world's width and height
	m_WorldWidth  = m_Regions[0].size() * width;
	m_WorldHeight = m_Regions.size() * height;

	return true;
}

void GameMap::SetViewPort(int x, int y)
{
	if(x > this->m_WorldWidth || x < 0)
	{
		x = 0;
	}// end if

	if(y > this->m_WorldHeight || y < 0)
	{
		y = 0;
	}// end if

	m_ViewPort.SetViewPortLocation(x, y);

}

bool GameMap::LoadBackgroundImage(int row, int column, string path, 
		                          const LPDIRECTDRAW7 lpDD, DDCOLORKEY key)
{
	// Validate the request.
	if(row < 0 || row > m_Regions.size())
	{
		return false;
	}// end if

	if(column < 0 || column > m_Regions[0].size())
	{
		return false;
	}// end if


	// The row and column are valid, so create the sprite and assign it into 
	// the sprite manager.  Store the value returned by the sprite manager 
	// into that region's image index variable.
	int index = m_SpriteManager.AddSprite(path, lpDD, key);

	m_Regions[row][column].SetImageIndex(index);

	return true;
}

float GameMap::GetViewPortX()
{
	return m_ViewPort.GetViewPortX();
}

float GameMap::GetViewPortY()
{
	return m_ViewPort.GetViewPortY();
}

int GameMap::GetRegionRows()
{
	return this->m_Regions.size();
}

int GameMap::GetRegionCols()
{
	return this->m_Regions[0].size();
}

int GameMap::GetRegionWidth()
{
	return this->m_Regions[0][0].GetRegionWidth();
}

int GameMap::GetRegionHeight()
{
	return this->m_Regions[0][0].GetRegionHeight();
}

int GameMap::GetRegionImageIndex(int row, int col)
{
	return this->m_Regions[row][col].GetImageIndex();
}

void GameMap::UpdateViewPort(float incrementX, float incrementY)
{
	m_ViewPort.UpdateViewPort(incrementX, incrementY);
}

int GameMap::GetMapWidth()
{
	return m_WorldWidth;
}

int GameMap::GetMapHeight()
{
	return m_WorldHeight;
}

float GameMap::Round(float v)
{
   float scaleFactor = pow(10, 0);
   return floor(v*scaleFactor+0.5)/scaleFactor;
}


HRESULT GameMap::RenderGameMap(LPDIRECTDRAWSURFACE7 backBuffer)
{	
	// First, determine where the view port is in relation
	// to the game map.  Iterate over the regions that the
	// view port is over and blit those background images 
	// to the back buffer of the direct draw object.
	float viewX      = GetViewPortX();
	float viewY      = GetViewPortY();

	int mapRows      = m_Regions.size();
	int mapCols      = m_Regions[0].size();

	int regionWidth  = GetRegionWidth();
	int regionHeight = GetRegionHeight();

	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int screenWidth  = GetSystemMetrics(SM_CXSCREEN);

	int startRow = viewY / regionHeight;
	int startCol = viewX / regionWidth;
	int maxRow   = ((viewY + screenHeight) / regionHeight) + 1;
	int maxCol   = ((viewX + screenWidth) / regionWidth) + 1;;


	// Validate the max row and column values.
	if(startCol < 0) startCol = 0;
	if(startRow < 0) startRow = 0;

	if(maxCol > mapCols) maxCol = mapCols;
	if(maxRow > mapRows) maxRow = mapRows;

	int screenX = Round(-1.0 * viewX);
	int screenY = Round(-1.0 * viewY);
	

	for(int i=startRow; i<maxRow; ++i)
	{
		for(int j=startCol; j<maxCol; ++j)
		{
			// For each region that the viewport touches, we must
			// at least in part render that region's background
			// image sprite.  Get the image map index of the 
			// sprite at [row][column] that we are currently on 
			// and use that image index to create a clipping rect
			// for that image.
			int index = GetRegionImageIndex(i, j);

			if(index < 0) continue;

			screenX = Round(-1.0*viewX) + j*m_SpriteManager.m_Sprites[index].m_SourceRect.right;
			screenY = Round(-1.0*viewY) + i*m_SpriteManager.m_Sprites[index].m_SourceRect.bottom;

			m_SpriteManager.m_Sprites[index].RenderSprite(screenX, screenY, backBuffer);

		}// end for(j)	

	}// end for(i)


	return DD_OK;
}




