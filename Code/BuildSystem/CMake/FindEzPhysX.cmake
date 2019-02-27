
# find the folder into which PhysX has been installed

# early out, if this target has been created before
if (TARGET ezPhysX::Foundation)
	return()
endif()

set (EZ_PHYSX_DIR "EZ_PHYSX_DIR-NOTFOUND" CACHE PATH "Directory of PhysX installation")

find_path(EZ_PHYSX_DIR PhysX_3.4/Include/PxActor.h
  PATHS
  ${CMAKE_SOURCE_DIR}/Code/ThirdParty/PhysX
)

set (PX_COMPILER_SUFFIX "vc14")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(PX_FOLDER_SUFFIX "win64")
  set(PX_LIB_SUFFIX "_x64.lib")
  set(PX_DLL_SUFFIX "_x64.dll")
else()
  set(PX_FOLDER_SUFFIX "win32")
  set(PX_LIB_SUFFIX "_x86.lib")
  set(PX_DLL_SUFFIX "_x86.dll")
endif()


set (PHYSX_LIB_DIR "${EZ_PHYSX_DIR}/PhysX_3.4/Lib/${PX_COMPILER_SUFFIX}${PX_FOLDER_SUFFIX}")
set (PHYSX_BIN_DIR "${EZ_PHYSX_DIR}/PhysX_3.4/Bin/${PX_COMPILER_SUFFIX}${PX_FOLDER_SUFFIX}")
set (PHYSX_INC_DIR "${EZ_PHYSX_DIR}/PhysX_3.4/Include")

set (PXSHARED_LIB_DIR "${EZ_PHYSX_DIR}/PxShared/Lib/${PX_COMPILER_SUFFIX}${PX_FOLDER_SUFFIX}")
set (PXSHARED_BIN_DIR "${EZ_PHYSX_DIR}/PxShared/Bin/${PX_COMPILER_SUFFIX}${PX_FOLDER_SUFFIX}")
set (PXSHARED_INC_DIR "${EZ_PHYSX_DIR}/PxShared/Include")



include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ezPhysX DEFAULT_MSG EZ_PHYSX_DIR)

