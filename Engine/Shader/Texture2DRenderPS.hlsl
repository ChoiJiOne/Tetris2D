struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD0;
};

struct PS_OUTPUT
{
    float4 Color : SV_TARGET0;
};

Texture2D Texture : register(t0);
SamplerState LinearSampler : register(s0);

PS_OUTPUT main(PS_INPUT Input)
{
    PS_OUTPUT Output;
    
    Output.Color = Texture.Sample(LinearSampler, Input.UV);
    
    return Output;
}