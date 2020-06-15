#pragma once

#include <d3d11.h>
#include <vector>
#include "..\visual\visualAbstract.h"

using std::vector;

class graphPixelShader;
class graphVertexShader;
class graphVertexBuffer;
class graphVertexDeclaration;
class graphIndexBuffer;
class graphCamera;

class graphServer
{
public:
	enum TopologyType
	{
		No = 0,
		PointList,
		LineList,
		LineStrip,
		TriangleList,
		TriangleStrip,
	};

private:
	static graphServer* m_Instance;

	D3D_DRIVER_TYPE m_DriverType;
	D3D_FEATURE_LEVEL m_FeatureLevel;
	ID3D11Device* m_D3dDevice;
	ID3D11DeviceContext* m_ImmediateContext;
	IDXGISwapChain* m_SwapChain;
	ID3D11RenderTargetView* m_RenderTargetView;
	ID3D11Texture2D* m_DepthStencil;
	ID3D11DepthStencilView* m_DepthStencilView;

	vector<graphIndexBuffer*> m_IndexBuffers;
	vector<graphVertexBuffer*> m_VertexBuffers;
	vector<graphVertexShader*> m_VertexShaders;
	vector<graphVertexDeclaration*> m_VertexDeclarations;
	vector<graphPixelShader*> m_PixelShaders;
	vector<graphCamera*> m_Cameras;

	int m_CurrentCamera;

	XMVECTOR m_AmbientColor;
	XMVECTOR m_DirLightDirection;
	XMVECTOR m_DirLightColor;

	vector<visualAbstract*> m_VisualObjects;

	void CleanupDevice ();

public:
	graphServer ();
	~graphServer ();

	HRESULT InitDevice (); // Создание устройства D3D
	HRESULT Render ();

	HRESULT LoadVertexShader ( const wchar_t* filename, const char* mainFunc, const wchar_t* name, const wchar_t* vDecl );
	HRESULT LoadPixelShader ( const wchar_t* filename, const char* mainFunc, const wchar_t* name );

	int CreateVertexBuffer ( const wchar_t* vDecl, int vCount, TopologyType topology );
	void FillPositionInVertexBuffer ( int vb, int index, float x, float y, float z );
	void FillNormalInVertexBuffer ( int vb, int index, float x, float y, float z );
	void FillDiffuseColorInVertexBuffer ( int vb, int index, float r, float g, float b, float a );
	void FillSpecularColorInVertexBuffer ( int vb, int index, float r, float g, float b, float a );
	void FillEmissiveColorInVertexBuffer ( int vb, int index, float r, float g, float b, float a );
	int AssignVertexBuffer ( int index );

	int CreateIndexBuffer ( int num_indices, unsigned short* indices );

	graphVertexShader* GetVertexShader ( int index );
	int GetVertexShaderIndex ( const wchar_t* shader_name );

	graphPixelShader* GetPixelShader ( int index );
	int GetPixelShaderIndex ( const wchar_t* shader_name );

	HRESULT SetCamera ( int index );
	int AddCamera ();
	HRESULT DeleteCamera ( int index );
	graphCamera* GetCamera ( int index ) const;

	void SetAmbientColor ( float r, float g, float b );
	void SetLightColor ( float r, float g, float b );
	void SetLightDirection ( float x, float y, float z );

	void AddVisualObject ( visualAbstract* visualObject );
	void DeleteVisualObject ( visualAbstract* visualObject );

	void Draw ( int vs, int ps, int ib, int vb );

	ID3D11Device* GetDevice () const;

	static graphServer* Instance ();
};

inline graphServer* graphServer::Instance ()
{
	return graphServer::m_Instance;
}

inline ID3D11Device* graphServer::GetDevice () const
{
	return this->m_D3dDevice;
}

inline graphCamera* graphServer::GetCamera ( int index ) const
{
	return ( ( index < 0 ) || ( index >= static_cast<int>( this->m_Cameras.size () ) ) ) ? nullptr : this->m_Cameras.at ( index );
}

inline void graphServer::DeleteVisualObject ( visualAbstract* visualObject )
{
	for ( auto& ptr : this->m_VisualObjects )
		if ( ptr == visualObject )
		{
			ptr = nullptr;
			break;
		}
}
