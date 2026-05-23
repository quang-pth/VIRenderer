#include "BasicShaderHeader.hlsli"

cbuffer MeshData : register(b0) 
{
	float4 color;
}

float4 BasicPS(Output input ) : SV_TARGET {
	// return float4(input.uv, 1, 1);
	// return float4(tex.Sample(smp, input.uv));
	// return float4(pow(tex.Sample(smp, input.uv).rgb, 1.0f / 2.0f), 1.0f);
	return color;
	// return greenColor;
	// float4 outColor = float4(1.0, 0.3, 0.1, 1.0); 
	// return float4(pow(outColor.rgb, 1.0f / 2.0f), 1.0f);
	// return outColor;
}