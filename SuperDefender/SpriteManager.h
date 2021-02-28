


#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include <ddraw.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

#include "Sprite.h"


#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H


class SpriteManager
{
public:

	// Constructors and destructors.
	SpriteManager();
	~SpriteManager();

	// Public interface methods.
	int  AddSprite(string path, const LPDIRECTDRAW7 lpDD, DDCOLORKEY key);

	void ClearManager();


	// Member variables.
	std::vector<Sprite>   m_Sprites;

};

#endif