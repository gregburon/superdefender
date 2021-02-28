

#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include <stdio.h>
#include <string.h>
#include <string>


#include "GameRegion.h"

GameRegion::GameRegion()
{
	m_Width				= 0;
	m_Height			= 0;
	m_ImageIndex		= 0;
}

GameRegion::~GameRegion()
{


}

void GameRegion::SetRegionDimensions(int width, int height)
{
	this->m_Height = height;
	this->m_Width  = width;
}

void GameRegion::SetImageIndex(int index)
{
	this->m_ImageIndex = index;
}

int GameRegion::GetRegionWidth()
{
	return this->m_Width;
}

int GameRegion::GetRegionHeight()
{
	return this->m_Height;
}

int GameRegion::GetImageIndex()
{
	return this->m_ImageIndex;
}
