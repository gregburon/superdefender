

/*****************************************************************************/
/*                                                                           */
/*  SuperDefender Tutorial                                                   */
/*                                                                           */
/*  Created by Greg Buron                                                    */
/*                                                                           */
/*  Ideas for and portions of this tutorial are generously provided from     */
/*  Andre LaMothe's book "Isometric Game Programming with DirectX 7" and     */
/*  Sam's "Teach Yourself DirectX7 in 24 Hours".                             */
/*                                                                           */
/*  This tutorial is intended to help you, the beginning game programmer,    */
/*  to understand some of the basics of DirectDraw, how to incorporate       */
/*  components of DirectX into a Visual Studio workspace, and how to create  */
/*  a basic rendering engine by componentizing the DirectDraw API.           */
/*                                                                           */
/*****************************************************************************/
                    
#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include "stdafx.h"
#include <stdio.h>
#include <ddraw.h>
#include <dinput.h>
#include <mmsystem.h>
#include <string.h>
#include <string>

#include "DirectDraw.h"
#include "DirectInput.h"
#include "GameTimer.h"
#include "SpaceShip.h"
#include "GameMap.h"
#include "SpriteManager.h"



/******************************************************************************/
/*                                                                            */
/*  Constants, Structures, and Class objects.                                 */
/*                                                                            */
/******************************************************************************/
HWND		    hWndGame;
HINSTANCE	    hInstanceGame;

DirectDraw      Draw;
DirectInput     Input;
GameTimer       Timer;
SpriteManager   SpritesManager;
GameMap         Map;


SpaceShip       ship;


void Cleanup()
// Release all of the memory for the surfaces 
// and to direct x interfaces classes.
{
	Draw.Cleanup();
	Input.Cleanup();
}

/******************************************************************************/
/*                                                                            */
/*   Windows Message Handling Function                                        */
/*                                                                            */
/******************************************************************************/
LRESULT CALLBACK WindowProc(HWND hWnd, unsigned uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_DESTROY:
			Cleanup();
            PostQuitMessage(0);
            break;

		case WM_MOUSEMOVE:
			break;

		case WM_LBUTTONDOWN:
			break;

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }// end switch

	return 0L;
}


void CreateGameMap()
{

	Map.SetRegions(3, 20);				// rows, columns
	Map.SetRegionDimensions(800, 600);	// width, height of each region
	Map.SetViewPort(0, 0);

	for(int i=0; i<20; ++i)
	{
		for(int j=0; j<3; ++j)
		{
			switch(j)
			{
			case 0:
				Map.LoadBackgroundImage(j, i, "images/top.bmp", 
										Draw.GetDirectDrawObject(), 
										Draw.GetTransparentColorKey());
				break;

			case 1:
				Map.LoadBackgroundImage(j, i, "images/middle.bmp", 
										Draw.GetDirectDrawObject(), 
										Draw.GetTransparentColorKey());
				break;

			case 2:
				Map.LoadBackgroundImage(j, i, "images/bottom.bmp", 
										Draw.GetDirectDrawObject(), 
										Draw.GetTransparentColorKey());
				break;
			}// end switch
		}// end for
	}// end for

	ship.m_Sprite.LoadSurface("images/spaceship.bmp", 
		                      Draw.GetDirectDrawObject(),
							  Draw.GetTransparentColorKey());

}

/*
    
	Map.SetRegions(100, 100);			// rows, columns
	Map.SetRegionDimensions(50, 50);	// width, height of each region
	Map.SetViewPort(0, 0);

	for(int i=0; i<100; ++i)
	{
		for(int j=0; j<100; ++j)
		{
			if(j%3 == 0 || i%3 == 0)
			{
				Map.LoadBackgroundImage(j, i, "images/back3.bmp", 
										Draw.GetDirectDrawObject(), 
										Draw.GetTransparentColorKey());

			}// end if
			else if(j%5 == 0 && i%5 == 0)
			{
				Map.LoadBackgroundImage(j, i, "images/back2.bmp", 
										Draw.GetDirectDrawObject(), 
										Draw.GetTransparentColorKey());
			}// end else if

			else
			{				
				Map.LoadBackgroundImage(j, i, "images/back1.bmp", 
										Draw.GetDirectDrawObject(), 
										Draw.GetTransparentColorKey());		
			}// end else

		}// end for

	}// end for

	ship.m_Sprite.LoadSurface("images/man.bmp", 
		                      Draw.GetDirectDrawObject(),
							  Draw.GetTransparentColorKey());

*/

