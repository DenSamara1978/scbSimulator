// scbSimulator.cpp: Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "scbSimulator.h"
#include "application\Application.h"

#define MAX_LOADSTRING 100

using namespace application;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Application* app = Application::getInstance();
	if (FAILED(app->initializeWindow(hInstance, nCmdShow, L"Direct3D11")))
		return 0;
	app->runMessageLoop();
	return 0;
}
