project(UnrealEngineModLoader)

set(IMGUI_FILES
	ImGui/imconfig.h
	ImGui/imgui.cpp
	ImGui/imgui.h
	ImGui/imgui_demo.cpp
	ImGui/imgui_draw.cpp
	ImGui/imgui_impl_dx11.cpp
	ImGui/imgui_impl_dx11.h
	ImGui/imgui_impl_win32.cpp
	ImGui/imgui_impl_win32.h
	ImGui/imgui_internal.h
	ImGui/imgui_tables.cpp
	ImGui/imgui_widgets.cpp
	ImGui/imstb_rectpack.h
	ImGui/imstb_textedit.h
	ImGui/imstb_truetype.h
)

set(INI_FILES
	INI/INI.h
)

set(MINHOOK_FILES
	MinHook/include/MinHook.h
)

set(UE4_FILES
	UE4/Basic.cpp
	UE4/Basic.hpp
	UE4/CoreUObject_classes.hpp
	UE4/CoreUObject_functions.cpp
	UE4/CoreUObject_parameters.hpp
	UE4/CoreUObject_structs.hpp
	UE4/Ue4.hpp
)

set(UNREALENGINEMODLOADER_FILES
	EventSystem.h
	Hooks.cpp
	Hooks.h
	LoaderUI.cpp
	LoaderUI.h
	PakLoader.cpp
	PakLoader.h
	UMLDefs.h
	UnrealEngineModLoader/GameInfo/GameInfo.cpp
	UnrealEngineModLoader/GameInfo/GameInfo.h
	UnrealEngineModLoader/Memory/CoreModLoader.cpp
	UnrealEngineModLoader/Memory/CoreModLoader.h
	UnrealEngineModLoader/Memory/mem.cpp
	UnrealEngineModLoader/Memory/mem.h
	UnrealEngineModLoader/Mod/Mod.cpp
	UnrealEngineModLoader/Mod/Mod.h
	UnrealEngineModLoader/Utilities/Dumper.cpp
	UnrealEngineModLoader/Utilities/Dumper.h
	UnrealEngineModLoader/Utilities/EngineDefFinder.cpp
	UnrealEngineModLoader/Utilities/EngineDefFinder.h
	UnrealEngineModLoader/Utilities/Globals.cpp
	UnrealEngineModLoader/Utilities/Globals.h
	UnrealEngineModLoader/Utilities/Logger.cpp
	UnrealEngineModLoader/Utilities/Logger.h
	UnrealEngineModLoader/Utilities/MinHook.h
	UnrealEngineModLoader/Utilities/Pattern.h
	UnrealEngineModLoader/Utilities/Version.h
	UnrealEngineModLoader/dllmain.cpp
)


add_library(${PROJECT_NAME} SHARED ${IMGUI_FILES} ${INI_FILES} ${MINHOOK_FILES} ${UE4_FILES} ${UNREALENGINEMODLOADER_FILES})

# definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE UNREALENGINEMODLOADER_EXPORTS _UNICODE) # work-around, 'UnrealEngineModLoader_EXPORTS' should be used in source code
target_compile_definitions(${PROJECT_NAME} PUBLIC _USRDLL _CRT_SECURE_NO_WARNINGS)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/MinHook
	${CMAKE_CURRENT_SOURCE_DIR}/
	${CMAKE_CURRENT_SOURCE_DIR}/UnrealEngineModLoader
)

target_link_directories(${PROJECT_NAME} PUBLIC MinHook/lib)
target_link_libraries(${PROJECT_NAME} libMinHook-x64-v141-mtd)

# install
install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION $<CONFIG>/Binaries/Win64
)

install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION $<CONFIG>/Binaries/Win64 OPTIONAL)
