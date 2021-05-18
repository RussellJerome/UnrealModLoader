#include <iostream>
#include<Windows.h>
#include <string>
#include  <filesystem>

uint32_t pid = 0;
void InjectDLL(std::string path)
{
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
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

std::string string_to_hex(const std::string& input)
{
    static const char hex_digits[] = "0123456789ABCDEF";

    std::string output;
    output.reserve(input.length() * 2);
    for (unsigned char c : input)
    {
        output.push_back(hex_digits[c >> 4]);
        output.push_back(hex_digits[c & 15]);
    }
    return output;
}

HWND WaitingForUnrealWindow()
{
    HWND hWnd = nullptr;
    bool WindowNotFound = true;
    std::cout << "Waiting for Game Window..." << std::endl;
    while (WindowNotFound)
    {
        LPSTR Test[MAX_PATH] = {0};
        hWnd = FindWindowA("UnrealWindow", nullptr);
        if (hWnd != nullptr)
        {
            std::wstring title(GetWindowTextLength(hWnd) + 1, L'\0');
            GetWindowTextW(hWnd, &title[0], title.size());
            std::string str(title.begin(), title.end());
            auto EpicString = string_to_hex(str);
            if (EpicString != "457069632047616D6573204C61756E6368657200")
            {
                if (EpicString != "00")
                {
                    std::cout << "Game Found" << std::endl;
                    WindowNotFound = false;
                }
            }
        }
        Sleep(1000 / 60);
    }
    return hWnd;
}

int main(int argc, char* argv[])
{
    GetWindowThreadProcessId(WaitingForUnrealWindow(), (DWORD*)(&pid));
    std::string path = std::string(argv[0]);
    path = path.substr(0, path.find_last_of("/\\"));
    path = path + "\\UnrealEngineModLoader.dll";
    InjectDLL(path);
    return 0;
}