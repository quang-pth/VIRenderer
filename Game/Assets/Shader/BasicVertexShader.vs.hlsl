struct Output {
	float4 pos : POSITION;
	float4 svpos : SV_POSITION;
};

Output BasicVS(float4 pos : POSITION) {
	Output output;
	output.pos = pos; // Remain in clip space (-1 to 1) for the pixel shader to use
	output.svpos = pos; // Pass through the position to SV_POSITION for rasterization
	return output;
}