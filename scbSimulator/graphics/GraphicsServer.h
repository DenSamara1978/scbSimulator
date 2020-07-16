#pragma once

#include <d3d11.h>
#include <vector>
#include "..\visual\VisualAbstract.h"

using std::vector;

using visual::VisualAbstract;

namespace graphics
{
	class IndexBuffer;
	class Camera;
	class PixelShader;
	class VertexShader;
	class VertexBuffer;
	class VertexDeclaration;

	class GraphicsServer
	{
	public:
		enum class TopologyType
		{
			No = 0,
			PointList,
			LineList,
			LineStrip,
			TriangleList,
			TriangleStrip,
		};

		~GraphicsServer();

		static GraphicsServer* getInstance();

		HRESULT initializeDevice(); // Создание устройства D3D
		HRESULT render();

		HRESULT loadVertexShader(const wchar_t* fileName, const char* mainFunc, const wchar_t* shaderName, const wchar_t* vertexDeclarationName);
		HRESULT loadPixelShader(const wchar_t* fileName, const char* mainFunc, const wchar_t* shaderName);

		int createVertexBuffer(const wchar_t* vertexDeclarationName, int nVertex, TopologyType topology);
		void fillPositionInVertexBuffer(int vertexBuffer, int index, float x, float y, float z);
		void fillNormalInVertexBuffer(int vertexBuffer, int index, float x, float y, float z);
		void fillDiffuseColorInVertexBuffer(int vertexBuffer, int index, float red, float green, float blue, float alpha);
		void fillSpecularColorInVertexBuffer(int vertexBuffer, int index, float red, float green, float blue, float alpha);
		void fillEmissiveColorInVertexBuffer(int vertexBuffer, int index, float red, float green, float blue, float alpha);
		int assignVertexBuffer(int index);

		int createIndexBuffer(int nIndices, unsigned short* indices);

		VertexShader* getVertexShader(int index);
		VertexShader* findVertexShader (const wchar_t* shaderName);
		int getVertexShaderIndexByName(const wchar_t* shaderName);

		PixelShader* getPixelShader(int index);
		PixelShader* findPixelShader (const wchar_t* shaderName);
		int getPixelShaderIndexByName(const wchar_t* shaderName);

		HRESULT setCamera(int index);
		int addCamera();
		HRESULT deleteCamera(int index);
		Camera* getCamera() const;
		Camera* getCamera(int index) const;

		void setAmbientColor(float red, float green, float blue);
		void setLightColor(float red, float green, float blue);
		void setLightDirection(float x, float y, float z);

		void addVisualObject(VisualAbstract* visualObject);
		void deleteVisualObject(VisualAbstract* visualObject);

		void draw(int vertexShader, int pixelShader, int indexBuffer, int vertexBuffer);

		ID3D11Device* getD3dDevice() const;

	private:
		GraphicsServer();

		void cleanupDevice();

		static GraphicsServer* instance;

		D3D_DRIVER_TYPE driverType;
		D3D_FEATURE_LEVEL featureLevel;
		ID3D11Device* d3dDevice;
		ID3D11DeviceContext* immediateContext;
		IDXGISwapChain* swapChain;
		ID3D11RenderTargetView* renderTargetView;
		ID3D11Texture2D* depthStencil;
		ID3D11DepthStencilView* depthStencilView;

		vector<IndexBuffer*> indexBuffers;
		vector<VertexBuffer*> vertexBuffers;
		vector<VertexShader*> vertexShaders;
		vector<VertexDeclaration*> vertexDeclarations;
		vector<PixelShader*> pixelShaders;
		vector<Camera*> cameras;

		int currentCamera;

		XMVECTOR ambientColor;
		XMVECTOR dirLightDirection;
		XMVECTOR dirLightColor;

		vector<VisualAbstract*> visualObjects;
	};

	inline GraphicsServer* GraphicsServer::getInstance()
	{
		if (GraphicsServer::instance == nullptr)
			GraphicsServer::instance = new GraphicsServer;
		return GraphicsServer::instance;
	}

	inline ID3D11Device* GraphicsServer::getD3dDevice() const
	{
		return this->d3dDevice;
	}

	inline Camera* GraphicsServer::getCamera (int index) const
	{
		bool inRange = (index >= 0) and (index < static_cast<int>(this->cameras.size ()));
		return inRange ? this->cameras.at(index) : nullptr;
	}

	inline Camera* GraphicsServer::getCamera() const
	{
		return this->cameras[this->currentCamera];
	}

	inline void GraphicsServer::deleteVisualObject(VisualAbstract* visualObject)
	{
		for (auto& ptr : this->visualObjects)
		{
			if (ptr == visualObject)
			{
				ptr = nullptr;
				break;
			}
		}
	}
}