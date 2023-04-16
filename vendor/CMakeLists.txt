include(ExternalProject)
set(FETCHCONTENT_QUIET FALSE)
include(FetchContent)
set(CMAKE_CXX_STANDARD 23)
# ======== ImGui ==========

if(ENABLE_GUI)

FetchContent_Declare(
	ImGui_Download
	
	GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
	GIT_TAG "2efebe331547a31b34ebf4049545df241cd04e50"
	GIT_PROGRESS TRUE
	GIT_SHALLOW FALSE

	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
)
FetchContent_MakeAvailable(ImGui_Download)

add_library(ImGui STATIC
		"${imgui_download_SOURCE_DIR}/imgui.cpp" 
		"${imgui_download_SOURCE_DIR}/imgui_draw.cpp"
		"${imgui_download_SOURCE_DIR}/imgui_internal.h"
		"${imgui_download_SOURCE_DIR}/imgui_widgets.cpp"
		"${imgui_download_SOURCE_DIR}/imgui_demo.cpp"
		"${imgui_download_SOURCE_DIR}/imgui_tables.cpp"
		
		"${imgui_download_SOURCE_DIR}/backends/imgui_impl_dx11.h"
		"${imgui_download_SOURCE_DIR}/backends/imgui_impl_dx11.cpp"

		"${imgui_download_SOURCE_DIR}/backends/imgui_impl_win32.h"
		"${imgui_download_SOURCE_DIR}/backends/imgui_impl_win32.cpp"

		"${imgui_download_SOURCE_DIR}/misc/cpp/imgui_stdlib.h"
		"${imgui_download_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp")

target_include_directories(ImGui PUBLIC "${imgui_download_SOURCE_DIR}" "${imgui_download_SOURCE_DIR}/backends")

endif()

# ======== MinHook ========

FetchContent_Declare(
	MinHook

	GIT_REPOSITORY "https://github.com/TsudaKageyu/minhook.git"
	GIT_TAG "49d03ad118cf7f6768c79a8f187e14b8f2a07f94"
	GIT_PROGRESS TRUE
	GIT_SHALLOW FALSE
)
set(BUILD_SHARED_LIBS OFF)
FetchContent_MakeAvailable(MinHook)

# ======== Fmt ======== 

FetchContent_Declare(
	fmt

	GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
	GIT_TAG "8.0.0"
	GIT_PROGRESS TRUE
	GIT_SHALLOW FALSE
)
FetchContent_MakeAvailable(fmt)

# ========  SpdLog ========

FetchContent_Declare(
	spdlog

	GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
	GIT_TAG "927cc29444a294d76e83dfb898e797dc431ce094"
	GIT_PROGRESS TRUE
	GIT_SHALLOW FALSE
)
set(SPDLOG_FMT_EXTERNAL YES)
FetchContent_MakeAvailable(spdlog)

# ======== Json ========

FetchContent_Declare(
	nlohmann_json

	GIT_REPOSITORY "https://github.com/nlohmann/json.git"
	GIT_TAG "b2306145e1789368e6f261680e8dc007e91cc986"
	GIT_PROGRESS TRUE
	GIT_SHALLOW FALSE
)
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(nlohmann_json)