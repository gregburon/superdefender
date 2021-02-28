
#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include <dinput.h>
#include <stdio.h>
#include <string.h>
#include <string>


#ifndef DIRECTINPUT_H
#define DIRECTINPUT_H


class DirectInput
{
public:

	// Constructors and destructors.
	DirectInput();
	~DirectInput();


	// Public interface member functions.
	bool InitializeDirectInputInterface(HWND hWnd, HINSTANCE hInstance);

	void GetKeyboardInput();

	int  IsKeyDown(unsigned char key);

	void Cleanup();

private:

	// Member variables.
	LPDIRECTINPUT           m_lpDI;
	LPDIRECTINPUTDEVICE     m_pKeyboard;
	char                    m_KeyBuffer[256];

};

#endif