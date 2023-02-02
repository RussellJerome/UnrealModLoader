# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("UnrealCppLoader")

# Include sub-projects.
add_subdirectory ("vendor")
add_subdirectory ("UnrealCppLoader")
add_subdirectory ("xinput1_3")
add_subdirectory ("ExampleMod")
# add_subdirectory ("SetSeedMod")