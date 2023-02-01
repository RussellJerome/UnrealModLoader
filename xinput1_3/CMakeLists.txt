
add_definitions(-DUNICODE -D_UNICODE -D_WINDOWS)

enable_language(C CXX ASM_MASM)
add_library(xinput1_3 SHARED "dllmain.cpp" "xinput1_3.asm" "xinput1_3.def")