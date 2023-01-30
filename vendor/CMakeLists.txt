
set(CMAKE_CXX_STANDARD 23)
# ======== ImGui ==========

add_library(ImGui STATIC 
		"imgui/imgui.cpp" 
		"imgui/imgui_draw.cpp"
		"imgui/imgui_internal.h"
		"imgui/imgui_widgets.cpp"
		"imgui/imgui_demo.cpp"
		"imgui/imgui_tables.cpp"
		
		"imgui/backends/imgui_impl_dx11.h"
		"imgui/backends/imgui_impl_dx11.cpp"

		"imgui/backends/imgui_impl_win32.h"
		"imgui/backends/imgui_impl_win32.cpp"

		"imgui/misc/cpp/imgui_stdlib.h"
		"imgui/misc/cpp/imgui_stdlib.cpp")

target_include_directories(ImGui PUBLIC "imgui" "imgui/backends")

# ======== MinHook ========

set(BUILD_SHARED_LIBS OFF)
add_subdirectory("MinHook")

# ======== FeatherIni ========

add_library(FeatherIni INTERFACE)
target_include_directories(FeatherIni INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/FeatherIni")

# ======== Fmt ======== 

add_subdirectory("fmt")

# ========  SpdLog ========

set(SPDLOG_FMT_EXTERNAL YES)
add_subdirectory("spdlog")