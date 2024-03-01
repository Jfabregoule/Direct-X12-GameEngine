cbuffer WorldBuffer : register(b0)
{
    float4x4 world; // Transformation matrix for object
};

cbuffer ViewBuffer : register(b1)
{
    float4x4 view; // View matrix
}

cbuffer ProjBuffer : register(b2)
{
    float4x4 projection; // Projection matrix
}

cbuffer ViewProjBuffer : register(b3)
{
    float4x4 worldViewProjMatrix; // Combined transformation matrix
}

Texture2D textureMap : register(t0);
SamplerState samplerState : register(s0);

struct VSInput
{
    float3 position : POSITION;
    float2 texCoord : TEXCOORD; // Texture coordinates
};

struct PSInput
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD; // Texture coordinates
};

PSInput vs_main(VSInput input)
{
    PSInput output;

    // Apply object transformations
    float4 worldPosition = mul(float4(input.position, 1.0f), world);
    float4 viewPosition = mul(worldPosition, view);
    float4 clipPosition = mul(viewPosition, projection);

    // Pass through transformed position
    output.position = clipPosition;

    // Pass through texture coordinates
    output.texCoord = input.texCoord;

    // Set color to white initially
    output.color = float3(1.0f, 1.0f, 1.0f);

    return output;
}

float4 ps_main(PSInput input) : SV_TARGET
{
    float4 finalColor;

    // Sample from texture using provided texture coordinates
    float4 texColor = textureMap.Sample(samplerState, input.texCoord);

    // Multiply texture color with interpolated color from vertex shader
    finalColor = float4(texColor.rgb * input.color, texColor.a);

    return finalColor;
}
