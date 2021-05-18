#pragma once
#include <windows.h>

bool Read(void* address, void* buffer, unsigned long long size);

template<typename T>
T Read(void* address)
{
	T buffer{};
	Read(address, &buffer, sizeof(T));
	return buffer;
}