
# todo: split into another lib
set(UE4_SOURCE "UE4/Basic.hpp" "UE4/Basic.cpp" "UE4/CoreUObject_classes.hpp" "UE4/CoreUObject_functions.cpp" "UE4/CoreUObject_parameters.hpp" "UE4/CoreUObject_structs.hpp" "UE4/Ue4.hpp")

set(SHARED_SOURCE "Shared/Hooks.h" "Shared/Hooks.cpp" "Shared/LoaderUI.h" "Shared/LoaderUI.cpp" "Shared/PakLoader.h" "Shared/PakLoader.cpp" "Shared/UMLDefs.h")

set(LOG_SOURCE "Log/Log.h" "Log/Log.cpp")
set(GAMEINFO_SOURCE "GameInfo/GameInfo.h" "GameInfo/GameInfo.cpp" "GameInfo/GameSettings.h" "GameInfo/GameSettings.cpp")
set(MEMORY_SOURCE "Memory/CoreModLoader.h" "Memory/CoreModLoader.cpp" "Memory/mem.h" "Memory/mem.cpp")
set(MOD_SOURCE "Mod/Mod.h" "Mod/Mod.cpp")
set(UTILITIES_SOURCE "Utilities/Dumper.h" "Utilities/Dumper.cpp" "Utilities/EngineDefFinder.h" "Utilities/EngineDefFinder.cpp" "Utilities/Globals.h" "Utilities/Globals.cpp" "Utilities/MinHook.h" "Utilities/Pattern.h" "Utilities/Version.h")

set(UML_SOURCE "dllmain.cpp" ${GAMEINFO_SOURCE} ${SHARED_SOURCE} ${MEMORY_SOURCE} ${MOD_SOURCE} ${UTILITIES_SOURCE} ${UE4_SOURCE} ${LOG_SOURCE})

add_definitions(-DUNICODE -D_UNICODE -DUNREALENGINEMODLOADER_EXPORTS -D_WINDOWS)

add_library(UnrealEngineModLoader SHARED ${UML_SOURCE})

set_property(TARGET UnrealEngineModLoader PROPERTY CXX_STANDARD 17)

target_include_directories(UnrealEngineModLoader PUBLIC "./")

target_include_directories(UnrealEngineModLoader PUBLIC ${ImGui_INCLUDE_DIRECTORIES})
target_link_libraries(UnrealEngineModLoader PUBLIC ImGui)

target_link_libraries(UnrealEngineModLoader PUBLIC minhook)

target_link_libraries(UnrealEngineModLoader PUBLIC FeatherIni)

target_link_libraries(UnrealEngineModLoader PUBLIC d3d11 d3dcompiler)

target_link_libraries(UnrealEngineModLoader PUBLIC spdlog::spdlog)