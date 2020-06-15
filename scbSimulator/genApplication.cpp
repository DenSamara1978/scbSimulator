#include "resource.h"
#include "genApplication.h"
#include "visual\visualPultTablo.h"
#include "visual\visualPultTabloButton.h"
#include "visual\visualPultTabloCommutator.h"
#include "visual\visualLightSignal.h"
#include "visual\visualMotorDrive.h"
#include "graphics\graphServer.h"
#include "graphics\graphCamera.h"
#include "graphics\graphVertexShader.h"
#include "graphics\graphPixelShader.h"
#include "scb\scbLightSignal.h"
#include "scb\scbMotorDrive.h"
#include "scb\scbMotorDriveDevice.h"
#include "scb\scbPultTablo.h"
#include "scb\scbPultTabloAbstractButton.h"
#include "scb\scbBus.h"
#include "scb\scbChain.h"
#include "scb\scbSchemeGPR.h"
#include "scb\scbSchemeSSE16.h"
#include "scb\scbSchemeSSE32.h"
#include "scb\scbSchemeSSE64.h"
#include "scb\scbSchemeSSE128.h"
#include "scb\scbSchemeSSE256.h"
#include "scb\scbSchemeAVX64.h"
#include "scb\scbSchemeAVX128.h"
#include "scb\scbSchemeAVX256.h"
#include "scb\scbSchemeOutput.h"
#include "track\trackSwitch.h"

genApplication* genApplication::m_Instance = nullptr;

genApplication::genApplication () :
	m_GraphicsServer ( nullptr ),
	m_Hwnd ( 0 ),
	m_HInstance ( 0 ),
	m_HAccelTable ( 0 )
{
	genApplication::m_Instance = this;
}

genApplication::~genApplication ()
{
	if ( this->m_GraphicsServer != nullptr )
	{
		delete this->m_GraphicsServer;
		this->m_GraphicsServer = nullptr;
	}
	for ( auto& scheme : this->m_Schemes )
	{
		delete scheme;
		scheme = nullptr;
	}
	genApplication::m_Instance = nullptr;
}

