// scbSimulator.cpp: Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "scbSimulator.h"
#include "genApplication.h"

#include "scb\scbTimer.h"

#define MAX_LOADSTRING 100

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	genApplication app;
	if ( FAILED ( app.InitWindow ( hInstance, nCmdShow, L"Direct3D11" ) ) )
		return 0;
	app.RunMessageLoop ();
	return 0;
}