if (ezPhysX_FOUND)

	add_library(ezPhysX::Foundation SHARED IMPORTED)
	set_target_properties(ezPhysX::Foundation PROPERTIES IMPORTED_LOCATION "${PXSHARED_BIN_DIR}/PxFoundation${PX_DLL_SUFFIX}")
	set_target_properties(ezPhysX::Foundation PROPERTIES IMPORTED_LOCATION_DEBUG "${PXSHARED_BIN_DIR}/PxFoundationDEBUG${PX_DLL_SUFFIX}")
	set_target_properties(ezPhysX::Foundation PROPERTIES IMPORTED_IMPLIB "${PXSHARED_LIB_DIR}/PxFoundation${PX_LIB_SUFFIX}")
	set_target_properties(ezPhysX::Foundation PROPERTIES IMPORTED_IMPLIB_DEBUG "${PXSHARED_LIB_DIR}/PxFoundationDEBUG${PX_LIB_SUFFIX}")
	set_target_properties(ezPhysX::Foundation PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${PXSHARED_INC_DIR}")

	add_library(ezPhysX::PVD SHARED IMPORTED)
	set_target_properties(ezPhysX::PVD PROPERTIES IMPORTED_LOCATION "${PXSHARED_BIN_DIR}/PxPvdSDK${PX_DLL_SUFFIX}")
	set_target_properties(ezPhysX::PVD PROPERTIES IMPORTED_LOCATION_DEBUG "${PXSHARED_BIN_DIR}/PxPvdSDKDEBUG${PX_DLL_SUFFIX}")
	set_target_properties(ezPhysX::PVD PROPERTIES IMPORTED_IMPLIB "${PXSHARED_LIB_DIR}/PxPvdSDK${PX_LIB_SUFFIX}")
	set_target_properties(ezPhysX::PVD PROPERTIES IMPORTED_IMPLIB_DEBUG "${PXSHARED_LIB_DIR}/PxPvdSDKDEBUG${PX_LIB_SUFFIX}")
	set_target_properties(ezPhysX::PVD PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${PXSHARED_INC_DIR}")
  target_link_libraries(ezPhysX::PVD INTERFACE ezPhysX::Foundation)

  add_library(ezPhysX::nvTools MODULE IMPORTED)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set_target_properties(ezPhysX::nvTools PROPERTIES IMPORTED_LOCATION "${PHYSX_BIN_DIR}/nvToolsExt64_1.dll")
  else()
    set_target_properties(ezPhysX::nvTools PROPERTIES IMPORTED_LOCATION "${PHYSX_BIN_DIR}/nvToolsExt32_1.dll")
  endif()

	add_library(ezPhysX::Common SHARED IMPORTED)
	set_target_properties(ezPhysX::Common PROPERTIES IMPORTED_LOCATION "${PHYSX_BIN_DIR}/PhysX3Common${PX_DLL_SUFFIX}")
	set_target_properties(ezPhysX::Common PROPERTIES IMPORTED_LOCATION_DEBUG "${PHYSX_BIN_DIR}/PhysX3CommonDEBUG${PX_DLL_SUFFIX}")
	set_target_properties(ezPhysX::Common PROPERTIES IMPORTED_IMPLIB "${PHYSX_LIB_DIR}/PhysX3Common${PX_LIB_SUFFIX}")
	set_target_properties(ezPhysX::Common PROPERTIES IMPORTED_IMPLIB_DEBUG "${PHYSX_LIB_DIR}/PhysX3CommonDEBUG${PX_LIB_SUFFIX}")
	set_target_properties(ezPhysX::Common PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${PHYSX_INC_DIR}")
  target_link_libraries(ezPhysX::Common INTERFACE ezPhysX::Foundation)

	add_library(ezPhysX::PhysX SHARED IMPORTED)
	set_target_properties(ezPhysX::PhysX PROPERTIES IMPORTED_LOCATION "${PHYSX_BIN_DIR}/PhysX3${PX_DLL_SUFFIX}")
	set_target_properties(ezPhysX::PhysX PROPERTIES IMPORTED_LOCATION_DEBUG "${PHYSX_BIN_DIR}/PhysX3DEBUG${PX_DLL_SUFFIX}")
	set_target_properties(ezPhysX::PhysX PROPERTIES IMPORTED_IMPLIB "${PHYSX_LIB_DIR}/PhysX3${PX_LIB_SUFFIX}")
	set_target_properties(ezPhysX::PhysX PROPERTIES IMPORTED_IMPLIB_DEBUG "${PHYSX_LIB_DIR}/PhysX3DEBUG${PX_LIB_SUFFIX}")
	set_target_properties(ezPhysX::PhysX PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${PHYSX_INC_DIR}")
  target_link_libraries(ezPhysX::PhysX INTERFACE ezPhysX::Common)

	add_library(ezPhysX::Cooking SHARED IMPORTED)
	set_target_properties(ezPhysX::Cooking PROPERTIES IMPORTED_LOCATION "${PHYSX_BIN_DIR}/PhysX3Cooking${PX_DLL_SUFFIX}")
	set_target_properties(ezPhysX::Cooking PROPERTIES IMPORTED_LOCATION_DEBUG "${PHYSX_BIN_DIR}/PhysX3CookingDEBUG${PX_DLL_SUFFIX}")
	set_target_properties(ezPhysX::Cooking PROPERTIES IMPORTED_IMPLIB "${PHYSX_LIB_DIR}/PhysX3Cooking${PX_LIB_SUFFIX}")
	set_target_properties(ezPhysX::Cooking PROPERTIES IMPORTED_IMPLIB_DEBUG "${PHYSX_LIB_DIR}/PhysX3CookingDEBUG${PX_LIB_SUFFIX}")
	set_target_properties(ezPhysX::Cooking PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${PHYSX_INC_DIR}")
  target_link_libraries(ezPhysX::Cooking INTERFACE ezPhysX::Foundation)

  add_library(ezPhysX::Extensions STATIC IMPORTED)
	set_target_properties(ezPhysX::Extensions PROPERTIES IMPORTED_LOCATION "${PHYSX_LIB_DIR}/PhysX3Extensions.lib")
	set_target_properties(ezPhysX::Extensions PROPERTIES IMPORTED_LOCATION_DEBUG "${PHYSX_LIB_DIR}/PhysX3ExtensionsDEBUG.lib")
	set_target_properties(ezPhysX::Extensions PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${PHYSX_INC_DIR}")
  target_link_libraries(ezPhysX::Extensions INTERFACE ezPhysX::PhysX)

	add_library(ezPhysX::Character SHARED IMPORTED)
	set_target_properties(ezPhysX::Character PROPERTIES IMPORTED_LOCATION "${PHYSX_BIN_DIR}/PhysX3CharacterKinematic${PX_DLL_SUFFIX}")
	set_target_properties(ezPhysX::Character PROPERTIES IMPORTED_LOCATION_DEBUG "${PHYSX_BIN_DIR}/PhysX3CharacterKinematicDEBUG${PX_DLL_SUFFIX}")
	set_target_properties(ezPhysX::Character PROPERTIES IMPORTED_IMPLIB "${PHYSX_LIB_DIR}/PhysX3CharacterKinematic${PX_LIB_SUFFIX}")
	set_target_properties(ezPhysX::Character PROPERTIES IMPORTED_IMPLIB_DEBUG "${PHYSX_LIB_DIR}/PhysX3CharacterKinematicDEBUG${PX_LIB_SUFFIX}")
	set_target_properties(ezPhysX::Character PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${PHYSX_INC_DIR}")
  target_link_libraries(ezPhysX::Character INTERFACE ezPhysX::PhysX)

endif()

unset (PHYSX_LIB_DIR)
unset (PHYSX_BIN_DIR)
unset (PHYSX_INC_DIR)
unset (PXSHARED_LIB_DIR)
unset (PXSHARED_BIN_DIR)
unset (PXSHARED_INC_DIR)
unset (PX_FOLDER_SUFFIX)
unset (PX_LIB_SUFFIX)





