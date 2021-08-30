#pragma once
#include <windows.h>
#include <cstdio>
#include <cinttypes>
bool Read(void* address, void* buffer, unsigned long long size);

template<typename T>
T Read(void* address)
{
	T buffer{};
	Read(address, &buffer, sizeof(T));
	return buffer;
}
namespace MEM
{
	HWND FindWindow(DWORD pid, wchar_t const* className);

	uint8_t __declspec(noinline)* GetAddressPTR(uint8_t* ptr, uint8_t offset, uint8_t instr_size);
};