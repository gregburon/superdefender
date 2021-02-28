


#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include <ddraw.h>
#include <stdio.h>
#include <string.h>
#include <string>


#ifndef SPRITE_H
#define SPRITE_H


class Sprite
{
public:

	// Constructors and destructors.
	Sprite();
	Sprite(string file_name, const LPDIRECTDRAW7 lpDD, DDCOLORKEY key);
	~Sprite();


	// Member functions.
	void    ReleaseSurface();

	bool    LoadSurface(string file_name, const LPDIRECTDRAW7 lpDD, DDCOLORKEY key);

	HRESULT RenderSprite(int x, int y, LPDIRECTDRAWSURFACE7 backBuffer);

	void    RenderDebugSprite(int x, int y, LPDIRECTDRAWSURFACE7 backBuffer);

	void    CreateClippingRect(int& x, int& y, RECT& clipRect, const RECT& sourceRect);

	bool    IsValid();



	// Member variables.
	LPDIRECTDRAWSURFACE7  m_Surface;
	RECT                  m_SourceRect;
	string                m_Path;

};

#endif
