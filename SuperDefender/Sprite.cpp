



#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include "Sprite.h"


Sprite::Sprite()
{

}


Sprite::Sprite(string file_name, const LPDIRECTDRAW7 lpDD, DDCOLORKEY key)
{
	LoadSurface(file_name, lpDD, key);
}

Sprite::~Sprite()
{

}


void Sprite::ReleaseSurface()
{
	if(m_Surface != NULL)
	{
		m_Surface->Release(); 
		m_Surface = NULL;
	}// end if
}


bool Sprite::LoadSurface(string file_name, const LPDIRECTDRAW7 lpDD, DDCOLORKEY key)
// Portions of this function are borrowed from "SAMS Teach Yourself DirectX in 
// 24 Hours" and from Andre LaMothe's "Isometric Game Programming with DirectX 7"
// books.  There are many tutorials on how to get a *.bmp file into a surface 
// which you can examine for even more details on loading bitmaps.
{
	HDC     hdc;
	HBITMAP bit;

	// load the interface bitmap
	bit = (HBITMAP)LoadImage(NULL, file_name.c_str(), IMAGE_BITMAP, 0, 0,
							 LR_DEFAULTSIZE|LR_LOADFROMFILE);
	if(!bit) 
	{
		// failed to load bitmap, 
		// return failure to caller
		return false;
	}// end if

	// get bitmap dimensions
	BITMAP bitmap;
    GetObject(bit, sizeof(BITMAP), &bitmap);

	int surf_width   = bitmap.bmWidth;
	int surf_height  = bitmap.bmHeight;

	m_SourceRect.top    = 0;
	m_SourceRect.bottom = surf_height;
	m_SourceRect.left   = 0;
	m_SourceRect.right  = surf_width;

	// create surface
	HRESULT ddrval;
	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT ;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN; 
	ddsd.dwWidth  = surf_width;
	ddsd.dwHeight = surf_height; 

	// attempt to create surface
	ddrval = lpDD->CreateSurface(&ddsd, &m_Surface, NULL);

	// created ok?
	if(ddrval!=DD_OK) 
	{
		// no, release the bitmap and return failure to caller
		DeleteObject(bit);
		return NULL;
	} 
	else 
	{
        // yes, get a DC for the surface
		m_Surface->GetDC(&hdc);

		// generate a compatible DC
		HDC bit_dc = CreateCompatibleDC(hdc);

		// blit the interface to the surface
		SelectObject(bit_dc,bit);
		BitBlt(hdc,0,0,surf_width,surf_height,bit_dc,0,0,SRCCOPY);

		// release the DCs
		m_Surface->ReleaseDC(hdc);
		DeleteDC(bit_dc);
	}

	// clear bitmap 
	DeleteObject(bit);
	DeleteDC(hdc);

	
	m_Surface->SetColorKey(DDCKEY_SRCBLT, &key);

	// Housekeeping stuff for the Sprite class.
	m_Path = file_name;

	return true;
}

HRESULT Sprite::RenderSprite(int x, int y, LPDIRECTDRAWSURFACE7 backBuffer)
// This function renders a sprite to the back buffer.  The x and 
// y coordinates passed as parameters to this function are in 
// screen coordinates.  Values in world coordinates must first
// be converted into screen space.
{
	if(!this->IsValid())
	{
		return DDERR_SURFACELOST;
	}

	RECT clipRect;

	clipRect.top    = 0;
	clipRect.bottom = m_SourceRect.bottom;
	clipRect.left   = 0;
	clipRect.right  = m_SourceRect.right;

	CreateClippingRect(x, y, clipRect, m_SourceRect);

	return backBuffer->BltFast(x, y, m_Surface, 
		                       &clipRect, 
					           DDBLTFAST_WAIT | 
							   DDBLTFAST_SRCCOLORKEY);
	return DD_OK;
}

void Sprite::RenderDebugSprite(int x, int y, LPDIRECTDRAWSURFACE7 backBuffer)
// Thie RenderDebugSprite() function draws a rectangle to the back buffer
// in the same fashion that the standard RenderSprite() funcion does. 
// The x and y coordinate are in screen coordinates.  If the values are in 
// world coordinates they should be converted to screen space before 
// this function is called.
{
	HDC  hdc;
	RECT clipRect;

	clipRect.top    = 0;
	clipRect.bottom = m_SourceRect.bottom;
	clipRect.left   = 0;
	clipRect.right  = m_SourceRect.right;

	CreateClippingRect(x, y, clipRect, m_SourceRect);

	if(backBuffer->GetDC(&hdc) == DD_OK) 
	{ 
		HPEN    borderpen;
		HBRUSH  backgroundbrush;
		borderpen = CreatePen(PS_SOLID, 1, RGB(0,0,255));
		backgroundbrush = CreateSolidBrush(RGB(0,0,0));
		SelectObject(hdc, borderpen);
		SelectObject(hdc, backgroundbrush);

		Rectangle(hdc, x, y, x + (clipRect.right  - clipRect.left), 
				             y + (clipRect.bottom - clipRect.top));

		DeleteObject(borderpen);
		DeleteObject(backgroundbrush);
	}

	backBuffer->ReleaseDC(hdc); 

	DeleteDC(hdc);
}

void Sprite::CreateClippingRect(int& x, int& y, RECT& clipRect, const RECT& sourceRect)
// The CreateClippingRect() function updates the x and y variables and 
// modifies the clipping rectangle clipRect in order to correctly blit 
// the intended sprite image to the screen.  As the source rect may be 
// partly off of the screen space, the clipping rectangle is set up to
// be completely on the screen space and to ignore any part of the sprite
// that is outside of the screen area.
{
	int height = GetSystemMetrics(SM_CYSCREEN);
	int width  = GetSystemMetrics(SM_CXSCREEN);

	if(y < 0)
	{
		clipRect.top -= y;
		y = 0;
	}// end if

	if(y + clipRect.bottom > height)
	{
		clipRect.bottom  = height - y;
	}// end if

	if(x < 0)
	{
		clipRect.left = abs(x);
		x = 0;
	}// end if

	if(x + clipRect.right > width)
	{
		clipRect.right = sourceRect.right - abs(width - (x + sourceRect.right));
	}// end if
}

bool Sprite::IsValid()
{
	if(m_Surface == NULL)
	{
		return false;
	}// end if

	return true;
}