#pragma once
#include <unordered_map>
#include <cstdint>
#include <string>
#include <Windows.h>

#pragma warning( disable : 4018 )

namespace UE4
{
	class FNamePoolFNameEntry
	{
	public:
		int16_t Key;

		union
		{
			char AnsiName[1024];
			wchar_t WideName[1024];
		};

		uint32_t GetLength() const
		{
			return Key >> 6;
		}

		bool IsWide() const
		{
			return Key & 1;
		}
		std::string GetAnsiName() const
		{
			auto len = GetLength();
			if (len > 1024) return "[Error: Overflow]";
			return std::string((const char*)AnsiName, len);
		}
		std::wstring GetWideName() const
		{
			auto len = GetLength();
			return std::wstring((const wchar_t*)WideName, len);
		}

		std::string GetName() const
		{
			return GetAnsiName();
		}
	};

	class FNamePoolFNameEntryAllocator
	{
	private:
		char frwLock[0x8];
	public:
		int32_t CurrentBlock;
		int32_t CurrentByteCursor;
		uint8_t* Blocks[8192];

		int32_t NumBlocks() const
		{
			return CurrentBlock + 1;
		}

		FNamePoolFNameEntry* GetById(int32_t key) const
		{
			uint32_t block = key >> 16;
			uint16_t offset = (uint16_t)key;

			if (!IsValidIndex(key, block, offset))
				return reinterpret_cast<FNamePoolFNameEntry*>(Blocks[0] + 0); // "None"

			return reinterpret_cast<FNamePoolFNameEntry*>(Blocks[block] + (offset * 2));
		}

		bool IsValidIndex(int32_t key) const
		{
			uint32_t block = key >> 16;
			uint16_t offset = key;
			return IsValidIndex(key, block, offset);
		}

		bool IsValidIndex(int32_t key, uint32_t block, uint16_t offset) const
		{
			return (key >= 0 && block < NumBlocks() && offset * 2 < 0x1FFFE);
		}
	};

	class FNamePool
	{
	public:
		FNamePoolFNameEntryAllocator Allocator;
		uint32_t AnsiCount;
		uint32_t WideCount;

		FNamePoolFNameEntry* GetNext(uint32_t& lastFNameId)
		{
			// Key		=> NameID
			// Value	=> StringLen
			static std::unordered_map<int, int> namesCache;
			const auto initLastFNameId = lastFNameId;
		RePlay:
			uint16_t block = lastFNameId >> 16;
			uint16_t nameOffset = (uint16_t)lastFNameId;
			uint32_t newOffset = 0;

			// We hit last Name in last Block
			if (block > Allocator.CurrentBlock)
				return nullptr;

			// If found lastId then add 2 to calc offset correct
			auto it = namesCache.find(lastFNameId);
			if (it != namesCache.end())
				newOffset += (nameOffset * 2) + 2 + it->second;

			if (newOffset >= 65535 * 2 || block == Allocator.CurrentBlock && newOffset >= Allocator.CurrentByteCursor)
			{
				lastFNameId = MAKELONG(0, block + 1);
				goto RePlay;
			}

			lastFNameId = MAKELONG(((unsigned short)(newOffset / 2)), block);

			uintptr_t entryOffset = reinterpret_cast<uintptr_t>(Allocator.Blocks[block]) + newOffset;

			unsigned short nameEntry = *reinterpret_cast<unsigned short*>(entryOffset);

			int nameLength = nameEntry >> 6;

			// if odd number (odd numbers are aligned with 0x00)
			if (nameLength % 2 != 0)
				nameLength += 1;

			// Cache
			namesCache.emplace(lastFNameId, nameLength);

			return Allocator.GetById(lastFNameId);
		}

		inline size_t Num() const
		{
			return AnsiCount;
		}

		inline bool IsValidIndex(int32_t id) const
		{
			return Allocator.IsValidIndex(static_cast<int32_t>(id));
		}

		inline FNamePoolFNameEntry* GetById(int32_t key) const
		{
			return Allocator.GetById(key);
		}

		inline FNamePoolFNameEntry* operator[](int32_t id) const
		{
			return Allocator.GetById(static_cast<int32_t>(id));
		}
	};
};