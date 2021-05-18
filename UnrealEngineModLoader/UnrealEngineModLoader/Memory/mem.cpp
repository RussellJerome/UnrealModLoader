#include "mem.h"
#include <process.h>

bool Read(void* address, void* buffer, unsigned long long size)
{
	auto hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, _getpid());
	return ReadProcessMemory(hProcess, address, buffer, size, nullptr);
}