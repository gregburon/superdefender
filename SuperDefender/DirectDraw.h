
#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include <ddraw.h>
#include <stdio.h>
#include <string.h>
#include <string>


#ifndef DIRECTDRAW_H
#define DIRECTDRAW_H


class DirectDraw
{
public:

	// Constructors and destructors.
	DirectDraw();
	~DirectDraw();


	// Public interface member functions.
	bool InitializeDirectDrawInterface(int width, int height, int depth, HWND hWnd);

	bool Cleanup();



	HRESULT              Flip();

	HRESULT				 Flip(float framesPerSecond);

	HRESULT				 Flip(float framesPerSecond, float speedFactor);

	HRESULT              TestCooperativeLevel();

	LPDIRECTDRAW7        GetDirectDrawObject();

	DDCOLORKEY           GetTransparentColorKey();

	LPDIRECTDRAWSURFACE7 GetBackBuffer();

private:

	// Private member functions.
	void CreateClippingRect(int& x, int& y, RECT& clip, const RECT& source);


	// Member variables for the DirectDraw interface.
	HWND				 m_hWndGame;
	HINSTANCE			 m_hInstanceGame;

	LPDIRECTDRAW7        m_lpDD;
	LPDIRECTDRAWSURFACE7 m_lpDDSPrimary;
	LPDIRECTDRAWSURFACE7 m_lpDDSBack;
	
	DWORD				 m_KeyColor;
	DDCOLORKEY			 m_key;

	int                  m_ScreenWidth;
	int                  m_ScreenHeight;
	int                  m_ColorDepth;
};

#endif