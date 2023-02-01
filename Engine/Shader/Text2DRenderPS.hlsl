struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD0;
};

struct PS_OUTPUT
{
    float4 Color : SV_TARGET0;
};

cbuffer TextColorConstantBuffer : register(b0)
{
    float4 TextColor;
};

Texture2D<float> Texture : register(t0);
SamplerState LinearSampler : register(s0);

PS_OUTPUT main(PS_INPUT Input)
{
    PS_OUTPUT Output;
    
    float TextAlpha = Texture.Sample(LinearSampler, Input.UV);
    
    Output.Color = float4(TextColor.r, TextColor.g, TextColor.b, TextAlpha);
    
    return Output;
}