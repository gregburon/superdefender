

#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include "DirectDraw.h"


DirectDraw::DirectDraw()
{
	m_lpDD					= NULL;
	m_lpDDSPrimary			= NULL;
	m_lpDDSBack				= NULL;

	m_KeyColor				= 0;

	m_ScreenWidth			= 0;
	m_ScreenHeight			= 0;
	m_ColorDepth			= 0;
}


DirectDraw::~DirectDraw()
{

}

bool DirectDraw::InitializeDirectDrawInterface(int width, 
											   int height, 
											   int depth, 
											   HWND hWnd)
// The InitializedDirectDrawInterface() function creates a wrapper
// for the DirectDraw object and sets up the "handshake" between 
// the windows application and the DirectDraw components (primary 
// and secondary buffers).
{
	HRESULT        ddrval;
	LPDIRECTDRAW   pDD;

	m_ScreenWidth   = width;
	m_ScreenHeight  = height;
	m_ColorDepth    = depth;

    // Create the main DirectDraw object
    ddrval = DirectDrawCreate(NULL, &pDD, NULL);
    if(ddrval != DD_OK)
	{
		MessageBox(NULL, "Could not create direct draw object", 
			             "Initialization Error.", 
				         MB_ICONEXCLAMATION|MB_OK);
		return FALSE;
	}// end if

    // Fetch DirectDraw interface
    ddrval = pDD->QueryInterface(IID_IDirectDraw4, (LPVOID *) &m_lpDD);
    if(ddrval != DD_OK) 
	{
		MessageBox(NULL, "Could not query direct draw interface", 
			             "Initialization Error.", 
				         MB_ICONEXCLAMATION|MB_OK);
		return FALSE;
	}// end if

    // Set our cooperative level
    ddrval = m_lpDD->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN);
    if(ddrval != DD_OK) 
	{
		MessageBox(NULL, "Could not set direct draw cooperative level", 
			             "Initialization Error.", 
				         MB_ICONEXCLAMATION|MB_OK);
		return FALSE;
	}// end if

	// Set the display mode
	ddrval = m_lpDD->SetDisplayMode(m_ScreenWidth, m_ScreenHeight, m_ColorDepth, 0, 0);
	if(ddrval !=DD_OK) 
	{
		MessageBox(NULL, "Could not set display mode", 
			             "Initialization Error.", 
				         MB_ICONEXCLAMATION|MB_OK);
		return FALSE;
	}// end if

    // Create the primary surface with 1 back buffer
    DDSURFACEDESC2 ddsd;

	// Surface capabilities.
	DDSCAPS2 ddscaps;

	ZeroMemory(&ddsd,sizeof(ddsd));
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
                          DDSCAPS_FLIP | 
                          DDSCAPS_COMPLEX;
    ddsd.dwBackBufferCount = 1;
    ddrval = m_lpDD->CreateSurface( &ddsd, &m_lpDDSPrimary, NULL );
	if(ddrval!=DD_OK) 
	{
		MessageBox(NULL, "Could not create primary surface", 
			             "Initialization Error.", 
				         MB_ICONEXCLAMATION|MB_OK);
		return FALSE;
	}// end if

	// Fetch back buffer interface
	ddscaps.dwCaps=DDSCAPS_BACKBUFFER;
	ddrval = m_lpDDSPrimary->GetAttachedSurface(&ddscaps,&m_lpDDSBack);
	if(ddrval!=DD_OK) 
	{
		MessageBox(NULL, "Could not get back buffer surface", 
			             "Initialization Error.", 
				         MB_ICONEXCLAMATION|MB_OK);
		return FALSE;
	}

	// get the pixel format
	DDPIXELFORMAT ddpf;
	ddpf.dwSize=sizeof(ddpf);
	m_lpDDSPrimary->GetPixelFormat(&ddpf);

	// Determine proper key for pixel format
	m_KeyColor = ddpf.dwRBitMask;

	// set color keys
	m_key.dwColorSpaceLowValue  = m_KeyColor;
	m_key.dwColorSpaceHighValue = m_KeyColor;

	// Determine proper key for pixel format
	m_KeyColor = ddpf.dwRBitMask;

	return true;
}

HRESULT DirectDraw::TestCooperativeLevel()
{
	return m_lpDD->TestCooperativeLevel();
}

LPDIRECTDRAW7 DirectDraw::GetDirectDrawObject()
{
	return this->m_lpDD;
}

DDCOLORKEY DirectDraw::GetTransparentColorKey()
{
	return this->m_key;
}

LPDIRECTDRAWSURFACE7 DirectDraw::GetBackBuffer()
{
	return this->m_lpDDSBack;
}

bool DirectDraw::Cleanup()
// The Cleanup() function releases all of the 
// interface variables and sets them to NULL.
{
	m_lpDDSBack->Release();
	m_lpDDSPrimary->Release();
	m_lpDD->Release();
	
	m_lpDD					= NULL;
	m_lpDDSPrimary			= NULL;
	m_lpDDSBack				= NULL;

	return true;
}

HRESULT DirectDraw::Flip()
// This function flips the back buffer to the primary buffer.
{
	return m_lpDDSPrimary->Flip(0, DDFLIP_WAIT  /* | DDFLIP_NOVSYNC  */ ); 
}

HRESULT DirectDraw::Flip(float framesPerSecond)
// This function flips the back buffer to the primary buffer.
{
	HDC hdc;

	if(m_lpDDSBack->GetDC(&hdc) == DD_OK) 
	{ 
		SetBkColor(hdc, TRANSPARENT ); 
		SetTextColor(hdc, RGB(255, 0, 0)); 

		// Setup the strings
		char frame_rate_string[256];

		// setup the strings
		sprintf(frame_rate_string, "frames per second: %5.2f fps", framesPerSecond);

		// Display the strings
		TextOut(hdc, 5, 25, frame_rate_string, strlen(frame_rate_string));

		m_lpDDSBack->ReleaseDC(hdc); 
	}// end if 

	// Clean the hdc memory.
	DeleteDC(hdc);

	return m_lpDDSPrimary->Flip(0, DDFLIP_WAIT  /* | DDFLIP_NOVSYNC  */); 
}

HRESULT	DirectDraw::Flip(float framesPerSecond, float speedFactor)
{
	HDC hdc;

	if(m_lpDDSBack->GetDC(&hdc) == DD_OK) 
	{ 
		SetBkColor(hdc, TRANSPARENT ); 
		SetTextColor(hdc, RGB(255, 0, 0)); 

		// Setup the strings
		char frame_rate_string[256];
		char speed_factor_string[256];

		// setup the strings
		sprintf(frame_rate_string, "FPS: %5.2f fps", framesPerSecond);
		sprintf(speed_factor_string, "speed factor: %5.2f sf", speedFactor);

		// Display the strings
		TextOut(hdc, 5, 25, frame_rate_string, strlen(frame_rate_string));
		TextOut(hdc, 5, 45, speed_factor_string, strlen(speed_factor_string));

		m_lpDDSBack->ReleaseDC(hdc); 
	}// end if 

	// Clean the hdc memory.
	DeleteDC(hdc);

	return m_lpDDSPrimary->Flip(0, DDFLIP_WAIT /* | DDFLIP_NOVSYNC  */ ); 
}



