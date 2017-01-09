#include <RendererCore/PCH.h>
#include <RendererCore/Shader/ShaderPermutationResource.h>
#include <RendererCore/ShaderCompiler/ShaderManager.h>
#include <RendererCore/ShaderCompiler/ShaderCompiler.h>


EZ_BEGIN_DYNAMIC_REFLECTED_TYPE(ezShaderPermutationResource, 1, ezRTTIDefaultAllocator<ezShaderPermutationResource>);
EZ_END_DYNAMIC_REFLECTED_TYPE

static ezShaderPermutationResourceLoader g_PermutationResourceLoader;

ezShaderPermutationResource::ezShaderPermutationResource() : ezResource<ezShaderPermutationResource, ezShaderPermutationResourceDescriptor>(DoUpdate::OnAnyThread, 1)
{
  m_bShaderPermutationValid = false;

  for (ezUInt32 stage = 0; stage < ezGALShaderStage::ENUM_COUNT; ++stage)
  {
    m_pShaderStageBinaries[stage] = nullptr;
  }
}

ezResourceLoadDesc ezShaderPermutationResource::UnloadData(Unload WhatToUnload)
{
  m_bShaderPermutationValid = false;

  auto pDevice = ezGALDevice::GetDefaultDevice();

  if (!m_hShader.IsInvalidated())
  {
    pDevice->DestroyShader(m_hShader);
    m_hShader.Invalidate();
  }

  if (!m_hBlendState.IsInvalidated())
  {
    pDevice->DestroyBlendState(m_hBlendState);
    m_hBlendState.Invalidate();
  }

  if (!m_hDepthStencilState.IsInvalidated())
  {
    pDevice->DestroyDepthStencilState(m_hDepthStencilState);
    m_hDepthStencilState.Invalidate();
  }

  if (!m_hRasterizerState.IsInvalidated())
  {
    pDevice->DestroyRasterizerState(m_hRasterizerState);
    m_hRasterizerState.Invalidate();
  }


  ezResourceLoadDesc res;
  res.m_State = ezResourceState::Unloaded;
  res.m_uiQualityLevelsDiscardable = 0;
  res.m_uiQualityLevelsLoadable = 0;

  return res;
}

ezResourceLoadDesc ezShaderPermutationResource::UpdateContent(ezStreamReader* Stream)
{
  ezUInt32 uiGPUMem = 0;
  ModifyMemoryUsage().m_uiMemoryGPU = 0;

  m_bShaderPermutationValid = false;

  ezResourceLoadDesc res;
  res.m_State = ezResourceState::Loaded;
  res.m_uiQualityLevelsDiscardable = 0;
  res.m_uiQualityLevelsLoadable = 0;

  if (Stream == nullptr)
  {
    ezLog::Error("Shader Permutation '{0}': Data is not available", GetResourceID().GetData());
    return res;
  }

  ezShaderPermutationBinary PermutationBinary;

  if (PermutationBinary.Read(*Stream).Failed())
  {
    ezLog::Error("Shader Permutation '{0}': Could not read shader permutation binary", GetResourceID().GetData());
    return res;
  }

  auto pDevice = ezGALDevice::GetDefaultDevice();

  // get the shader render state object
  {
    m_hBlendState = pDevice->CreateBlendState(PermutationBinary.m_StateDescriptor.m_BlendDesc);
    m_hDepthStencilState = pDevice->CreateDepthStencilState(PermutationBinary.m_StateDescriptor.m_DepthStencilDesc);
    m_hRasterizerState = pDevice->CreateRasterizerState(PermutationBinary.m_StateDescriptor.m_RasterizerDesc);
  }

  ezGALShaderCreationDescription ShaderDesc;

  // iterate over all shader stages, add them to the descriptor
  for (ezUInt32 stage = ezGALShaderStage::VertexShader; stage < ezGALShaderStage::ENUM_COUNT; ++stage)
  {
    const ezUInt32 uiStageHash = PermutationBinary.m_uiShaderStageHashes[stage];

    if (uiStageHash == 0) // not used
      continue;

    ezShaderStageBinary* pStageBin = ezShaderStageBinary::LoadStageBinary((ezGALShaderStage::Enum) stage, uiStageHash);

    if (pStageBin == nullptr)
    {
      ezLog::Error("Shader Permutation '{0}': Stage '{1}' could not be loaded", GetResourceID().GetData(), ezGALShaderStage::Names[stage]);
      return res;
    }

    // store not only the hash but also the pointer to the stage binary
    // since it contains other useful information (resource bindings), that we need for shader binding
    m_pShaderStageBinaries[stage] = pStageBin;

    EZ_ASSERT_DEV(pStageBin->m_Stage == stage, "Invalid shader stage! Expected stage '{0}', but loaded data is for stage '{1}'", ezGALShaderStage::Names[stage], ezGALShaderStage::Names[pStageBin->m_Stage]);

    ShaderDesc.m_ByteCodes[stage] = pStageBin->m_pGALByteCode;

    uiGPUMem += pStageBin->m_ByteCode.GetCount();
  }

  m_hShader = pDevice->CreateShader(ShaderDesc);

  if (m_hShader.IsInvalidated())
  {
    ezLog::Error("Shader Permutation '{0}': Shader program creation failed", GetResourceID().GetData());
    return res;
  }

  pDevice->GetShader(m_hShader)->SetDebugName(GetResourceID());

  m_PermutationVars = PermutationBinary.m_PermutationVars;

  m_bShaderPermutationValid = true;

  ModifyMemoryUsage().m_uiMemoryGPU = uiGPUMem;

  return res;
}

