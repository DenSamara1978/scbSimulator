#pragma once

#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <vector>
#include <string>
#include <algorithm>
#include "stdafx.h"
#include "scb\scbTimer.h"
#include "scb\scbAbstractScheme.h"

class visualAbstract;

using namespace DirectX;
using std::vector;
using std::wstring;

class graphServer;

class genApplication
{
	static genApplication* m_Instance;

	graphServer* m_GraphicsServer;
	scbTimer m_scbTimer;
	vector<scbAbstractScheme*> m_Schemes;

	HWND m_Hwnd;
	HINSTANCE m_HInstance;
	HACCEL m_HAccelTable;

	static LRESULT CALLBACK WndProc ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ); // главная Windows-процедура обратного вызова

	void OnResize ( UINT width, UINT height ); // меняет размер RenderTarget

public:
	genApplication ();
	~genApplication ();

	HWND GetHWND () const;

	static genApplication* Instance ();

	scbAbstractScheme* GetScheme ( const wstring& name );

	HRESULT InitWindow ( HINSTANCE hInstance, int nCmdShow, const wchar_t* graphics ); // Общая инициализация windows-приложения

	void RunMessageLoop (); // итерация главного цикла приложения

	void Action1 ();
	void Action2 ();
	void Action3 ();
	void Action4 ();
	void Action5 ();
	void Action6 ();
	void Action7 ();
	void Action8 ();
	void Action9 ();
	void Action10 ();
	void Action11 ();
	void Action12 ();
	void Action13 ();
	void Action14 ();
	void Action15 ();
	void Action16 ();
	void Action17 ();
};

inline genApplication* genApplication::Instance ()
{
	return genApplication::m_Instance;
}

inline HWND genApplication::GetHWND () const
{
	return this->m_Hwnd;
}

inline scbAbstractScheme* genApplication::GetScheme ( const wstring& name )
{
	auto scheme = find_if ( this->m_Schemes.cbegin (), this->m_Schemes.cend (), [&] ( const scbAbstractScheme* scheme ) -> bool { return scheme->IsA ( name ); } );
	return ( scheme != this->m_Schemes.cend () ) ? *scheme : nullptr;
}
