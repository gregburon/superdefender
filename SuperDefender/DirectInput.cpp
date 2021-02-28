

#pragma warning(disable: 4786)

#include <typeinfo.h>

using namespace std;

#include "DirectInput.h"


DirectInput::DirectInput()
{

}


DirectInput::~DirectInput()
{

}

int DirectInput::IsKeyDown(unsigned char key)
{
	return (m_KeyBuffer[key] & 0x80);
}

bool DirectInput::InitializeDirectInputInterface(HWND hWnd, HINSTANCE hInstance)
{
    // Create the DI object
    if(DirectInputCreate(hInstance, DIRECTINPUT_VERSION, &m_lpDI, NULL) != DI_OK)
    {
		MessageBox(NULL, "Could not create direct input object", 
			             "Initialization Error.", 
				         MB_ICONEXCLAMATION|MB_OK);
        return FALSE;
    }

    // Create and initialize the keyboard device
    if(m_lpDI->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL) != DI_OK)
    {
		MessageBox(NULL, "Could not initialize keyboard device", 
			             "Initialization Error.", 
				         MB_ICONEXCLAMATION|MB_OK);
		return FALSE;
    }// end if
    if(m_pKeyboard->SetDataFormat(&c_dfDIKeyboard) != DI_OK)
    {
        m_pKeyboard->Release();
		m_pKeyboard = NULL;
        return FALSE;
    }// end if
    if(m_pKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND|DISCL_NONEXCLUSIVE) != DI_OK)
    {
        m_pKeyboard->Release();
		m_pKeyboard = NULL;
        return FALSE;
    }// end if
    if(m_pKeyboard->Acquire() != DI_OK)
    {
        m_pKeyboard->Release();
		m_pKeyboard = NULL;
        return FALSE;
    }// end if

  
	return true;
}

void DirectInput::GetKeyboardInput()
{
	if(m_pKeyboard->GetDeviceState(sizeof(m_KeyBuffer), (LPVOID)&m_KeyBuffer) == DIERR_INPUTLOST)
	{
		// Reacquire the keyboard and try again
		if(m_pKeyboard->Acquire() == DI_OK)
		{
			m_pKeyboard->GetDeviceState(sizeof(m_KeyBuffer), (LPVOID)&m_KeyBuffer);
		}
	}// end if
}

void DirectInput::Cleanup()
{

    if(m_pKeyboard)
    {
         m_pKeyboard->Unacquire();
         m_pKeyboard->Release();
         m_pKeyboard = NULL;
    }// end if

    m_lpDI->Release();
	m_lpDI = NULL;
}