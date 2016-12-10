//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// ShaderNormal
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string ShaderNormal_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.x";

float4x4 matViewProjection : ViewProjection;    // ð\ 
float4x4 matWorld;

struct VS_INPUT 
{
   float4 mPosition : POSITION0;
   float2 mUV       : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 mPosition    : POSITION0;
   float2 mUV          : TEXCOORD0;
};

VS_OUTPUT ShaderNormal_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output = (VS_OUTPUT)0;
   Output.mPosition = mul(Input.mPosition, matWorld);
   Output.mPosition = mul(Output.mPosition, matViewProjection);
   Output.mUV = Input.mUV;
   
   return( Output ); 
}




struct PS_INPUT
{
   float2 mUV       : TEXCOORD0;
};

texture DiffuseMap_Tex
<
   string ResourceName = "..\\Objects\\Surface\\Map1.jpg";
>;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
};

float4 ShaderNormal_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR0
{
   float4 albedo = tex2D(DiffuseSampler, Input.mUV);
   
   return( albedo );
}




//--------------------------------------------------------------//
// Technique Section for ShaderNormal
//--------------------------------------------------------------//
technique ShaderNormal
{
   pass Pass_0
   {
      VertexShader = compile vs_3_0 ShaderNormal_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_3_0 ShaderNormal_Pass_0_Pixel_Shader_ps_main();
   }

}

