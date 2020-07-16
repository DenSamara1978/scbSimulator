#include "..\resource.h"
#include "Application.h"
#include "..\visual\PultTablo.h"
#include "..\visual\PultTabloButton.h"
#include "..\visual\PultTabloCommutator.h"
#include "..\visual\LightSignal.h"
#include "..\visual\MotorDrive.h"
#include "..\graphics\GraphicsServer.h"
#include "..\graphics\Camera.h"
#include "..\graphics\VertexShader.h"
#include "..\graphics\PixelShader.h"
#include "..\scb\LightSignalScheme.h"
#include "..\scb\MotorDriveScheme.h"
#include "..\scb\MotorDriveDevice.h"
#include "..\scb\PultTabloScheme.h"
#include "..\scb\PultTabloAbstractButton.h"
#include "..\scb\BusScheme.h"
#include "..\scb\ChainScheme.h"
#include "..\scb\SchemeGpr.h"
#include "..\scb\SchemeSse16.h"
#include "..\scb\SchemeSse32.h"
#include "..\scb\SchemeSse64.h"
#include "..\scb\SchemeSse128.h"
#include "..\scb\SchemeSse256.h"
#include "..\scb\SchemeAvx64.h"
#include "..\scb\SchemeAvx128.h"
#include "..\scb\SchemeAvx256.h"
#include "..\scb\SchemeOutput.h"
#include "..\scb\SchemeServer.h"
#include "..\track\Switch.h"

using namespace scb;
using namespace visual;
using namespace graphics;

using application::Application;

Application* Application::instance = nullptr;

Application::Application() :
	hwnd(0),
	hInstance(0),
	hAccelTable(0),
	mainWindowHeight(0),
	mainWindowWidth(0)
{
	Application::instance = this;
}

Application::~Application()
{
	Application::instance = nullptr;
}

void Application::runMessageLoop()
{
	MSG msg = {0};

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			this->timer.tick();
			if (GraphicsServer::getInstance()->render() != S_OK)
				break;
		}
	}
}

