struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

struct PS_OUTPUT
{
    float4 Color : SV_TARGET0;
};

PS_OUTPUT main(PS_INPUT Input)
{
    PS_OUTPUT Output;
    
    Output.Color = Input.Color;
    
    return Output;
}