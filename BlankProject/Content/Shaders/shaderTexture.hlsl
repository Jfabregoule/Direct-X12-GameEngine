Texture2D gTex : register(t0);
SamplerState gSampler : register(s0);


cbuffer ConstantBuffer : register(b0)
{
	matrix WorldViewProjection;
}

struct VertexInput
{
	float3 position : POSITION;
	float4 color : COLOR;
	float2 TexC : TEXCOORD;
};

struct VertexOutput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 TexC : TEXCOORD;
};

VertexOutput vs_main(VertexInput input)
{
	VertexOutput output;
    //output.position = mul(WorldViewProjection, float4(input.position, 1.0f));
    output.position = mul(float4(input.position, 1.0f), WorldViewProjection);
	output.color = input.color;
	output.TexC = input.TexC;
	return output;
}

float4 ps_main(VertexOutput input) : SV_TARGET
{
    //return float4(1, 0, 0, 1);
	return gTex.Sample(gSampler, input.TexC);
}