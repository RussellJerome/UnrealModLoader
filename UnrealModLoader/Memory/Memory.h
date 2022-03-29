#pragma once
#include <windows.h>
#include <cinttypes>

namespace UML
{
	namespace Memory
	{
		template<typename T>
		T Read(void* address)
		{
			return *reinterpret_cast<T*>((byte*)address);
		}
		uint8_t __declspec(noinline)* GetAddressPTR(uint8_t* ptr, uint8_t offset, uint8_t instr_size);
	};
};