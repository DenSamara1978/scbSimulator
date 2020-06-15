cbuffer ConstantBuffer : register ( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
	float4 DiffuseColor;
	float4 SpecularColor;
	float4 EmissiveColor;
	float4 AmbientColor;
	float4 DirLightColor;
	float4 DirLightDirection;
}

struct VS_INPUT
{
	float4 Pos : POSITION;
	float3 Normal : NORMAL;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
};

VS_OUTPUT VS_main ( VS_INPUT input )
{
	VS_OUTPUT output = ( VS_OUTPUT ) 0;

	// √еометрические преобразовани€ координаты
	output.Pos = mul ( input.Pos, World ); // сначала в пространство мира
	output.Pos = mul ( output.Pos, View ); // затем в пространство вида
	output.Pos = mul ( output.Pos, Projection ); // в проекционное пространство

												 // ѕреобразовани€ цвета
	output.Normal = mul ( input.Normal, World );

	return output;
}

float4 PS_main ( VS_OUTPUT input ) : SV_TARGET
{
	float3 lightDir = normalize ( - DirLightDirection );

	float lightIntensity = saturate ( dot ( input.Normal, lightDir ) );
	float4 color = AmbientColor * DiffuseColor;
	color += ( DiffuseColor * max ( 0, lightIntensity ) );
	color = max ( saturate ( color ), EmissiveColor );
	color.a = 1.0f;

	return color;
}
