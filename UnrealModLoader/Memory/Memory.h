#pragma once
#include <windows.h>
#include <cinttypes>
#include <cstdio>
#include <tchar.h>
#include <process.h>

namespace UML
{
	namespace Memory
	{
		bool Write(void* address, void* buffer, unsigned long long size);
		template<typename T>
		T Write(void* address, T buffer)
		{
			Write(address, &buffer, sizeof(T));
			return buffer;
			//*reinterpret_cast<T*>((byte*)address) = buffer;
			//return buffer;
		}
		bool Read(void* address, void* buffer, unsigned long long size);
		template<typename T>
		T Read(void* address)
		{
			T buffer{};
			Read(address, &buffer, sizeof(T));
			return buffer;
			//return *reinterpret_cast<T*>((byte*)address);
		}
		uint8_t __declspec(noinline)* GetAddressPTR(uint8_t* ptr, uint8_t offset, uint8_t instr_size);
	};
};