/******************************************************************************/
/*                                                                            */
/*   Windows Instantiation/Initalization Function Definition                  */
/*                                                                            */
/******************************************************************************/
static BOOL Init(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASS  wc;

    // Set up and register window class
    wc.style                 = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc           = (WNDPROC) WindowProc;
    wc.cbClsExtra            = 0;
    wc.cbWndExtra            = sizeof(DWORD);
    wc.hInstance             = hInstance;
    wc.hIcon                 = NULL;
    wc.hCursor               = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground         = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName          = NULL;
    wc.lpszClassName         = "App";


    if(!RegisterClass(&wc)) 
	{
		MessageBox(NULL, "Could not create register window class", 
			             "Initialization Error.", 
				         MB_ICONEXCLAMATION|MB_OK);
        return FALSE;
	}

    // Get dimensions of display
    int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Create a window and display
	HWND hWnd;

    hWnd = CreateWindow("App",   				// class
                        "App",  				// caption
						WS_VISIBLE|WS_POPUP,	// style 
						0,						// left
						0,						// top
						ScreenWidth,			// width
						ScreenHeight,			// height
                        NULL,					// parent window
                        NULL,					// menu 
                        hInstance,				// instance
                        NULL);					// parms
    if(!hWnd) 
	{
		MessageBox(NULL, "Could not create window", 
			             "Initialization Error.", 
				         MB_ICONEXCLAMATION|MB_OK);
        return FALSE;
	}// end if

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


	hWndGame      = hWnd;
	hInstanceGame = hInstance; 

	Draw.InitializeDirectDrawInterface(800, 600, 32, hWnd);

	Input.InitializeDirectInputInterface(hWnd, hInstance);


	CreateGameMap();

	// return success to caller
	return TRUE;
}


bool ProcessKeyboardInput()
{
	bool   notDone = true;
	float  value   = 5.0f;
	
	Input.GetKeyboardInput();

	

	if(Input.IsKeyDown(DIK_ESCAPE))
	{
		notDone = false;
	}// end if

	if(Input.IsKeyDown(DIK_UP))
	{
		if(Map.GetViewPortY() > 0)
		{
		  Map.UpdateViewPort(0, -1.0*value);
		}// end if
	}// end if

	if(Input.IsKeyDown(DIK_DOWN))
	{
		if(Map.GetViewPortY() + 600 < Map.GetMapHeight())
		{
			Map.UpdateViewPort(0, 1.0*value);
		}// end if
	}// end if

	if(Input.IsKeyDown(DIK_LEFT))
	{
		if(Map.GetViewPortX() > 0)
		{
			Map.UpdateViewPort(-1.0*value, 0);
		}// end if
	}// end if

	if(Input.IsKeyDown(DIK_RIGHT))
	{
		if(Map.GetViewPortX() + 800 < Map.GetMapWidth())
		{
			Map.UpdateViewPort(1.0*value, 0);
		}// end if
	}// end if

	return notDone;
}




void RenderFrame()
{
	Map.RenderGameMap(Draw.GetBackBuffer());

	ship.m_Sprite.RenderSprite(ship.m_x, ship.m_y, Draw.GetBackBuffer());

	Draw.Flip();
}



int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

	bool  notDone = true;

	const int FRAME_RATE = 100;

	MSG msg; 

	Timer.InitializeGameTimer(FRAME_RATE);

	// Initialize the application, exit on failure
    if(!Init(hInstance, nCmdShow)) 
	{
		Cleanup();
        return FALSE;
	}// end if


	ShowCursor(false);

	Timer.SetNextFrameTime();
	
	// Run till completed 
	while(notDone) 
	{
		// Is there a windows message to process? 
		if(PeekMessage( &msg, NULL, 0, 0, PM_REMOVE)) 
		{ 
			// Yes, is it a quit message? 
			if(msg.message == WM_QUIT) 
			{
				notDone = false; 
			}// end if

			// dispatch the message 
			TranslateMessage(&msg);
			DispatchMessage(&msg); 
		} 
		else 
		{
			// Is it time to render the frame? 
			if(Timer.IsTimeUp()) 
			{ 
				Timer.CalculateElapsedTime();

				// render the frame 
				RenderFrame();

				// Process keyboard commands.
				notDone = ProcessKeyboardInput();

				// Update the timer with the time when the next 
				// frame update is to occur.
				Timer.SetNextFrameTime();
				
				// Determine if our cooperative level has been lost.
				if(Draw.TestCooperativeLevel() != DD_OK)
				{
					Draw.Cleanup();
					exit(1);
				}// end if

			}// end (render frame)

		}// end else (no message to process)

	}// end while


	// Destroy all DirectX components.
	Cleanup();

	// exit returning final message
    return (msg.wParam);
}






