struct VSInput
{
    float3 position : POSITION;
};

struct PSInput
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

PSInput vs_main(VSInput input)
{
    PSInput output;
    
    // Transformation de la position en coordonnées homogènes 4D
    output.position = float4(input.position, 1.0f);

    // Vous pouvez définir une couleur ici ou la transmettre à partir de VS à PS
    output.color = float3(1.0f, 0.0f, 0.0f); // Rouge

    return output;
}

float4 ps_main(PSInput input) : SV_TARGET
{
    // Utilisez la couleur interpolée provenant du vertex shader
    return float4(input.color, 1.0f); // Utilisation de la couleur interpolée pour le fragment
}
