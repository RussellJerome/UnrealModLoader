cmake_minimum_required(VERSION 3.0)
project(UnrealEngineModLoader)

set(CMAKE_CXX_STANDARD 17) # required by i.e. #include <filesystem>
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# TODO: optimize: avoid restricted default folder "C:/Program Files (x86)/..."
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install" CACHE FILEPATH "Install path prefix, prependen onto install directories." FORCE)

add_subdirectory(UnrealEngineModLoader)
add_subdirectory(UnrealEngineModLauncher)
add_subdirectory(LoaderAutoInjector) # xinput1_3.dll
add_subdirectory(ExampleMod)

# ADD YOUR MODS HERE
#add_subdirectory(MyMod1)
#add_subdirectory(MyMod2)
# ...

# install
install(FILES "ModLoaderInfo.ini"
	DESTINATION $<CONFIG>/Binaries/Win64
)

install(DIRECTORY "Profiles"
	DESTINATION $<CONFIG>/Binaries/Win64
)
