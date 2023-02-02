#include "CoreModLoader.h"
#include <filesystem>
#include <process.h>
#include <windows.h>
namespace fs = std::filesystem;
namespace CoreModLoader
{
void LoadCoreMods()
{
    auto Path = std::filesystem::temp_directory_path() / "unrealmodding" / "cpp_loader" / "mods";

    for (const auto &Entry : fs::directory_iterator(Path))
    {
        if (Entry.path().extension().string() == ".dll")
        {
            LoadLibraryW(Entry.path().c_str());
        }
    }
}
}; // namespace CoreModLoader