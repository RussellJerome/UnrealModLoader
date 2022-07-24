project(LoaderAutoInjector LANGUAGES CXX ASM_MASM)

set(LOADERAUTOINJECTOR_FILES
	Loader/Loader.cpp
	Loader/Loader.h
	xinput1_3/xinput1_3.cpp
	xinput1_3/xinput1_3.def
	xinput1_3/xinput1_3_asm.asm
)


add_library(${PROJECT_NAME} SHARED ${LOADERAUTOINJECTOR_FILES})

# change output name from LoaderAutoInjector to xinput1_3
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME xinput1_3)

# definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE LOADERAUTOINJECTOR_EXPORTS _UNICODE) # work-around, 'LoaderAutoInjector_EXPORTS' should be used in source code
target_compile_definitions(${PROJECT_NAME} PUBLIC _USRDLL _CRT_SECURE_NO_WARNINGS)

# includes
target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../UnrealEngineModLoader
	${CMAKE_CURRENT_SOURCE_DIR}
)

# install
install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION $<CONFIG>/Binaries/Win64
)

install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION $<CONFIG>/Binaries/Win64 OPTIONAL)
