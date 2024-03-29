cbuffer WorldViewProjBuffer : register(b0)
{
    float4x4 worldViewProjMatrix; // Combined transformation matrix
}

struct VSInput
{
    float3 position : POSITION;
    float4 color : COLOR; // Texture coordinates
};

struct PSInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PSInput vs_main(VSInput input)
{
    PSInput output;

    // Pass through transformed position
    //output.position = mul(worldViewProjMatrix, float4(input.position, 1.0f));
    output.position = mul(float4(input.position, 1.0f), worldViewProjMatrix);
    // Set color to white initially
    output.color = input.color;
    input.color.a = 1.0f;

    return output;
}

float4 ps_main(PSInput input) : SV_TARGET
{
    return input.color;
}