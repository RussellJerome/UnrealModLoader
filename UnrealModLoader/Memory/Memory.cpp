#include "Memory.h"
#include <tchar.h>
#include <process.h>

namespace UML
{
	namespace Memory
	{
		bool Read(void* address, void* buffer, unsigned long long size)
		{
			static auto hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, _getpid());
			return ReadProcessMemory(hProcess, address, buffer, size, nullptr);
		}
		bool Write(void* address, void* buffer, unsigned long long size)
		{
			static auto hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, _getpid());
			return WriteProcessMemory(hProcess, address, buffer, size, nullptr);
		}
		uint8_t __declspec(noinline)* GetAddressPTR(uint8_t* ptr, uint8_t offset, uint8_t instr_size)
		{
			return (ptr + *(int32_t*)(ptr + offset) + instr_size);
		}
	};
};