struct VSInput
{
    float3 position : POSITION;
};

struct PSInput
{
    float4 position : SV_POSITION;
};

PSInput vs_main(VSInput input)
{
    PSInput output;
    output.position = float4(input.position, 1.0f);
    return output;
}

float4 ps_main(PSInput input) : SV_TARGET
{
    return float4(0.0f, 0.0f, 0.0f, 1.0f); // Noir (RGB: 0,0,0)
}
