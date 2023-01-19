cbuffer cbEveryFrame : register(b0)
{
    matrix World;
    matrix View;
    matrix Project;
};

struct VS_INPUT
{
    float3 Position : POSITION;
    float4 Color : COLOR;
};

struct VS_OUTPUT
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

VS_OUTPUT main(VS_INPUT Input)
{
    VS_OUTPUT Output;
    
    Output.Position = mul(float4(Input.Position, 1.0f), World);
    Output.Position = mul(Output.Position, View);
    Output.Position = mul(Output.Position, Project);
    
    Output.Color = Input.Color;
    
    return Output;
}