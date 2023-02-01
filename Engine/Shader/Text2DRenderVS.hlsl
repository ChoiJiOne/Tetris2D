cbuffer cbEveryFrame : register(b0)
{
    matrix Projection;
};

struct VS_INPUT
{
    float3 Position : POSITION;
    float2 UV : TEXCOORD0;
};

struct VS_OUTPUT
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD0;
};

VS_OUTPUT main(VS_INPUT Input)
{
    VS_OUTPUT Output;
    
    Output.Position = mul(float4(Input.Position, 1.0f), Projection);
    
    Output.UV = Input.UV;
    
    return Output;
}