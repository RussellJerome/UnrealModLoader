
# todo: split into another lib
set(UE4_SOURCE "UE4/Basic.hpp" "UE4/Basic.cpp" "UE4/CoreUObject_classes.hpp" "UE4/CoreUObject_functions.cpp" "UE4/CoreUObject_parameters.hpp" "UE4/CoreUObject_structs.hpp" "UE4/Ue4.hpp")

set(SHARED_SOURCE "Shared/Hooks.h" "Shared/Hooks.cpp" "Shared/UCPPLDefs.h")

if (ENABLE_GUI)
	set(SHARED_SOURCE ${SHARED_SOURCE} "Shared/LoaderUI.h" "Shared/LoaderUI.cpp")
	add_definitions(-DENABLE_GUI)
endif()

set(LOG_SOURCE "Log/Log.h" "Log/Log.cpp")
set(GAMEINFO_SOURCE "GameInfo/GameInfo.h" "GameInfo/GameInfo.cpp" "GameInfo/GameSettings.h")
set(MEMORY_SOURCE "Memory/CoreModLoader.h" "Memory/CoreModLoader.cpp" "Memory/mem.h" "Memory/mem.cpp" "Memory/Pattern.h" "Memory/Pattern.cpp" "Memory/PatternScanner.h" "Memory/PatternScanner.h")
set(MOD_SOURCE "Mod/Mod.h" "Mod/Mod.cpp")
set(UTILITIES_SOURCE "Utilities/Dumper.h" "Utilities/Dumper.cpp" "Utilities/EngineDefFinder.h" "Utilities/EngineDefFinder.cpp" "Utilities/Globals.h" "Utilities/Globals.cpp" "Utilities/MinHook.h")

set(UCPPL_SOURCE "dllmain.cpp" ${GAMEINFO_SOURCE} ${SHARED_SOURCE} ${MEMORY_SOURCE} ${MOD_SOURCE} ${UTILITIES_SOURCE} ${UE4_SOURCE} ${LOG_SOURCE})

add_definitions(-DUNICODE -D_UNICODE -DUNREALCPPLOADER_EXPORTS -D_WINDOWS)
add_compile_definitions(UNREALCPPLOADER_VERSION="${UNREALCPPLOADER_VERSION}")
add_compile_definitions(MODLOADER_VERSION="${UNREALCPPLOADER_VERSION}")

add_library(UnrealCppLoader SHARED ${UCPPL_SOURCE})

set_property(TARGET UnrealCppLoader PROPERTY CXX_STANDARD 23)

target_include_directories(UnrealCppLoader PUBLIC "./")

if(ENABLE_GUI)
	target_include_directories(UnrealCppLoader PUBLIC ${ImGui_INCLUDE_DIRECTORIES})
	target_link_libraries(UnrealCppLoader PUBLIC ImGui)
endif()

target_link_libraries(UnrealCppLoader PUBLIC minhook)

target_link_libraries(UnrealCppLoader PUBLIC d3d11 d3dcompiler)

target_link_libraries(UnrealCppLoader PUBLIC spdlog::spdlog)

target_link_libraries(UnrealCppLoader PUBLIC nlohmann_json::nlohmann_json)