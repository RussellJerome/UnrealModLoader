# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("UnrealModLoader")

# Include sub-projects.
add_subdirectory ("UnrealEngineModLoader")
add_subdirectory ("ExampleMod")
add_subdirectory ("vendor")
