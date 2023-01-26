
add_definitions(-DEXAMPLEMOD_EXPORTS)

add_library(ExampleMod SHARED "dllmain.cpp" "ExampleMod.h" "ExampleMod.cpp")

target_link_libraries(ExampleMod PUBLIC UnrealEngineModLoader)
# todo: reexport