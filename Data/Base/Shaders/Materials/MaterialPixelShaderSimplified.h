#pragma once

#if RENDER_PASS != RENDER_PASS_FORWARD
  #error "MaterialPixelShaderSimplified supports only the forward render pass"
#endif

#if BLEND_MODE == BLEND_MODE_MASKED && RENDER_PASS != RENDER_PASS_WIREFRAME

  #if defined(MSAA)
    #if MSAA == TRUE
      #define USE_ALPHA_TEST_SUPER_SAMPLING
    #endif
  #endif

#endif

//include <Shaders/Common/Lighting.h>
#include <Shaders/Materials/MaterialHelper.h>


struct PS_OUT
{
  float4 Color : SV_Target;
  
  #if defined(USE_ALPHA_TEST_SUPER_SAMPLING)
    uint Coverage : SV_Coverage;
  #endif
};

PS_OUT main(PS_IN Input)
{
#if CAMERA_MODE == CAMERA_MODE_STEREO
  s_ActiveCameraEyeIndex = Input.RenderTargetArrayIndex;
#endif

  G.Input = Input;

  PS_OUT Output;

  #if BLEND_MODE == BLEND_MODE_MASKED
    uint coverage = CalculateCoverage();
    if (coverage == 0)
    {
      discard;
    }
    #if defined(USE_ALPHA_TEST_SUPER_SAMPLING)
      Output.Coverage = coverage;
    #endif
  #endif

  ezMaterialData matData = FillMaterialData();

  Output.Color = float4(matData.diffuseColor, 1.0f);

  return Output;

  // TODO
/*

  float opacity = 1.0f;

  #if BLEND_MODE == BLEND_MODE_MASKED

    #if defined(USE_ALPHA_TEST)
      uint coverage = CalculateCoverage(Input);
      if (coverage == 0)
      {
        discard;
      }
    #endif

  #elif BLEND_MODE != BLEND_MODE_OPAQUE
    opacity = GetOpacity(Input);
  #endif

  ezMaterialData matData = FillMaterialData();

  #if defined(USE_DECALS)
    ApplyDecals(matData, clusterData);
  #endif

  #if RENDER_PASS == RENDER_PASS_EDITOR
    if (RenderPass == EDITOR_RENDER_PASS_LIT_ONLY)
    {
      matData.diffuseColor = 0.5;
      matData.specularColor = 0.0;
    }
  #endif

  #if defined(SHADING_MODE) && SHADING_MODE == SHADING_MODE_LIT
    float3 litColor = CalculateLighting(matData, clusterData, Input.Position.xyw);  // TODO
  #else
    float3 litColor = matData.diffuseColor;
  #endif

  litColor += matData.emissiveColor;

  Output.Color = float4(litColor, opacity);

  return Output;
*/
}
