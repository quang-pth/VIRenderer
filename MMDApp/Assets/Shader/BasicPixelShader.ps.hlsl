#include "BasicShaderHeader.hlsli"

cbuffer MeshData : register(b0) 
{
	float4 color;
}

float4 MainPS(Output input) : SV_TARGET {
	return color;
}