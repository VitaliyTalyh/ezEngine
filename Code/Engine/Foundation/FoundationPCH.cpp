#include <FoundationPCH.h>

EZ_STATICLINK_LIBRARY(Foundation)
{
  if (bReturn)
    return;

  EZ_STATICLINK_REFERENCE(Foundation_Algorithm_Implementation_HashHelperString);
  EZ_STATICLINK_REFERENCE(Foundation_Algorithm_Implementation_HashingUtils);
  EZ_STATICLINK_REFERENCE(Foundation_Application_Config_Implementation_FileSystemConfig);
  EZ_STATICLINK_REFERENCE(Foundation_Application_Config_Implementation_PluginConfig);
  EZ_STATICLINK_REFERENCE(Foundation_Application_Implementation_Application);
  EZ_STATICLINK_REFERENCE(Foundation_Application_Implementation_MainLoop);
  EZ_STATICLINK_REFERENCE(Foundation_Application_Implementation_Android_Application_android);
  EZ_STATICLINK_REFERENCE(Foundation_Application_Implementation_uwp_Application_uwp);
  EZ_STATICLINK_REFERENCE(Foundation_Basics_Assert);
  EZ_STATICLINK_REFERENCE(Foundation_Basics_Basics);
  EZ_STATICLINK_REFERENCE(Foundation_Basics_IncludeAll);
  EZ_STATICLINK_REFERENCE(Foundation_Basics_Platform_Win_HResultUtils);
  EZ_STATICLINK_REFERENCE(Foundation_Basics_Platform_uwp_UWPUtils);
  EZ_STATICLINK_REFERENCE(Foundation_CodeUtils_Implementation_Conditions);
  EZ_STATICLINK_REFERENCE(Foundation_CodeUtils_Implementation_Defines);
  EZ_STATICLINK_REFERENCE(Foundation_CodeUtils_Implementation_Expand);
  EZ_STATICLINK_REFERENCE(Foundation_CodeUtils_Implementation_FileHandling);
  EZ_STATICLINK_REFERENCE(Foundation_CodeUtils_Implementation_Macros);
  EZ_STATICLINK_REFERENCE(Foundation_CodeUtils_Implementation_MathExpression);
  EZ_STATICLINK_REFERENCE(Foundation_CodeUtils_Implementation_Preprocessor);
  EZ_STATICLINK_REFERENCE(Foundation_CodeUtils_Implementation_PreprocessorParseHelper);
  EZ_STATICLINK_REFERENCE(Foundation_CodeUtils_Implementation_TokenParseUtils);
  EZ_STATICLINK_REFERENCE(Foundation_CodeUtils_Implementation_Tokenizer);
  EZ_STATICLINK_REFERENCE(Foundation_Communication_Implementation_DataTransfer);
  EZ_STATICLINK_REFERENCE(Foundation_Communication_Implementation_GlobalEvent);
  EZ_STATICLINK_REFERENCE(Foundation_Communication_Implementation_IpcChannel);
  EZ_STATICLINK_REFERENCE(Foundation_Communication_Implementation_IpcChannelEnet);
  EZ_STATICLINK_REFERENCE(Foundation_Communication_Implementation_Message);
  EZ_STATICLINK_REFERENCE(Foundation_Communication_Implementation_MessageLoop);
  EZ_STATICLINK_REFERENCE(Foundation_Communication_Implementation_Mobile_MessageLoop_mobile);
  EZ_STATICLINK_REFERENCE(Foundation_Communication_Implementation_RemoteInterface);
  EZ_STATICLINK_REFERENCE(Foundation_Communication_Implementation_RemoteInterfaceEnet);
  EZ_STATICLINK_REFERENCE(Foundation_Communication_Implementation_RemoteMessage);
  EZ_STATICLINK_REFERENCE(Foundation_Communication_Implementation_Telemetry);
  EZ_STATICLINK_REFERENCE(Foundation_Communication_Implementation_TelemetryHelpers);
  EZ_STATICLINK_REFERENCE(Foundation_Communication_Implementation_TelemetryMessage);
  EZ_STATICLINK_REFERENCE(Foundation_Communication_Implementation_TelemetryThread);
  EZ_STATICLINK_REFERENCE(Foundation_Communication_Implementation_Win_MessageLoop_win);
  EZ_STATICLINK_REFERENCE(Foundation_Communication_Implementation_Win_PipeChannel_win);
  EZ_STATICLINK_REFERENCE(Foundation_Configuration_Implementation_CVar);
  EZ_STATICLINK_REFERENCE(Foundation_Configuration_Implementation_Plugin);
  EZ_STATICLINK_REFERENCE(Foundation_Configuration_Implementation_Singleton);
  EZ_STATICLINK_REFERENCE(Foundation_Configuration_Implementation_Startup);
  EZ_STATICLINK_REFERENCE(Foundation_Containers_Implementation_Blob);
  EZ_STATICLINK_REFERENCE(Foundation_DataProcessing_Stream_DefaultImplementations_Implementation_ZeroInitializer);
  EZ_STATICLINK_REFERENCE(Foundation_DataProcessing_Stream_Implementation_ProcessingStream);
  EZ_STATICLINK_REFERENCE(Foundation_DataProcessing_Stream_Implementation_ProcessingStreamGroup);
  EZ_STATICLINK_REFERENCE(Foundation_DataProcessing_Stream_Implementation_ProcessingStreamProcessor);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Archive_Implementation_Archive);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Archive_Implementation_ArchiveBuilder);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Archive_Implementation_ArchiveReader);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Archive_Implementation_ArchiveUtils);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Archive_Implementation_DataDirTypeArchive);
  EZ_STATICLINK_REFERENCE(Foundation_IO_FileSystem_Implementation_DataDirType);
  EZ_STATICLINK_REFERENCE(Foundation_IO_FileSystem_Implementation_DataDirTypeFolder);
  EZ_STATICLINK_REFERENCE(Foundation_IO_FileSystem_Implementation_DeferredFileWriter);
  EZ_STATICLINK_REFERENCE(Foundation_IO_FileSystem_Implementation_FileReader);
  EZ_STATICLINK_REFERENCE(Foundation_IO_FileSystem_Implementation_FileSystem);
  EZ_STATICLINK_REFERENCE(Foundation_IO_FileSystem_Implementation_FileWriter);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_ChunkStream);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_CompressedStreamZlib);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_CompressedStreamZstd);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_DeduplicationContext);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_DependencyFile);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_DirectoryWatcher);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_JSONParser);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_JSONReader);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_JSONWriter);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_MemoryMappedFile);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_MemoryStream);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_OSFile);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_OpenDdlParser);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_OpenDdlReader);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_OpenDdlUtils);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_OpenDdlWriter);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_StandardJSONWriter);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_Stream);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_StreamOperations);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_StreamOperationsOther);
  EZ_STATICLINK_REFERENCE(Foundation_IO_Implementation_StringDeduplicationContext);
  EZ_STATICLINK_REFERENCE(Foundation_Logging_Implementation_ConsoleWriter);
  EZ_STATICLINK_REFERENCE(Foundation_Logging_Implementation_ETWWriter);
  EZ_STATICLINK_REFERENCE(Foundation_Logging_Implementation_HTMLWriter);
  EZ_STATICLINK_REFERENCE(Foundation_Logging_Implementation_Log);
  EZ_STATICLINK_REFERENCE(Foundation_Logging_Implementation_LogEntry);
  EZ_STATICLINK_REFERENCE(Foundation_Logging_Implementation_VisualStudioWriter);
  EZ_STATICLINK_REFERENCE(Foundation_Math_Implementation_Color);
  EZ_STATICLINK_REFERENCE(Foundation_Math_Implementation_Float16);
  EZ_STATICLINK_REFERENCE(Foundation_Math_Implementation_Frustum);
  EZ_STATICLINK_REFERENCE(Foundation_Math_Implementation_Intersection);
  EZ_STATICLINK_REFERENCE(Foundation_Math_Implementation_Math);
  EZ_STATICLINK_REFERENCE(Foundation_Math_Implementation_Random);
  EZ_STATICLINK_REFERENCE(Foundation_Memory_Implementation_AllocatorBase);
  EZ_STATICLINK_REFERENCE(Foundation_Memory_Implementation_AllocatorWrapper);
  EZ_STATICLINK_REFERENCE(Foundation_Memory_Implementation_EndianHelper);
  EZ_STATICLINK_REFERENCE(Foundation_Memory_Implementation_FrameAllocator);
  EZ_STATICLINK_REFERENCE(Foundation_Memory_Implementation_MemoryTracker);
  EZ_STATICLINK_REFERENCE(Foundation_Memory_Implementation_MemoryUtils);
  EZ_STATICLINK_REFERENCE(Foundation_Memory_Implementation_PageAllocator);
  EZ_STATICLINK_REFERENCE(Foundation_Memory_Policies_GuardedAllocation);
  EZ_STATICLINK_REFERENCE(Foundation_Profiling_Implementation_Profiling);
  EZ_STATICLINK_REFERENCE(Foundation_Reflection_Implementation_PropertyAttributes);
  EZ_STATICLINK_REFERENCE(Foundation_Reflection_Implementation_PropertyPath);
  EZ_STATICLINK_REFERENCE(Foundation_Reflection_Implementation_RTTI);
  EZ_STATICLINK_REFERENCE(Foundation_Reflection_Implementation_ReflectionUtils);
  EZ_STATICLINK_REFERENCE(Foundation_Reflection_Implementation_StandardTypes);
  EZ_STATICLINK_REFERENCE(Foundation_Serialization_Implementation_AbstractObjectGraph);
  EZ_STATICLINK_REFERENCE(Foundation_Serialization_Implementation_BinarySerializer);
  EZ_STATICLINK_REFERENCE(Foundation_Serialization_Implementation_DdlSerializer);
  EZ_STATICLINK_REFERENCE(Foundation_Serialization_Implementation_GraphPatch);
  EZ_STATICLINK_REFERENCE(Foundation_Serialization_Implementation_GraphVersioning);
  EZ_STATICLINK_REFERENCE(Foundation_Serialization_Implementation_ReflectionSerializer);
  EZ_STATICLINK_REFERENCE(Foundation_Serialization_Implementation_RttiConverterReader);
  EZ_STATICLINK_REFERENCE(Foundation_Serialization_Implementation_RttiConverterWriter);
  EZ_STATICLINK_REFERENCE(Foundation_SimdMath_Implementation_SimdMat4f);
  EZ_STATICLINK_REFERENCE(Foundation_SimdMath_Implementation_SimdQuat);
  EZ_STATICLINK_REFERENCE(Foundation_Strings_Implementation_FormatString);
  EZ_STATICLINK_REFERENCE(Foundation_Strings_Implementation_HashedString);
  EZ_STATICLINK_REFERENCE(Foundation_Strings_Implementation_PathUtils);
  EZ_STATICLINK_REFERENCE(Foundation_Strings_Implementation_StringBuilder);
  EZ_STATICLINK_REFERENCE(Foundation_Strings_Implementation_StringConversion);
  EZ_STATICLINK_REFERENCE(Foundation_Strings_Implementation_StringUtils);
  EZ_STATICLINK_REFERENCE(Foundation_Strings_Implementation_StringView);
  EZ_STATICLINK_REFERENCE(Foundation_Strings_Implementation_TranslationLookup);
  EZ_STATICLINK_REFERENCE(Foundation_Strings_Implementation_snprintf);
  EZ_STATICLINK_REFERENCE(Foundation_System_Implementation_Process);
  EZ_STATICLINK_REFERENCE(Foundation_System_Implementation_ProcessGroup);
  EZ_STATICLINK_REFERENCE(Foundation_System_Implementation_SystemInformation);
  EZ_STATICLINK_REFERENCE(Foundation_System_Implementation_UuidGenerator);
  EZ_STATICLINK_REFERENCE(Foundation_Threading_Implementation_OSThread);
  EZ_STATICLINK_REFERENCE(Foundation_Threading_Implementation_TaskGroups);
  EZ_STATICLINK_REFERENCE(Foundation_Threading_Implementation_TaskSystem);
  EZ_STATICLINK_REFERENCE(Foundation_Threading_Implementation_TaskWorkers);
  EZ_STATICLINK_REFERENCE(Foundation_Threading_Implementation_Tasks);
  EZ_STATICLINK_REFERENCE(Foundation_Threading_Implementation_Thread);
  EZ_STATICLINK_REFERENCE(Foundation_Threading_Implementation_ThreadSignal);
  EZ_STATICLINK_REFERENCE(Foundation_Threading_Implementation_ThreadUtils);
  EZ_STATICLINK_REFERENCE(Foundation_Time_Implementation_Clock);
  EZ_STATICLINK_REFERENCE(Foundation_Time_Implementation_DefaultTimeStepSmoothing);
  EZ_STATICLINK_REFERENCE(Foundation_Time_Implementation_Stopwatch);
  EZ_STATICLINK_REFERENCE(Foundation_Time_Implementation_Time);
  EZ_STATICLINK_REFERENCE(Foundation_Time_Implementation_Timestamp);
  EZ_STATICLINK_REFERENCE(Foundation_Tracks_Implementation_ColorGradient);
  EZ_STATICLINK_REFERENCE(Foundation_Tracks_Implementation_Curve1D);
  EZ_STATICLINK_REFERENCE(Foundation_Tracks_Implementation_EventTrack);
  EZ_STATICLINK_REFERENCE(Foundation_Types_Implementation_Status);
  EZ_STATICLINK_REFERENCE(Foundation_Types_Implementation_TagRegistry);
  EZ_STATICLINK_REFERENCE(Foundation_Types_Implementation_VarianceTypes);
  EZ_STATICLINK_REFERENCE(Foundation_Types_Implementation_Variant);
  EZ_STATICLINK_REFERENCE(Foundation_Utilities_Implementation_CommandLineUtils);
  EZ_STATICLINK_REFERENCE(Foundation_Utilities_Implementation_Compression);
  EZ_STATICLINK_REFERENCE(Foundation_Utilities_Implementation_ConversionUtils);
  EZ_STATICLINK_REFERENCE(Foundation_Utilities_Implementation_DGMLWriter);
  EZ_STATICLINK_REFERENCE(Foundation_Utilities_Implementation_ExceptionHandler);
  EZ_STATICLINK_REFERENCE(Foundation_Utilities_Implementation_GraphicsUtils);
  EZ_STATICLINK_REFERENCE(Foundation_Utilities_Implementation_Node);
  EZ_STATICLINK_REFERENCE(Foundation_Utilities_Implementation_Progress);
  EZ_STATICLINK_REFERENCE(Foundation_Utilities_Implementation_StackTracer);
  EZ_STATICLINK_REFERENCE(Foundation_Utilities_Implementation_Stats);
}

