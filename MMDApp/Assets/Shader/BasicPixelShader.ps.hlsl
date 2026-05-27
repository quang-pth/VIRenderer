#include "BasicShaderHeader.hlsli"

cbuffer MeshData : register(b0) 
{
	float3 meshColor;
}

cbuffer Light : register(b1)
{
    float3 lightColor;
}

float4 MainPS(Output input) : SV_TARGET {
	// return float4(1.0f, 0.0f, 0.0f, 1.0f);
	return float4(meshColor * lightColor, 1.0f);
}