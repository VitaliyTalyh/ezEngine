#include "Main.h"
#include <Foundation/Logging/Log.h>
#include <Foundation/Configuration/Startup.h>
#include <Foundation/Threading/Lock.h>
#include <RendererCore/Meshes/MeshComponent.h>
#include <GameUtils/Components/RotorComponent.h>
#include <Foundation/IO/FileSystem/FileReader.h>
#include <Core/WorldSerializer/WorldReader.h>
#include <GameUtils/Components/TimedDeathComponent.h>
#include <GameUtils/Components/SpawnComponent.h>
#include <CoreUtils/Assets/AssetFileHeader.h>
#include <GameUtils/Components/CameraComponent.h>
#include <GameUtils/Components/SliderComponent.h>
#include <GameUtils/Components/InputComponent.h>

ezPlayerApplication::ezPlayerApplication()
  : ezGameApplication(ezGameApplicationType::StandAlone, nullptr)
{
  m_pWorld = nullptr;
}

void ezPlayerApplication::BeforeCoreStartup()
{
  m_sSceneFile = ezCommandLineUtils::GetInstance()->GetStringOption("-scene", 0, "");
  EZ_ASSERT_ALWAYS(!m_sSceneFile.IsEmpty(), "Scene file has not been specified. Use the -scene command followed by a full path to the ezBinaryScene file");

  m_sAppProjectPath = FindProjectDirectoryForScene(m_sSceneFile);
  EZ_ASSERT_ALWAYS(!m_sAppProjectPath.IsEmpty(), "No project directory could be found for scene file '%s'", m_sSceneFile.GetData());
}


void ezPlayerApplication::AfterCoreStartup()
{
  DoProjectSetup();

  ezStartup::StartupEngine();

  SetupLevel();

  CreateGameStateForWorld(m_pWorld);

  ActivateAllGameStates();
}

void ezPlayerApplication::BeforeCoreShutdown()
{
  GetGameApplicationInstance()->DestroyWorld(m_pWorld);

  ezGameApplication::BeforeCoreShutdown();
}

void ezPlayerApplication::SetupLevel()
{
  EZ_LOG_BLOCK("SetupLevel", m_sSceneFile.GetData());

  m_pWorld = CreateWorld(m_sSceneFile, true);

  EZ_LOCK(m_pWorld->GetWriteMarker());

  /// \todo More 'elegant' solution to registering all component managers
  m_pWorld->GetOrCreateComponentManager<ezMeshComponentManager>();
  m_pWorld->GetOrCreateComponentManager<ezRotorComponentManager>();
  m_pWorld->GetOrCreateComponentManager<ezSliderComponentManager>();
  m_pWorld->GetOrCreateComponentManager<ezTimedDeathComponentManager>();
  m_pWorld->GetOrCreateComponentManager<ezSpawnComponentManager>();
  m_pWorld->GetOrCreateComponentManager<ezCameraComponentManager>();
  m_pWorld->GetOrCreateComponentManager<ezInputComponentManager>();
  

  {
    ezFileReader file;
    if (file.Open(m_sSceneFile).Succeeded())
    {
      // File Header
      {
        ezAssetFileHeader header;
        header.Read(file);

        char szSceneTag[16];
        file.ReadBytes(szSceneTag, sizeof(char) * 16);

        EZ_ASSERT_RELEASE(ezStringUtils::IsEqualN(szSceneTag, "[ezBinaryScene]", 16), "The given file is not a valid scene file");
        EZ_ASSERT_RELEASE(header.GetFileVersion() == 1, "The given scene file has an invalid version: %u", header.GetFileVersion());
      }

      ezWorldReader reader;
      reader.ReadWorldDescription(file);
      reader.InstantiateWorld(*m_pWorld);
      //reader.InstantiatePrefab(*m_pWorld, ezVec3(0, 2, 0), ezQuat::IdentityQuaternion(), ezVec3(0.1f));
    }
    else
    {
      ezLog::Error("Could not read level '%s'", m_sSceneFile.GetData());
    }
  }
}


EZ_CONSOLEAPP_ENTRY_POINT(ezPlayerApplication);