void ezShaderPermutationResource::UpdateMemoryUsage(MemoryUsage& out_NewMemoryUsage)
{
  out_NewMemoryUsage.m_uiMemoryCPU = sizeof(ezShaderPermutationResource);
  out_NewMemoryUsage.m_uiMemoryGPU = ModifyMemoryUsage().m_uiMemoryGPU;
}

ezResourceTypeLoader* ezShaderPermutationResource::GetDefaultResourceTypeLoader() const
{
  return &g_PermutationResourceLoader;
}

struct ShaderPermutationResourceLoadData
{
  ShaderPermutationResourceLoadData() : m_Reader(&m_Storage)
  {
  }

  ezMemoryStreamStorage m_Storage;
  ezMemoryStreamReader m_Reader;
};

ezResult ezShaderPermutationResourceLoader::RunCompiler(const ezResourceBase* pResource, ezShaderPermutationBinary& BinaryInfo, bool bForce)
{
  if (ezShaderManager::IsRuntimeCompilationEnabled())
  {
    if (!bForce)
    {
      // check whether any dependent file has changed, and trigger a recompilation if necessary
      if (BinaryInfo.m_DependencyFile.HasAnyFileChanged())
      {
        bForce = true;
      }
    }

    if (!bForce) // no recompilation necessary
      return EZ_SUCCESS;

    ezStringBuilder sPermutationFile = pResource->GetResourceID();

    sPermutationFile.ChangeFileExtension("");
    sPermutationFile.Shrink(ezShaderManager::GetCacheDirectory().GetCharacterCount() + ezShaderManager::GetActivePlatform().GetCharacterCount() + 2, 1);

    sPermutationFile.Shrink(0, 8); // remove the hash at the end
    sPermutationFile.Append(".ezShader");

    ezArrayPtr<const ezPermutationVar> permutationVars = static_cast<const ezShaderPermutationResource*>(pResource)->GetPermutationVars();

    ezShaderCompiler sc;
    return sc.CompileShaderPermutationForPlatforms(sPermutationFile, permutationVars, ezShaderManager::GetActivePlatform());
  }
  else
  {
    if (bForce)
    {
      ezLog::Error("Shader was forced to be compiled, but runtime shader compilation is not available");
      return EZ_FAILURE;
    }
  }

  return EZ_SUCCESS;
}

