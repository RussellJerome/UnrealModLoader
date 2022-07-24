# CONFIG: Choose a proper project/target name
project(ExampleMod)

# CONFIG: Set bigobj files (*.cpp) with thousands of functions to export
set(EXAMPLEMOD_BIGOBJ_FILES
	# ...
)

# CONFIG: Set other header/source files (*.h/*.hpp/*.cpp) here
set(EXAMPLEMOD_FILES
	${EXAMPLEMOD_BIGOBJ_FILES} # bigobj from above are also source code files
	../UnrealEngineModLoader/UE4/Basic.cpp
	../UnrealEngineModLoader/UE4/CoreUObject_functions.cpp
	../UnrealEngineModLoader/UE4/Ue4.hpp
	dllmain.cpp
	ExampleMod.cpp
	ExampleMod.h
)
set_source_files_properties(${EXAMPLEMOD_BIGOBJ_FILES} PROPERTIES COMPILE_OPTIONS "/bigobj")

add_library(${PROJECT_NAME} SHARED ${EXAMPLEMOD_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC UnrealEngineModLoader)

# definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE _UNICODE)

# includes
# CONFIG: set your include directories here
#target_include_directories(${PROJECT_NAME} PUBLIC PATH_TO_INCLUDE_FOLDER)

# linking
# CONFIG: set folders with libraries here
#target_link_directories(${PROJECT_NAME} PUBLIC YOUR_PATH_TO_LIBRARY)
target_link_libraries(${PROJECT_NAME} PUBLIC UnrealEngineModLoader)
# CONFIG: set library names only here (no folders)
#target_link_libraries(${PROJECT_NAME} PUBLIC YOUR_LIBRARY_NAME)

# install
install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION $<CONFIG>/Content/CoreMods
)

install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION $<CONFIG>/Content/CoreMods OPTIONAL)
