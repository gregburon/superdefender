



#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include "SpriteManager.h"
#include "Sprite.h"


SpriteManager::SpriteManager()
{

}


SpriteManager::~SpriteManager()
{
	for(int i=0; i<m_Sprites.size(); ++i)
	{
		m_Sprites[i].ReleaseSurface();
	}// end for
}

int SpriteManager::AddSprite(string path, const LPDIRECTDRAW7 lpDD, DDCOLORKEY key)
{
	// First, determine if we have already loaded this
	// sprite.  If we have, simply return the index 
	// of the already loaded sprite.  If not, then 
	// create the new sprite.
	for(int i=0; i<m_Sprites.size(); ++i)
	{
		if(m_Sprites[i].m_Path == path)
		{
			return i;
		}// end if

	}// end for


	Sprite NewSprite;

	if(NewSprite.LoadSurface(path, lpDD, key) == false)
	{
		MessageBox(NULL, "Could not load surface", 
			             path.c_str(), 
				         MB_ICONEXCLAMATION|MB_OK);

		return -1;
	}// end if

	m_Sprites.push_back(NewSprite);

	return m_Sprites.size() - 1;
}


void SpriteManager::ClearManager()
{
	for(int i=0; i<m_Sprites.size(); ++i)
	{
		m_Sprites[i].ReleaseSurface();
	}// end for

	m_Sprites.clear();
}