bool ezShaderPermutationResourceLoader::IsResourceOutdated(const ezResourceBase* pResource) const
{
#if EZ_ENABLED(EZ_SUPPORTS_FILE_STATS)
  if (pResource->GetLoadedFileModificationTime().IsValid())
  {
    ezStringBuilder sAbs;
    if (ezFileSystem::ResolvePath(pResource->GetResourceID(), &sAbs, nullptr).Failed())
      return false;

    ezFileStats stat;
    if (ezOSFile::GetFileStats(sAbs, stat).Failed())
      return false;

    if (!stat.m_LastModificationTime.Compare(pResource->GetLoadedFileModificationTime(), ezTimestamp::CompareMode::FileTimeEqual))
      return true;
  }

#endif

  ezDependencyFile dep;
  if (dep.ReadDependencyFile(pResource->GetResourceID()).Failed())
    return true;

  return dep.HasAnyFileChanged();
}

ezResourceLoadData ezShaderPermutationResourceLoader::OpenDataStream(const ezResourceBase* pResource)
{
  ezResourceLoadData res;

  ezShaderPermutationBinary permutationBinary;

  bool bNeedsCompilation = true;

  {
    ezFileReader File;
    if (File.Open(pResource->GetResourceID().GetData()).Failed())
    {
      ezLog::Debug("Shader Permutation '{0}' does not exist, triggering recompile.", pResource->GetResourceID().GetData());

      bNeedsCompilation = false;
      if (RunCompiler(pResource, permutationBinary, true).Failed())
        return res;

      // try again
      if (File.Open(pResource->GetResourceID().GetData()).Failed())
      {
        ezLog::Debug("Shader Permutation '{0}' still does not exist after recompile.", pResource->GetResourceID().GetData());
        return res;
      }
    }

    res.m_sResourceDescription = File.GetFilePathRelative().GetData();

#if EZ_ENABLED(EZ_SUPPORTS_FILE_STATS)
    ezFileStats stat;
    if (ezOSFile::GetFileStats(File.GetFilePathAbsolute(), stat).Succeeded())
    {
      res.m_LoadedFileModificationDate = stat.m_LastModificationTime;
    }
#endif

    if (permutationBinary.Read(File).Failed())
    {
      ezLog::Error("Shader Permutation '{0}': Could not read shader permutation binary", pResource->GetResourceID().GetData());

      bNeedsCompilation = true;
    }
  }

  if (bNeedsCompilation)
  {
    if (RunCompiler(pResource, permutationBinary, false).Failed())
      return res;

    ezFileReader File;

    if (File.Open(pResource->GetResourceID().GetData()).Failed())
    {
      ezLog::Error("Shader Permutation '{0}': Failed to open the file", pResource->GetResourceID().GetData());
      return res;
    }

    if (permutationBinary.Read(File).Failed())
    {
      ezLog::Error("Shader Permutation '{0}': Binary data could not be read", pResource->GetResourceID().GetData());
      return res;
    }

    File.Close();
  }



  ShaderPermutationResourceLoadData* pData = EZ_DEFAULT_NEW(ShaderPermutationResourceLoadData);

  ezMemoryStreamWriter w(&pData->m_Storage);

  // preload the files that are referenced in the .ezPermutation file
  {
    // write the permutation file info back to the output stream, so that the resource can read it as well
    permutationBinary.Write(w);

    for (ezUInt32 stage = ezGALShaderStage::VertexShader; stage < ezGALShaderStage::ENUM_COUNT; ++stage)
    {
      const ezUInt32 uiStageHash = permutationBinary.m_uiShaderStageHashes[stage];

      if (uiStageHash == 0) // not used
        continue;

      // this is where the preloading happens
      ezShaderStageBinary::LoadStageBinary((ezGALShaderStage::Enum) stage, uiStageHash);
    }
  }

  res.m_pDataStream = &pData->m_Reader;
  res.m_pCustomLoaderData = pData;

  return res;
}

void ezShaderPermutationResourceLoader::CloseDataStream(const ezResourceBase* pResource, const ezResourceLoadData& LoaderData)
{
  ShaderPermutationResourceLoadData* pData = static_cast<ShaderPermutationResourceLoadData*>(LoaderData.m_pCustomLoaderData);

  EZ_DEFAULT_DELETE(pData);
}




EZ_STATICLINK_FILE(RendererCore, RendererCore_Shader_ShaderPermutationResource);

