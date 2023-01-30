#include "mem.h"
#include <process.h>
#include <tchar.h>

bool Read(void *address, void *buffer, unsigned long long size)
{
    memcpy(buffer, address, size);
    return true;
}

bool Write(void *address, void *buffer, unsigned long long size)
{
    memcpy(address, buffer, size);
    return true;
}

namespace MEM
{
HWND FindWindow(DWORD pid, wchar_t const *className)
{
    HWND hCurWnd = GetTopWindow(0);
    while (hCurWnd != NULL)
    {
        DWORD cur_pid;
        DWORD dwTheardId = GetWindowThreadProcessId(hCurWnd, &cur_pid);

        if (cur_pid == pid)
        {
            if (IsWindowVisible(hCurWnd) != 0)
            {
                TCHAR szClassName[256];
                GetClassName(hCurWnd, szClassName, 256);
                if (_tcscmp(szClassName, className) == 0)
                {
                    return hCurWnd;
                }
            }
        }
        hCurWnd = GetNextWindow(hCurWnd, GW_HWNDNEXT);
    }
    return NULL;
}

uint8_t __declspec(noinline) * GetAddressPTR(uint8_t *ptr, uint8_t offset, uint8_t instr_size)
{
    return (ptr + *(int32_t *)(ptr + offset) + instr_size);
}
}; // namespace MEM