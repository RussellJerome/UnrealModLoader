project(UnrealEngineModLauncher)

add_executable(${PROJECT_NAME} resource.h UnrealEngineModLauncher.cpp u4mdl_logo_ZfM_icon.ico)
target_sources(${PROJECT_NAME} PRIVATE UnrealEngineModLauncher.rc)

# definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE _UNICODE)

# install
install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION $<CONFIG>/Binaries/Win64
)

install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION $<CONFIG>/Binaries/Win64 OPTIONAL)
