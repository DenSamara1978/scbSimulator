#pragma once

#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <vector>
#include <string>
#include <algorithm>
#include "..\stdafx.h"


using namespace DirectX;
using std::vector;
using std::wstring;

namespace application
{

	class Application
	{
	public:
		~Application();

		static Application* getInstance();

		HWND getHwnd() const;
		unsigned int getMainWindowWidth() const;
		unsigned int getMainWindowHeight() const;

		HRESULT initializeWindow (HINSTANCE hInstance, int nCmdShow, const wchar_t* graphics); // ����� ������������� windows-����������

		void runMessageLoop (); // �������� �������� ����� ����������

		void action1 ();
		void action2 ();
		void action3 ();
		void action4 ();
		void action5 ();
		void action6 ();
		void action7 ();
		void action8 ();
		void action9 ();
		void action10 ();
		void action11 ();
		void action12 ();
		void action13 ();
		void action14 ();
		void action15 ();
		void action16 ();
		void action17 ();

	private:
		Application();

		static Application* instance;

		HWND hwnd;
		unsigned int mainWindowHeight;
		unsigned int mainWindowWidth;
		HINSTANCE hInstance;
		HACCEL hAccelTable;

		static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // ������� Windows-��������� ��������� ������

		void onResize(UINT width, UINT height); // ������ ������ RenderTarget
	};

	inline Application* Application::getInstance()
	{
		if (Application::instance == nullptr)
			Application::instance = new Application;
		return Application::instance;
	}

	inline HWND Application::getHwnd() const
	{
		return this->hwnd;
	}

	inline unsigned int Application::getMainWindowWidth() const
	{
		return this->mainWindowWidth;
	}

	inline unsigned int Application::getMainWindowHeight() const
	{
		return this->mainWindowHeight;
	}
}