void genApplication::RunMessageLoop ()
{
	MSG msg = { 0 };

	while ( msg.message != WM_QUIT )
	{
		if ( PeekMessage ( &msg, 0, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage ( &msg );
			DispatchMessage ( &msg );
		}
		else
		{
			this->m_scbTimer.Time ();
			if ( this->m_GraphicsServer->Render () != S_OK )
				break;
		}
	}
}

HRESULT genApplication::InitWindow ( HINSTANCE hInstance, int nCmdShow, const wchar_t* graphics )
{
	this->m_HInstance = hInstance;

	WNDCLASSEX wcex = { sizeof ( WNDCLASSEX ) };
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = genApplication::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = this->m_HInstance;
	wcex.hIcon = LoadIcon ( this->m_HInstance, MAKEINTRESOURCE ( IDI_SCBSIMULATOR ) );
	wcex.hIconSm = LoadIcon ( this->m_HInstance, MAKEINTRESOURCE ( IDI_SMALL ) );
	wcex.hbrBackground = ( HBRUSH ) ( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = MAKEINTRESOURCEW ( IDC_SCBSIMULATOR );
	wcex.hCursor = LoadCursor ( 0, IDI_APPLICATION );
	wcex.lpszClassName = L"scbSimulator";

	RegisterClassEx ( &wcex );

	this->m_Hwnd = CreateWindow (
		L"scbSimulator",
		L"Симулятор схем СЦБ",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1500,
		1000,
		0,
		0,
		this->m_HInstance,
		nullptr
	);

	if ( !this->m_Hwnd )
		return E_FAIL;

	ShowWindow ( this->m_Hwnd, SW_SHOWNORMAL );

	this->m_HAccelTable = LoadAccelerators ( this->m_HInstance, MAKEINTRESOURCE ( IDC_SCBSIMULATOR ) );

	if ( lstrcmp ( graphics, L"Direct3D11" ) == 0 )
		this->m_GraphicsServer = new graphServer;
	else
		return E_FAIL;

	if ( this->m_GraphicsServer->InitDevice () != S_OK )
		return E_FAIL;
	if ( this->m_GraphicsServer->LoadVertexShader ( L"Shaders.hlsl", "VS_main", L"vs", L"PN" ) != S_OK )
		return E_FAIL;
	if ( this->m_GraphicsServer->LoadPixelShader ( L"Shaders.hlsl", "PS_main", L"ps" ) != S_OK )
		return E_FAIL;

	graphCamera* pCamera = this->m_GraphicsServer->GetCamera ( 0 );
	if ( pCamera == nullptr )
		return E_FAIL;
	pCamera->SetPosition ( 0.0f, 10.0f, -20.0f );
	pCamera->SetLookPoint ( 0.0f, 4.0f, 0.0f );
	pCamera->SetOrientation ( 0.0f, 1.0f, 0.0f );

	this->m_GraphicsServer->SetAmbientColor ( 0.3f, 0.3f, 0.3f );
	this->m_GraphicsServer->SetLightColor ( 0.8f, 0.8f, 0.8f );
	this->m_GraphicsServer->SetLightDirection ( 2.0f, -2.0f, 1.0f );

	graphVertexShader* pVS = this->m_GraphicsServer->GetVertexShader ( this->m_GraphicsServer->GetVertexShaderIndex ( L"vs" ) );
	pVS->SetConstantType ( 0, graphShader::WorldMatrix );
	pVS->SetConstantType ( 1, graphShader::ViewMatrix );
	pVS->SetConstantType ( 2, graphShader::ProjectionMatrix );
	pVS->SetConstantType ( 3, graphShader::DiffuseColor );
	pVS->SetConstantType ( 4, graphShader::SpecularColor );
	pVS->SetConstantType ( 5, graphShader::EmissiveColor );
	pVS->SetConstantType ( 6, graphShader::AmbientColor );
	pVS->SetConstantType ( 7, graphShader::DirectionLightColor );
	pVS->SetConstantType ( 8, graphShader::DirectionLightDir );
	if ( pVS->CreateConstantBuffer () != S_OK )
		return E_FAIL;

	graphPixelShader* pPS = this->m_GraphicsServer->GetPixelShader ( this->m_GraphicsServer->GetPixelShaderIndex ( L"ps" ) );
	pPS->SetConstantType ( 0, graphShader::WorldMatrix );
	pPS->SetConstantType ( 1, graphShader::ViewMatrix );
	pPS->SetConstantType ( 2, graphShader::ProjectionMatrix );
	pPS->SetConstantType ( 3, graphShader::DiffuseColor );
	pPS->SetConstantType ( 4, graphShader::SpecularColor );
	pPS->SetConstantType ( 5, graphShader::EmissiveColor );
	pPS->SetConstantType ( 6, graphShader::AmbientColor );
	pPS->SetConstantType ( 7, graphShader::DirectionLightColor );
	pPS->SetConstantType ( 8, graphShader::DirectionLightDir );
	if ( pPS->CreateConstantBuffer () != S_OK )
		return E_FAIL;

	if ( visualLightSignal::InitBuffers () != S_OK )
		return E_FAIL;
	if ( visualPultTabloButton::InitBuffers () != S_OK )
		return E_FAIL;
	if ( visualPultTabloCommutator::InitBuffers () != S_OK )
		return E_FAIL;
	if ( visualPultTablo::InitBuffers () != S_OK )
		return E_FAIL;
	if ( visualMotorDrive::InitBuffers () != S_OK )
		return E_FAIL;

	scbLightSignal* pLS = new scbLightSignal ( L"Светофор.М2" );
	this->m_Schemes.push_back ( pLS );
	pLS->SetDeviceCount ( 6 );
	if ( !pLS->SetLamp ( 0, scbLightSignal::LampPurpose::FirstYellow ) )
		return E_FAIL;
	if ( !pLS->SetLamp ( 1, scbLightSignal::LampPurpose::Blue ) )
		return E_FAIL;
	if ( !pLS->SetLamp ( 2, scbLightSignal::LampPurpose::White ) )
		return E_FAIL;
	if ( !pLS->SetLamp ( 3, scbLightSignal::LampPurpose::Green ) )
		return E_FAIL;
	if ( !pLS->SetLamp ( 4, scbLightSignal::LampPurpose::Red ) )
		return E_FAIL;
	if ( !pLS->SetLamp ( 5, scbLightSignal::LampPurpose::SecondYellow ) )
		return E_FAIL;

	visualLightSignal* pVLS = new visualLightSignal ();
	this->m_GraphicsServer->AddVisualObject ( pVLS );
	if ( pVLS->AssignScbLightSignal ( pLS ) != S_OK )
		return E_FAIL;

	pLS = new scbLightSignal ( L"Светофор.М3" );
	this->m_Schemes.push_back ( pLS );
	pLS->SetDeviceCount ( 1 );
	if ( !pLS->SetLamp ( 0, scbLightSignal::LampPurpose::Green ) )
		return E_FAIL;

	pVLS = new visualLightSignal ();
	this->m_GraphicsServer->AddVisualObject ( pVLS );
	pVLS->SetPosition ( 3.0f, 5.0f, 0.0f );
	if ( pVLS->AssignScbLightSignal ( pLS ) != S_OK )
		return E_FAIL;

	scbPultTablo* pPT = new scbPultTablo ( L"Пульт" );
	this->m_Schemes.push_back ( pPT );
	pPT->SetDeviceCount ( 1, 2, 3, 0, 1 );
	pPT->SetButtonKmd ( 0, scbPultTablo::Color::White, 0 );
	pPT->SetButtonKmd ( 1, scbPultTablo::Color::Green, 1, 2 );
	pPT->SetCommutatorKmtn ( 2, scbPultTablo::Color::Red, 3, 4, 5, 6, 7, 8 );
	pPT->SetOutput ( 0, L"Светофор.М1.Исполнение", 0 );
	pPT->SetOutput ( 1, L"Светофор.М3.Исполнение", 0 );
	pPT->MapInputOutput ( 0, 0, 0 );
	pPT->MapInputOutput ( 0, 1, 3 );
	pPT->MapInputOutput ( 0, 2, 8 );
	pPT->MapInputOutput ( 0, 3, 9 );
	pPT->MapInputOutput ( 0, 4, 11 );
	pPT->MapInputOutput ( 0, 5, 10 );
	pPT->MapInputOutput ( 0, 6, 12 );
	pPT->MapInputOutput ( 0, 7, 14 );
	pPT->MapInputOutput ( 0, 8, 13 );
	pPT->MapInputOutput ( 1, 0, 0 );

	visualPultTabloButton* pVButton = new visualPultTabloButton ();
	pVButton->SetPosition ( -5.0f, 0.0f, 0.0f );
	this->m_GraphicsServer->AddVisualObject ( pVButton );
	if ( pVButton->AssignButton ( pPT, 0 ) != S_OK )
		return E_FAIL;

	pVButton = new visualPultTabloButton ();
	pVButton->SetPosition ( -7.0f, 0.0f, 0.0f );
	this->m_GraphicsServer->AddVisualObject ( pVButton );
	if ( pVButton->AssignButton ( pPT, 1 ) != S_OK )
		return E_FAIL;

	visualPultTabloCommutator* pVComm = new visualPultTabloCommutator ();
	pVComm->SetPosition ( -9.0f, 0.0f, 0.0f );
	this->m_GraphicsServer->AddVisualObject ( pVComm );
	if ( pVComm->AssignCommutator ( pPT, 2 ) != S_OK )
		return E_FAIL;

	visualPultTablo* pVPT = new visualPultTablo ();
	pVPT->SetPosition ( -10.0f, 6.0f, 4.0f );
	this->m_GraphicsServer->AddVisualObject ( pVPT );
	if ( pVPT->AssignPultTablo ( pPT ) != S_OK )
		return E_FAIL;

	pVPT->AddCellLamp ( 0, 0, -2.25f, 2.0f, 0, scbPultTablo::Color::Yellow );
	pVPT->AddCellLamp ( 0, 1, -0.75f, 2.0f, 0, scbPultTablo::Color::Green );
	pVPT->AddCellLamp ( 0, 2, 0.75f, 2.0f, 0, scbPultTablo::Color::Red );
	pVPT->AddCellLamp ( 0, 3, 2.25f, 2.0f, 0, scbPultTablo::Color::White );
	pVPT->AddRoundLamp ( 0, 4, -1.5f, 4.0f, scbPultTablo::Color::Green );
	pVPT->AddRoundLamp ( 0, 5, 1.5f, 4.0f, scbPultTablo::Color::Blue );
	pVPT->AddCellLamp ( 0, 6, -2.25f, 0.0f, 0, scbPultTablo::Color::White );
	pVPT->AddCellLamp ( 0, 7, -0.75f, 0.0f, 0, scbPultTablo::Color::Green );
	pVPT->AddCellLamp ( 0, 8, 0.75f, 0.0f, 0, scbPultTablo::Color::Green );
	pVPT->AddCellLamp ( 0, 9, 2.25f, 0.0f, 0, scbPultTablo::Color::White );
	pVPT->AddCellLamp ( 0, 10, -2.25f, -2.0f, 0, scbPultTablo::Color::Yellow );
	pVPT->AddCellLamp ( 0, 11, -0.75f, -2.0f, 0, scbPultTablo::Color::Yellow );
	pVPT->AddCellLamp ( 0, 12, 0.75f, -2.0f, 0, scbPultTablo::Color::Yellow );
	pVPT->AddCellLamp ( 0, 13, 2.25f, -2.0f, 0, scbPultTablo::Color::Yellow );
	pVPT->AddRoundLamp ( 0, 14, -1.5f, -4.0f, scbPultTablo::Color::Green );
	pVPT->AddRoundLamp ( 0, 15, 0.0f, -4.0f, scbPultTablo::Color::Yellow );
	pVPT->AddRoundLamp ( 0, 16, 1.5f, -4.0f, scbPultTablo::Color::White );

	trackSwitch* sw = new trackSwitch;

	scbMotorDrive* pMD = new scbMotorDrive ( L"Стрелка.2" );
	this->m_Schemes.push_back ( pMD );
	pMD->GetDriveDevice ()->SetSwitch ( sw );
	pMD->SetDeviceCount ( 1 );
	pMD->SetOutput ( 0, L"Светофор.М1.Исполнение" );

	pMD->MapInputOutput ( 0, 0, 15 );
	pMD->MapInputOutput ( 0, 1, 16 );
	pMD->MapInputOutput ( 0, 2, 17 );
	pMD->MapInputOutput ( 0, 3, 18 );
	pMD->MapInputOutput ( 0, 4, 19 );
	pMD->MapInputOutput ( 0, 5, 20 );
	pMD->MapInputOutput ( 0, 6, 21 );
	pMD->MapInputOutput ( 0, 7, 22 );
	pMD->MapInputOutput ( 0, 8, 23 );
	pMD->MapInputOutput ( 0, 9, 24 );
	pMD->MapInputOutput ( 0, 10, 25 );

	visualMotorDrive* pVMD = new visualMotorDrive ();
	pVMD->SetPosition ( 8.0f, 4.0f, 3.0f );
	this->m_GraphicsServer->AddVisualObject ( pVMD );
	if ( pVMD->AssignScbMotorDrive ( pMD ) != S_OK )
		return E_FAIL;

	scbScheme* pScheme = new scbSchemeSSE128 ( L"Светофор.М1.Исполнение", 0, 27, 0, 0 );
	this->m_Schemes.push_back ( pScheme );
	pScheme->SetDeviceCount ( 7 );

	pScheme->SetNeutralRelay ( 0, 1, 2 );
	pScheme->AddRelayTimeSample ( 0, 0, 1, 100, 50 );
	pScheme->AddRelayTimeSample ( 0, 1, 0, 200, 150 );
	pScheme->AddRelayConvertation ( 0, 0, 0 );

	pScheme->SetNeutralRelay ( 1, 4, 5 );
	pScheme->AddRelayTimeSample ( 1, 0, 1, 100, 50 );
	pScheme->AddRelayTimeSample ( 1, 1, 0, 200, 150 );
	pScheme->AddRelayConvertation ( 1, 5, 0 );

	pScheme->SetNeutralRelay ( 2, 6, 7 );
	pScheme->AddRelayTimeSample ( 2, 0, 1, 100, 50 );
	pScheme->AddRelayTimeSample ( 2, 1, 0, 200, 150 );
	pScheme->AddRelayConvertation ( 2, 12, 0 );

	pScheme->SetOutput ( 3, L"Светофор.М2" );
	pScheme->SetOutput ( 4, L"Пульт", 0 );
	pScheme->SetOutput ( 5, L"Стрелка.2" );
	pScheme->SetOutput ( 6, L"Шина" );

	pScheme->MapInputOutput ( 3, 1, 6 );
//	pScheme->MapInputOutput ( 3, 2, 3 );
	pScheme->MapInputOutput ( 3, 3, 10 );
//	pScheme->MapInputOutput ( 3, 4, 5 );
	pScheme->MapInputOutput ( 3, 6, 2 );
//	pScheme->MapInputOutput ( 3, 7, 1 );
	pScheme->MapInputOutput ( 3, 8, 30 );
//	pScheme->MapInputOutput ( 3, 9, 15 );
	pScheme->MapInputOutput ( 3, 10, 18 );
//	pScheme->MapInputOutput ( 3, 11, 9 );
	pScheme->MapInputOutput ( 3, 13, 22 );
//	pScheme->MapInputOutput ( 3, 14, 11 );

	pScheme->MapInputOutput ( 4, 15, 0 );
	pScheme->MapInputOutput ( 4, 16, 1 );
	pScheme->MapInputOutput ( 4, 17, 2 );
	pScheme->MapInputOutput ( 4, 18, 3 );
	pScheme->MapInputOutput ( 4, 19, 4 );
	pScheme->MapInputOutput ( 4, 20, 5 );
	pScheme->MapInputOutput ( 4, 21, 6 );
	pScheme->MapInputOutput ( 4, 22, 7 );
	pScheme->MapInputOutput ( 4, 23, 8 );
	pScheme->MapInputOutput ( 4, 24, 9 );
	pScheme->MapInputOutput ( 4, 25, 10 );
	pScheme->MapInputOutput ( 4, 26, 11 );
	pScheme->MapInputOutput ( 4, 27, 12 );
	pScheme->MapInputOutput ( 4, 28, 13 );
	pScheme->MapInputOutput ( 4, 29, 14 );
	pScheme->MapInputOutput ( 4, 30, 15 );
	pScheme->MapInputOutput ( 4, 31, 16 );

	pScheme->MapInputOutput ( 5, 15, 0 );
	pScheme->MapInputOutput ( 5, 18, 1 );

	pScheme->MapInputOutput ( 6, 21, 0 );
	pScheme->MapInputOutput ( 6, 24, 35 );

	scbOutputStream mask, result;

	// Б = (Кнопка_белого)
	mask = { 1, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 0, mask, result );

	// {Синий} = !Б
	mask = { 4, 0, 0, 0, 0, 0, 0, 0 };
	result = { 6, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 1, mask, result );

	// {Белый} = Б
	mask = { 2, 0, 0, 0, 0, 0, 0, 0 };
	result = { 0x18, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 2, mask, result );

	// З = (Кнопка_зеленого)
	mask = { 8, 0, 0, 0, 0, 0, 0, 0 };
	result = { 0x20, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 3, mask, result );

	// {Красный} = !З
	mask = { 0x20, 0, 0, 0, 0, 0, 0, 0 };
	result = { 0xC0, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 4, mask, result );

	// {Зеленый} = З
	mask = { 0x10, 0, 0, 0, 0, 0, 0, 0 };
	result = { 0x300, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 5, mask, result );

	// {Первый_желтый} = З & Б
	mask = { 0x12, 0, 0, 0, 0, 0, 0, 0 };
	result = { 0xC00, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 6, mask, result );

	// 2Ж = (Кнопка_белого)
	mask = { 1, 0, 0, 0, 0, 0, 0, 0 };
	result = { 0x1000, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 7, mask, result );

	// 2Ж = 2Ж & !(Кнопка_зеленого)
	mask = { 0x140, 0, 0, 0, 0, 0, 0, 0 };
	result = { 0x1000, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 8, mask, result );

	// {Второй_желтый} = 2Ж
	mask = { 0x40, 0, 0, 0, 0, 0, 0, 0 };
	result = { 0x6000, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 9, mask, result );

	// Коммутатор - левый фронт
	mask = { 1 << 9, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1 << 15, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 10, mask, result );

	// Коммутатор - левый тыл
	mask = { 1 << 11, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1 << 16, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 11, mask, result );

	// Коммутатор - правый фронт
	mask = { 1 << 10, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1 << 18, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 12, mask, result );

	// Коммутатор - правый тыл
	mask = { 1 << 12, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1 << 17, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 13, mask, result );

	// Коммутатор - отжат
	mask = { 1 << 13, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1 << 19, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 14, mask, result );

	// Коммутатор - нажат
	mask = { 1 << 14, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1 << 20, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 15, mask, result );

	// Привод - автопереключатель 1
	mask = { 1 << 16, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1 << 21, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 16, mask, result );

	// Привод - автопереключатель 2
	mask = { 1 << 15, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1 << 22, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 17, mask, result );

	// Привод - автопереключатель 3
	mask = { 1 << 17, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1 << 23, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 18, mask, result );

	// Привод - автопереключатель 4
	mask = { 1 << 18, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1 << 24, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 19, mask, result );

	// Привод - автопереключатель 1 без инея
	mask = { 1 << 21, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1 << 25, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 20, mask, result );

	// Привод - автопереключатель 2 без инея
	mask = { 1 << 22, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1 << 26, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 21, mask, result );

	// Привод - автопереключатель 3 без инея
	mask = { 1 << 23, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1 << 27, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 22, mask, result );

	// Привод - автопереключатель 4 без инея
	mask = { 1 << 24, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1 << 28, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 23, mask, result );

	// Привод - ток
	mask = { 1 << 19, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1 << 29, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 24, mask, result );

	// Привод - ток фрикции
	mask = { 1 << 20, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1 << 30, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 25, mask, result );

	// Привод - блокировочный контакт
	mask = { 1 << 25, 0, 0, 0, 0, 0, 0, 0 };
	result = { 0x80000000, 0, 0, 0, 0, 0, 0, 0 };
	pScheme->SetMainCircuit ( 26, mask, result );

	scbChain* pBus = new scbChain ( L"Шина", 2 );
	pBus->SetDeviceCount ( 1 );
	pBus->SetOutput ( 0, L"Светофор.М2", -1 );
	pBus->MapInputOutput ( 0, 0, 16 );
//	pBus->MapInputOutput ( 0, 0, 17 );
	this->m_Schemes.push_back ( pBus );

	// Тестовая схема для проверки работоспособности любого типа схем
	const int stride = 128;
	pScheme = new scbSchemeGPR ( L"Светофор.М3.Исполнение", 0, stride, 0, 0 );
	this->m_Schemes.push_back ( pScheme );
	pScheme->SetDeviceCount ( stride );

	for ( int i = 0; i < stride - 1; ++i )
	{
		pScheme->SetNeutralRelay ( i, i + 1 );
		pScheme->AddRelayTimeSample ( i, 0, 1, 20, 10 );
		pScheme->AddRelayTimeSample ( i, 1, 0, 20, 10 );
		pScheme->AddRelayConvertation ( i, i + 1, 0 );

		mask = { 0, 0, 0, 0, 0, 0, 0, 0 };
		result = { 0, 0, 0, 0, 0, 0, 0, 0 };
		mask.Mask [( i & 0xE0 ) >> 5] = 1L << ( i & 0x1F );
		result.Mask [( ( i + 1 ) & 0xE0 ) >> 5] = 1L << ( ( i + 1 ) & 0x1F );
		pScheme->SetMainCircuit ( i, mask, result );
	}
	mask = { 0, 0, 0, 0, 0, 0, 0, 0 };
	result = { 1, 0, 0, 0, 0, 0, 0, 0 };
	mask.Mask [(( stride - 1 ) & 0xE0 ) >> 5] = 1L << (( stride - 1 ) & 0x1F );
	pScheme->SetMainCircuit ( stride - 1, mask, result );

	pScheme->SetOutput ( stride - 1, L"Светофор.М3" );
	pScheme->MapInputOutput ( stride - 1, stride - 1, 30 );


	for ( auto& scheme : this->m_Schemes )
	{
		scheme->Init ();
		scheme->MarkToRecalculate ();
	}

	return S_OK;
}

void genApplication::Action1 ()
{
	dynamic_cast< scbPultTablo* > ( this->GetScheme ( L"Пульт" ))->GetActiveDevice ( 0 )->Press ();
}

void genApplication::Action2 ()
{
	dynamic_cast< scbPultTablo* > ( this->GetScheme ( L"Пульт" ))->GetActiveDevice ( 0 )->Release ();
}

void genApplication::Action3 ()
{
	dynamic_cast< scbPultTablo* > ( this->GetScheme ( L"Пульт" ))->GetActiveDevice ( 1 )->Press ();
}

void genApplication::Action4 ()
{
	dynamic_cast< scbPultTablo* > ( this->GetScheme ( L"Пульт" ))->GetActiveDevice ( 1 )->Release ();
}

void genApplication::Action5 ()
{
	dynamic_cast< scbPultTablo* > ( this->GetScheme ( L"Пульт" ))->GetActiveDevice ( 2 )->Press ();
}

void genApplication::Action6 ()
{
	dynamic_cast< scbPultTablo* > ( this->GetScheme ( L"Пульт" ))->GetActiveDevice ( 2 )->Release ();
}

void genApplication::Action7 ()
{
	dynamic_cast< scbPultTablo* > ( this->GetScheme ( L"Пульт" ))->GetActiveDevice ( 2 )->TurnCW ();
}

void genApplication::Action8 ()
{
	dynamic_cast< scbPultTablo* > ( this->GetScheme ( L"Пульт" ))->GetActiveDevice ( 2 )->TurnCCW ();
}

void genApplication::Action9 ()
{
	dynamic_cast< scbMotorDrive* > ( this->GetScheme ( L"Стрелка.2" ) )->GetDriveDevice ()->FlapDown ();
}

void genApplication::Action10 ()
{
	dynamic_cast< scbMotorDrive* > ( this->GetScheme ( L"Стрелка.2" ) )->GetDriveDevice ()->FlapUp ();
}

void genApplication::Action11 ()
{
	dynamic_cast< scbMotorDrive* > ( this->GetScheme ( L"Стрелка.2" ) )->GetDriveDevice ()->LeftWedgeInsert ();
}

void genApplication::Action12 ()
{
	dynamic_cast< scbMotorDrive* > ( this->GetScheme ( L"Стрелка.2" ) )->GetDriveDevice ()->LeftWedgeRemove ();
}

void genApplication::Action13 ()
{
	dynamic_cast< scbMotorDrive* > ( this->GetScheme ( L"Стрелка.2" ) )->GetDriveDevice ()->RightWedgeInsert ();
}

void genApplication::Action14 ()
{
	dynamic_cast< scbMotorDrive* > ( this->GetScheme ( L"Стрелка.2" ) )->GetDriveDevice ()->RightWedgeRemove ();
}

void genApplication::Action15 ()
{
}

void genApplication::Action16 ()
{
}

void genApplication::Action17 ()
{
}

LRESULT CALLBACK genApplication::WndProc ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	LRESULT result = 0;
	unsigned int scancode;
//	PAINTSTRUCT ps;
//	HDC hdc;
	if ( message == WM_CREATE )
	{
		result = 1;
	}
	else
	{
		genApplication* pApp = genApplication::m_Instance;
		bool wasHandled = false;
		if ( pApp != nullptr )
		{
			UINT width;
			UINT height;
			switch ( message )
			{
			case WM_COMMAND:
				switch ( LOWORD ( wParam ))
				{
				case IDM_EXIT:
					DestroyWindow ( hwnd );
					break;
				default:
					return DefWindowProc ( hwnd, message, wParam, lParam );
				}
				break;
			case WM_KEYDOWN:
				scancode = ( lParam >> 16 ) & 0xff;
				switch ( scancode )
				{
				case 2: // клавиша 1
					pApp->Action1 ();
					break;
				case 3: // клавиша 2
					pApp->Action3 ();
					break;
				case 4: // клавиша 3
					pApp->Action8 ();
					break;
				case 5: // клавиша 4
					pApp->Action5 ();
					break;
				case 6: // клавиша 5
					pApp->Action7 ();
					break;

				case 0x10: // клавиша Q
					pApp->Action9 ();
					break;
				case 0x11: // клавиша W
					pApp->Action10 ();
					break;
				case 0x12: // клавиша E
					pApp->Action11 ();
					break;
				case 0x13: // клавиша R
					pApp->Action12 ();
					break;
				case 0x14: // клавиша T
					pApp->Action13 ();
					break;
				case 0x15: // клавиша Y
					pApp->Action14 ();
					break;
				}
				break;
			case WM_KEYUP:
				scancode = ( lParam >> 16 ) & 0xff;
				switch ( scancode )
				{
				case 2: // клавиша 1
					pApp->Action2 ();
					break;
				case 3: // клавиша 2
					pApp->Action4 ();
					break;
				case 5: // клавиша 4
					pApp->Action6 ();
					break;
				}
				break;
			case WM_SIZE:
				width = LOWORD ( lParam );
				height = HIWORD ( lParam );
				pApp->OnResize ( width, height );
				result = 0;
				wasHandled = true;
				break;
//			case WM_PAINT:
//				hdc = BeginPaint ( genApplication::Instance ()->m_Hwnd, &ps );
//				EndPaint ( genApplication::Instance ()->m_Hwnd, &ps );
//				result = 0;
//				wasHandled = true;
//				break;
			case WM_DESTROY:
				PostQuitMessage ( 0 );
				result = 1;
				wasHandled = true;
				break;
			}
		}
		if ( !wasHandled )
			result = DefWindowProc ( hwnd, message, wParam, lParam );
	}
	return result;
}

void genApplication::OnResize ( UINT width, UINT height )
{
}
