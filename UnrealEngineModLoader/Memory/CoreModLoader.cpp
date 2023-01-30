#include "CoreModLoader.h"
#include <filesystem>
#include <process.h>
#include <windows.h>
namespace fs = std::filesystem;
namespace CoreModLoader
{
void LoadCoreMods()
{
    wchar_t CPath[MAX_PATH];
    GetModuleFileNameW(NULL, CPath, MAX_PATH);
    std::filesystem::path Path(CPath);
    Path = Path.parent_path().parent_path().parent_path() / "Content" / "CoreMods";

    if (!std::filesystem::exists(Path))
    {
        std::filesystem::create_directory(Path);
    }

    for (const auto &Entry : fs::directory_iterator(Path))
    {
        if (Entry.path().extension().string() == ".dll")
        {
            LoadLibraryW(Entry.path().c_str());
        }
    }
}
}; // namespace CoreModLoader