HRESULT Application::initializeWindow(HINSTANCE hInstance, int nCmdShow, const wchar_t* graphics)
{
	this->hInstance = hInstance;

	WNDCLASSEX wcex = {sizeof(WNDCLASSEX)};
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Application::wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = this->hInstance;
	wcex.hIcon = LoadIcon(this->hInstance, MAKEINTRESOURCE(IDI_SCBSIMULATOR));
	wcex.hIconSm = LoadIcon(this->hInstance, MAKEINTRESOURCE(IDI_SMALL));
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SCBSIMULATOR);
	wcex.hCursor = LoadCursor(0, IDI_APPLICATION);
	wcex.lpszClassName = L"scbSimulator";

	RegisterClassEx(&wcex);

	this->hwnd = CreateWindow(L"scbSimulator", L"Симулятор схем СЦБ",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		1500, 1000, 0, 0, this->hInstance, nullptr);

	if (!this->hwnd)
		return E_FAIL;

	ShowWindow(this->hwnd, SW_SHOWNORMAL);
	RECT rc;
	GetClientRect(this->hwnd, &rc);
	this->mainWindowWidth = rc.right - rc.left;
	this->mainWindowHeight = rc.bottom - rc.top;

	this->hAccelTable = LoadAccelerators(this->hInstance, MAKEINTRESOURCE(IDC_SCBSIMULATOR));

	SchemeServer* schemeServer = SchemeServer::getInstance();
	GraphicsServer* graphicsServer = GraphicsServer::getInstance();

	if (lstrcmp(graphics, L"Direct3D11") != 0)
		return E_FAIL;

	if (graphicsServer->initializeDevice() != S_OK)
		return E_FAIL;
	if (graphicsServer->loadVertexShader(L"Shaders.hlsl", "VS_main", L"vs", L"PN") != S_OK)
		return E_FAIL;
	if (graphicsServer->loadPixelShader(L"Shaders.hlsl", "PS_main", L"ps") != S_OK)
		return E_FAIL;

	Camera* camera = graphicsServer->getCamera(0);
	if (camera == nullptr)
		return E_FAIL;
	camera->setPosition(0.0f, 10.0f, -20.0f);
	camera->setLookPoint(0.0f, 4.0f, 0.0f);
	camera->setOrientation(0.0f, 1.0f, 0.0f);

	graphicsServer->setAmbientColor(0.3f, 0.3f, 0.3f);
	graphicsServer->setLightColor(0.8f, 0.8f, 0.8f);
	graphicsServer->setLightDirection(2.0f, -2.0f, 1.0f);

	VertexShader* vertexShader = graphicsServer->findVertexShader(L"vs");
	vertexShader->setConstantType(0, Shader::ConstantType::WorldMatrix);
	vertexShader->setConstantType(1, Shader::ConstantType::ViewMatrix);
	vertexShader->setConstantType(2, Shader::ConstantType::ProjectionMatrix);
	vertexShader->setConstantType(3, Shader::ConstantType::DiffuseColor);
	vertexShader->setConstantType(4, Shader::ConstantType::SpecularColor);
	vertexShader->setConstantType(5, Shader::ConstantType::EmissiveColor);
	vertexShader->setConstantType(6, Shader::ConstantType::AmbientColor);
	vertexShader->setConstantType(7, Shader::ConstantType::DirectionLightColor);
	vertexShader->setConstantType(8, Shader::ConstantType::DirectionLightDir);
	if (vertexShader->createConstantBuffer() != S_OK)
		return E_FAIL;

	PixelShader* pixelShader = graphicsServer->findPixelShader(L"ps");
	pixelShader->setConstantType(0, Shader::ConstantType::WorldMatrix);
	pixelShader->setConstantType(1, Shader::ConstantType::ViewMatrix);
	pixelShader->setConstantType(2, Shader::ConstantType::ProjectionMatrix);
	pixelShader->setConstantType(3, Shader::ConstantType::DiffuseColor);
	pixelShader->setConstantType(4, Shader::ConstantType::SpecularColor);
	pixelShader->setConstantType(5, Shader::ConstantType::EmissiveColor);
	pixelShader->setConstantType(6, Shader::ConstantType::AmbientColor);
	pixelShader->setConstantType(7, Shader::ConstantType::DirectionLightColor);
	pixelShader->setConstantType(8, Shader::ConstantType::DirectionLightDir);
	if (pixelShader->createConstantBuffer() != S_OK)
		return E_FAIL;

	if (!LightSignal::initializeBuffers())
		return E_FAIL;
	if (!PultTabloButton::initializeBuffers())
		return E_FAIL;
	if (!PultTabloCommutator::initializeBuffers())
		return E_FAIL;
	if (!PultTablo::initializeBuffers())
		return E_FAIL;
	if (!MotorDrive::initializeBuffers())
		return E_FAIL;

	vector<LightSignalScheme::LampPurpose> lamps = {LightSignalScheme::LampPurpose::FirstYellow,
													LightSignalScheme::LampPurpose::Blue,
													LightSignalScheme::LampPurpose::White,
													LightSignalScheme::LampPurpose::Green,
													LightSignalScheme::LampPurpose::Red,
													LightSignalScheme::LampPurpose::SecondYellow
	};
	LightSignalScheme* lightSignalScheme = schemeServer->addNewLightSignalScheme(L"Светофор.М2", lamps);
	if (lightSignalScheme == nullptr)
		return E_FAIL;

	visual::LightSignal* pVLS = new visual::LightSignal();
	graphicsServer->addVisualObject(pVLS);
	if (!pVLS->assignScbLightSignal(lightSignalScheme))
		return E_FAIL;

	lamps = {LightSignalScheme::LampPurpose::Green};
	lightSignalScheme = schemeServer->addNewLightSignalScheme(L"Светофор.М3", lamps);
	if (lightSignalScheme == nullptr)
		return E_FAIL;

	pVLS = new visual::LightSignal();
	graphicsServer->addVisualObject(pVLS);
	pVLS->setPosition(3.0f, 5.0f, 0.0f);
	if (!pVLS->assignScbLightSignal(lightSignalScheme))
		return E_FAIL;

	PultTabloScheme* pPT = schemeServer->addNewPultTablo(L"Пульт");
	pPT->setDeviceCount(1, 2, 3, 0, 1);
	pPT->setButtonKmd(0, Color::White, 0);
	pPT->setButtonKmd(1, Color::Green, 1, 2);
	pPT->setCommutatorKmtn(2, Color::Red, 3, 4, 5, 6, 7, 8);
	pPT->setOutput(0, L"Светофор.М2.Исполнение", 0);
	pPT->setOutput(1, L"Светофор.М3.Исполнение", 0);
	pPT->mapInputOutput(0, 0, 0);
	pPT->mapInputOutput(0, 1, 3);
	pPT->mapInputOutput(0, 2, 8);
	pPT->mapInputOutput(0, 3, 9);
	pPT->mapInputOutput(0, 4, 11);
	pPT->mapInputOutput(0, 5, 10);
	pPT->mapInputOutput(0, 6, 12);
	pPT->mapInputOutput(0, 7, 14);
	pPT->mapInputOutput(0, 8, 13);
	pPT->mapInputOutput(1, 0, 0);

	visual::PultTabloButton* pVButton = new visual::PultTabloButton();
	pVButton->setPosition(-5.0f, -3.0f, 0.0f);
	graphicsServer->addVisualObject(pVButton);
	if (!pVButton->assignButton(pPT, 0))
		return E_FAIL;

	pVButton = new visual::PultTabloButton();
	pVButton->setPosition(-7.0f, -3.0f, 0.0f);
	graphicsServer->addVisualObject(pVButton);
	if (!pVButton->assignButton(pPT, 1))
		return E_FAIL;

	visual::PultTabloCommutator* pVComm = new visual::PultTabloCommutator();
	pVComm->setPosition(-9.0f, -3.0f, 0.0f);
	graphicsServer->addVisualObject(pVComm);
	if (!pVComm->assignCommutator(pPT, 2))
		return E_FAIL;

	visual::PultTablo* pVPT = new visual::PultTablo();
	pVPT->setPosition(-10.0f, 6.0f, 4.0f);
	graphicsServer->addVisualObject(pVPT);
	if (!pVPT->assignPultTablo(pPT))
		return E_FAIL;

	pVPT->addCellLamp(0, 0, -2.25f, 2.0f, 0, Color::Yellow);
	pVPT->addCellLamp(0, 1, -0.75f, 2.0f, 0, Color::Green);
	pVPT->addCellLamp(0, 2, 0.75f, 2.0f, 0, Color::Red);
	pVPT->addCellLamp(0, 3, 2.25f, 2.0f, 0, Color::White);
	pVPT->addRoundLamp(0, 4, -1.5f, 4.0f, Color::Green);
	pVPT->addRoundLamp(0, 5, 1.5f, 4.0f, Color::Blue);
	pVPT->addCellLamp(0, 6, -2.25f, 0.0f, 0, Color::White);
	pVPT->addCellLamp(0, 7, -0.75f, 0.0f, 0, Color::Green);
	pVPT->addCellLamp(0, 8, 0.75f, 0.0f, 0, Color::Green);
	pVPT->addCellLamp(0, 9, 2.25f, 0.0f, 0, Color::White);
	pVPT->addCellLamp(0, 10, -2.25f, -2.0f, 0, Color::Yellow);
	pVPT->addCellLamp(0, 11, -0.75f, -2.0f, 0, Color::Yellow);
	pVPT->addCellLamp(0, 12, 0.75f, -2.0f, 0, Color::Yellow);
	pVPT->addCellLamp(0, 13, 2.25f, -2.0f, 0, Color::Yellow);
	pVPT->addRoundLamp(0, 14, -1.5f, -4.0f, Color::Green);
	pVPT->addRoundLamp(0, 15, 0.0f, -4.0f, Color::Yellow);
	pVPT->addRoundLamp(0, 16, 1.5f, -4.0f, Color::White);

	track::Switch* sw = new track::Switch;

	MotorDriveScheme* motorDriveScheme = schemeServer->addNewMotorDriveScheme(L"Стрелка.2");
	motorDriveScheme->getDriveDevice()->setSwitch(sw);
	motorDriveScheme->setDeviceCount(1);
	motorDriveScheme->setOutput(0, L"Светофор.М2.Исполнение");

	motorDriveScheme->mapInputOutput(0, 0, 15);
	motorDriveScheme->mapInputOutput(0, 1, 16);
	motorDriveScheme->mapInputOutput(0, 2, 17);
	motorDriveScheme->mapInputOutput(0, 3, 18);
	motorDriveScheme->mapInputOutput(0, 4, 19);
	motorDriveScheme->mapInputOutput(0, 5, 20);
	motorDriveScheme->mapInputOutput(0, 6, 21);
	motorDriveScheme->mapInputOutput(0, 7, 22);
	motorDriveScheme->mapInputOutput(0, 8, 23);
	motorDriveScheme->mapInputOutput(0, 9, 24);
	motorDriveScheme->mapInputOutput(0, 10, 25);

	visual::MotorDrive* pVMD = new visual::MotorDrive();
	pVMD->setPosition(8.0f, 4.0f, 3.0f);
	graphicsServer->addVisualObject(pVMD);
	if (!pVMD->assignScbMotorDrive(motorDriveScheme))
		return E_FAIL;

	Scheme* pScheme = schemeServer->addNewScheme(L"Светофор.М2.Исполнение", 0, 27, 0, 0);
	pScheme->setDeviceCount(7);

	pScheme->setNeutralRelay(0, 1, 2);
	pScheme->addRelayTimeSample(0, 0, 1, 100, 50);
	pScheme->addRelayTimeSample(0, 1, 0, 200, 150);
	pScheme->addRelayConvertation(0, 0, 0);

	pScheme->setNeutralRelay(1, 4, 5);
	pScheme->addRelayTimeSample(1, 0, 1, 100, 50);
	pScheme->addRelayTimeSample(1, 1, 0, 200, 150);
	pScheme->addRelayConvertation(1, 5, 0);

	pScheme->setNeutralRelay(2, 6, 7);
	pScheme->addRelayTimeSample(2, 0, 1, 100, 50);
	pScheme->addRelayTimeSample(2, 1, 0, 200, 150);
	pScheme->addRelayConvertation(2, 12, 0);

	pScheme->setOutput(3, L"Светофор.М2");
	pScheme->setOutput(4, L"Пульт", 0);
	pScheme->setOutput(5, L"Стрелка.2");
	pScheme->setOutput(6, L"Шина");

	pScheme->mapInputOutput(3, 1, 6);
	//	pScheme->mapInputOutput ( 3, 2, 3 );
	pScheme->mapInputOutput(3, 3, 10);
	//	pScheme->mapInputOutput ( 3, 4, 5 );
	pScheme->mapInputOutput(3, 6, 2);
	//	pScheme->mapInputOutput ( 3, 7, 1 );
	pScheme->mapInputOutput(3, 8, 30);
	//	pScheme->mapInputOutput ( 3, 9, 15 );
	pScheme->mapInputOutput(3, 10, 18);
	//	pScheme->mapInputOutput ( 3, 11, 9 );
	pScheme->mapInputOutput(3, 13, 22);
	//	pScheme->mapInputOutput ( 3, 14, 11 );

	pScheme->mapInputOutput(4, 15, 0);
	pScheme->mapInputOutput(4, 16, 1);
	pScheme->mapInputOutput(4, 17, 2);
	pScheme->mapInputOutput(4, 18, 3);
	pScheme->mapInputOutput(4, 19, 4);
	pScheme->mapInputOutput(4, 20, 5);
	pScheme->mapInputOutput(4, 21, 6);
	pScheme->mapInputOutput(4, 22, 7);
	pScheme->mapInputOutput(4, 23, 8);
	pScheme->mapInputOutput(4, 24, 9);
	pScheme->mapInputOutput(4, 25, 10);
	pScheme->mapInputOutput(4, 26, 11);
	pScheme->mapInputOutput(4, 27, 12);
	pScheme->mapInputOutput(4, 28, 13);
	pScheme->mapInputOutput(4, 29, 14);
	pScheme->mapInputOutput(4, 30, 15);
	pScheme->mapInputOutput(4, 31, 16);

	pScheme->mapInputOutput(5, 15, 0);
	pScheme->mapInputOutput(5, 18, 1);

	pScheme->mapInputOutput(6, 21, 0);
	pScheme->mapInputOutput(6, 24, 35);

	OutputStream mask, result;

	// Б = (Кнопка_белого)
	mask = {1, 0, 0, 0, 0, 0, 0, 0};
	result = {1, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(0, mask, result);

	// {Синий} = !Б
	mask = {4, 0, 0, 0, 0, 0, 0, 0};
	result = {6, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(1, mask, result);

	// {Белый} = Б
	mask = {2, 0, 0, 0, 0, 0, 0, 0};
	result = {0x18, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(2, mask, result);

	// З = (Кнопка_зеленого)
	mask = {8, 0, 0, 0, 0, 0, 0, 0};
	result = {0x20, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(3, mask, result);

	// {Красный} = !З
	mask = {0x20, 0, 0, 0, 0, 0, 0, 0};
	result = {0xC0, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(4, mask, result);

	// {Зеленый} = З
	mask = {0x10, 0, 0, 0, 0, 0, 0, 0};
	result = {0x300, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(5, mask, result);

	// {Первый_желтый} = З & Б
	mask = {0x12, 0, 0, 0, 0, 0, 0, 0};
	result = {0xC00, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(6, mask, result);

	// 2Ж = (Кнопка_белого)
	mask = {1, 0, 0, 0, 0, 0, 0, 0};
	result = {0x1000, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(7, mask, result);

	// 2Ж = 2Ж & !(Кнопка_зеленого)
	mask = {0x140, 0, 0, 0, 0, 0, 0, 0};
	result = {0x1000, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(8, mask, result);

	// {Второй_желтый} = 2Ж
	mask = {0x40, 0, 0, 0, 0, 0, 0, 0};
	result = {0x6000, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(9, mask, result);

	// Коммутатор - левый фронт
	mask = {1 << 9, 0, 0, 0, 0, 0, 0, 0};
	result = {1 << 15, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(10, mask, result);

	// Коммутатор - левый тыл
	mask = {1 << 11, 0, 0, 0, 0, 0, 0, 0};
	result = {1 << 16, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(11, mask, result);

	// Коммутатор - правый фронт
	mask = {1 << 10, 0, 0, 0, 0, 0, 0, 0};
	result = {1 << 18, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(12, mask, result);

	// Коммутатор - правый тыл
	mask = {1 << 12, 0, 0, 0, 0, 0, 0, 0};
	result = {1 << 17, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(13, mask, result);

	// Коммутатор - отжат
	mask = {1 << 13, 0, 0, 0, 0, 0, 0, 0};
	result = {1 << 19, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(14, mask, result);

	// Коммутатор - нажат
	mask = {1 << 14, 0, 0, 0, 0, 0, 0, 0};
	result = {1 << 20, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(15, mask, result);

	// Привод - автопереключатель 1
	mask = {1 << 16, 0, 0, 0, 0, 0, 0, 0};
	result = {1 << 21, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(16, mask, result);

	// Привод - автопереключатель 2
	mask = {1 << 15, 0, 0, 0, 0, 0, 0, 0};
	result = {1 << 22, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(17, mask, result);

	// Привод - автопереключатель 3
	mask = {1 << 17, 0, 0, 0, 0, 0, 0, 0};
	result = {1 << 23, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(18, mask, result);

	// Привод - автопереключатель 4
	mask = {1 << 18, 0, 0, 0, 0, 0, 0, 0};
	result = {1 << 24, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(19, mask, result);

	// Привод - автопереключатель 1 без инея
	mask = {1 << 21, 0, 0, 0, 0, 0, 0, 0};
	result = {1 << 25, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(20, mask, result);

	// Привод - автопереключатель 2 без инея
	mask = {1 << 22, 0, 0, 0, 0, 0, 0, 0};
	result = {1 << 26, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(21, mask, result);

	// Привод - автопереключатель 3 без инея
	mask = {1 << 23, 0, 0, 0, 0, 0, 0, 0};
	result = {1 << 27, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(22, mask, result);

	// Привод - автопереключатель 4 без инея
	mask = {1 << 24, 0, 0, 0, 0, 0, 0, 0};
	result = {1 << 28, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(23, mask, result);

	// Привод - ток
	mask = {1 << 19, 0, 0, 0, 0, 0, 0, 0};
	result = {1 << 29, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(24, mask, result);

	// Привод - ток фрикции
	mask = {1 << 20, 0, 0, 0, 0, 0, 0, 0};
	result = {1 << 30, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(25, mask, result);

	// Привод - блокировочный контакт
	mask = {1 << 25, 0, 0, 0, 0, 0, 0, 0};
	result = {0x80000000, 0, 0, 0, 0, 0, 0, 0};
	pScheme->setMainCircuit(26, mask, result);

	ChainScheme* pChain = schemeServer->addNewChainScheme(L"Шина", 2);
	pChain->setDeviceCount(1);
	pChain->setOutput(0, L"Светофор.М2", -1);
	pChain->mapInputOutput(0, 0, 16);
	//	pBus->mapInputOutput ( 0, 0, 17 );

	// Тестовая схема для проверки работоспособности любого типа схем
	const int stride = 128;
	pScheme = schemeServer->addNewScheme(L"Светофор.М3.Исполнение", 0, stride, 0, 0);
	pScheme->setDeviceCount(stride);

	for (int i = 0; i < stride - 1; ++i)
	{
		pScheme->setNeutralRelay(i, i + 1);
		pScheme->addRelayTimeSample(i, 0, 1, 20, 10);
		pScheme->addRelayTimeSample(i, 1, 0, 20, 10);
		pScheme->addRelayConvertation(i, i + 1, 0);

		mask = {0, 0, 0, 0, 0, 0, 0, 0};
		result = {0, 0, 0, 0, 0, 0, 0, 0};
		mask.mask[(i & 0xE0) >> 5] = 1L << (i & 0x1F);
		result.mask[((i + 1) & 0xE0) >> 5] = 1L << ((i + 1) & 0x1F);
		pScheme->setMainCircuit(i, mask, result);
	}
	mask = {0, 0, 0, 0, 0, 0, 0, 0};
	result = {1, 0, 0, 0, 0, 0, 0, 0};
	mask.mask[((stride - 1) & 0xE0) >> 5] = 1L << ((stride - 1) & 0x1F);
	pScheme->setMainCircuit(stride - 1, mask, result);

	pScheme->setOutput(stride - 1, L"Светофор.М3");
	pScheme->mapInputOutput(stride - 1, stride - 1, 30);

	schemeServer->initialize();

	return S_OK;
}

void Application::action1()
{
	SchemeServer::getInstance()->findPultTabloSchemeByName(L"Пульт")->getActiveDevice(0)->press();
}

void Application::action2()
{
	SchemeServer::getInstance()->findPultTabloSchemeByName(L"Пульт")->getActiveDevice(0)->release();
}

void Application::action3()
{
	SchemeServer::getInstance()->findPultTabloSchemeByName(L"Пульт")->getActiveDevice(1)->press();
}

void Application::action4()
{
	SchemeServer::getInstance()->findPultTabloSchemeByName(L"Пульт")->getActiveDevice(1)->release();
}

void Application::action5()
{
	SchemeServer::getInstance()->findPultTabloSchemeByName(L"Пульт")->getActiveDevice(2)->press();
}

void Application::action6()
{
	SchemeServer::getInstance()->findPultTabloSchemeByName(L"Пульт")->getActiveDevice(2)->release();
}

void Application::action7()
{
	SchemeServer::getInstance()->findPultTabloSchemeByName(L"Пульт")->getActiveDevice(2)->turnCw();
}

void Application::action8()
{
	SchemeServer::getInstance()->findPultTabloSchemeByName(L"Пульт")->getActiveDevice(2)->turnCcw();
}

void Application::action9()
{
	SchemeServer::getInstance()->findMotorDriveSchemeByName(L"Стрелка.2")->getDriveDevice()->flapDown();
}

void Application::action10()
{
	SchemeServer::getInstance()->findMotorDriveSchemeByName(L"Стрелка.2")->getDriveDevice()->flapUp();
}

void Application::action11()
{
	SchemeServer::getInstance()->findMotorDriveSchemeByName(L"Стрелка.2")->getDriveDevice()->leftWedgeInsert();
}

void Application::action12()
{
	SchemeServer::getInstance()->findMotorDriveSchemeByName(L"Стрелка.2")->getDriveDevice()->leftWedgeRemove();
}

void Application::action13()
{
	SchemeServer::getInstance()->findMotorDriveSchemeByName(L"Стрелка.2")->getDriveDevice()->rightWedgeInsert();
}

void Application::action14()
{
	SchemeServer::getInstance()->findMotorDriveSchemeByName(L"Стрелка.2")->getDriveDevice()->rightWedgeRemove();
}

void Application::action15()
{
}

void Application::action16()
{
}

void Application::action17()
{
}

LRESULT CALLBACK Application::wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	unsigned int scanCode;
	//	PAINTSTRUCT ps;
	//	HDC hdc;
	if (message == WM_CREATE)
		result = 1;
	else
	{
		Application* application = Application::getInstance();
		bool wasHandled = false;
		if (application != nullptr)
		{
			UINT width;
			UINT height;
			switch (message)
			{
				case WM_COMMAND:
					switch (LOWORD(wParam))
					{
						case IDM_EXIT:
							DestroyWindow(hwnd);
							break;
						default:
							return DefWindowProc(hwnd, message, wParam, lParam);
					}
					break;
				case WM_KEYDOWN:
					scanCode = (lParam >> 16) & 0xff;
					switch (scanCode)
					{
						case 2: // клавиша 1
							application->action1();
							break;
						case 3: // клавиша 2
							application->action3();
							break;
						case 4: // клавиша 3
							application->action8();
							break;
						case 5: // клавиша 4
							application->action5();
							break;
						case 6: // клавиша 5
							application->action7();
							break;

						case 0x11: // клавиша W
							GraphicsServer::getInstance()->getCamera()->moveForward(0.1f);
							break;
						case 0x1F: // клавиша S
							GraphicsServer::getInstance()->getCamera()->moveBackward(0.1f);
							break;
						case 0x1E: // клавиша A
							GraphicsServer::getInstance()->getCamera()->moveLeft(0.1f);
							break;
						case 0x20: // клавиша D
							GraphicsServer::getInstance()->getCamera()->moveRight(0.1f);
							break;
						case 0x48: // клавиша Up
							GraphicsServer::getInstance()->getCamera()->turnUp(10.0f);
							break;
						case 0x50: // клавиша Down
							GraphicsServer::getInstance()->getCamera()->turnDown(10.0f);
							break;
						case 0x4B: // клавиша Left
							GraphicsServer::getInstance()->getCamera()->turnLeft(10.0f);
							break;
						case 0x4D: // клавиша Right
							GraphicsServer::getInstance()->getCamera()->turnRight(10.0f);
							break;

						case 0x3B: // клавиша F1
							application->action9();
							break;
						case 0x3C: // клавиша F2
							application->action10();
							break;
						case 0x3D: // клавиша F3
							application->action11();
							break;
						case 0x3E: // клавиша F4
							application->action12();
							break;
						case 0x3F: // клавиша F5
							application->action13();
							break;
						case 0x40: // клавиша F6
							application->action14();
							break;
					}
					break;
				case WM_KEYUP:
					scanCode = (lParam >> 16) & 0xff;
					switch (scanCode)
					{
						case 2: // клавиша 1
							application->action2();
							break;
						case 3: // клавиша 2
							application->action4();
							break;
						case 5: // клавиша 4
							application->action6();
							break;
					}
					break;
				case WM_SIZE:
					width = LOWORD(lParam);
					height = HIWORD(lParam);
					application->onResize(width, height);
					result = 0;
					wasHandled = true;
					break;
				case WM_DESTROY:
					PostQuitMessage(0);
					result = 1;
					wasHandled = true;
					break;
			}
		}
		if (!wasHandled)
			result = DefWindowProc(hwnd, message, wParam, lParam);
	}
	return result;
}

void Application::onResize(UINT width, UINT height)
{
	this->mainWindowWidth = width;
	this->mainWindowHeight = height;
}
