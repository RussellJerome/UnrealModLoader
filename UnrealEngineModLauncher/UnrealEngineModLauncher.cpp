#include <Windows.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <psapi.h>

uint32_t FoundGamepid = 0;
std::vector<std::string> GameProfiles;

void InjectDLL(std::string path)
{
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, FoundGamepid);
    if (hProc && hProc != INVALID_HANDLE_VALUE)
    {
        void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        WriteProcessMemory(hProc, loc, path.c_str(), strlen(path.c_str()) + 1, 0);
        HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);
        if (hThread)
        {
            CloseHandle(hThread);
        }
    }
    if (hProc)
    {
        CloseHandle(hProc);
    }
}


void GetAllProfiles(std::string path)
{
    path = path.substr(0, path.find_last_of("/\\"));
    path = path + "\\Profiles\\";
    if (!std::filesystem::exists(path))
    {
        std::cout << "PROFILES FOLDER NOT FOUND!" << std::endl;
        Sleep(5000);
        exit(0);
    }
    else
    {
        std::cout << "PROFILES FOLDER FOUND!!!!" << std::endl;
        for (const auto& entry : std::filesystem::directory_iterator(path))
        {
            if (entry.path().extension().string() == ".profile")
            {
                std::wstring filename = entry.path().filename().wstring();
                std::string str(filename.begin(), filename.end());
                str = str.substr(0, str.find_last_of("."));
                GameProfiles.push_back(str);
            }
        }
    }
}

BOOL CALLBACK WindowEnumerationCallBack(HWND hwnd, LPARAM lParam) 
{
    int length = ::GetWindowTextLength(hwnd);
    if (!IsWindowVisible(hwnd) || length == 0) 
    {
        return TRUE;
    }
    DWORD dwProcId = 0;
    GetWindowThreadProcessId(hwnd, &dwProcId);
    HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcId);
    std::wstring EXEName;
    if (NULL != hProc)
    {
        HMODULE hMod;
        DWORD cbNeeded;
        TCHAR szEXEName[MAX_PATH];
        if (EnumProcessModules(hProc, &hMod,
            sizeof(hMod), &cbNeeded))
        {
            GetModuleBaseName(hProc, hMod, szEXEName,
                sizeof(szEXEName) / sizeof(TCHAR));

            EXEName = (szEXEName);
        }
    }
    CloseHandle(hProc);

    std::string strStd(EXEName.begin(), EXEName.end());
    strStd = strStd.substr(0, strStd.find_last_of("."));
    for (int i = 0; i < GameProfiles.size(); i++)
    {
        if (strStd == GameProfiles[i])
        {
            std::cout << "Found Game: " << GameProfiles[i] << std::endl;
            FoundGamepid = dwProcId;
        }
    }
    return TRUE;
}

void WaitingForUnrealWindow(std::string path)
{
    HWND hWnd = nullptr;
    bool WindowNotFound = true;
    std::cout << "Waiting for Game Window..." << std::endl;
    while (WindowNotFound)
    {
        EnumWindows(WindowEnumerationCallBack, (LPARAM)nullptr);
        if (FoundGamepid != 0)
        {
            WindowNotFound = false;
            path = path.substr(0, path.find_last_of("/\\"));
            path = path + "\\UnrealEngineModLoader.dll";
            InjectDLL(path);
        }
        Sleep(1000 / 60);
    }
}

int main(int argc, char* argv[])
{
    GetAllProfiles(std::string(argv[0]));
    WaitingForUnrealWindow(std::string(argv[0]));
    return 0;
}