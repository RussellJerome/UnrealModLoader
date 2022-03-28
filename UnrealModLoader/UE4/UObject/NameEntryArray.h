#pragma once
#include "../UnrealModLoader.h"

#pragma warning( disable : 4200 )
#pragma warning( disable : 4311 )
#pragma warning( disable : 4302 )

class FNameEntry
{
public:
	inline const char* GetAnsiName() const
	{
		return (char*)this + (UML::GetGameInfo()->IsUsing4_22 ? 0xC : 0x10);
	}
};

class TNameEntryArray
{
public:
	inline int Num() const
	{
		return GetNumElements();
	}

	inline bool IsValidIndex(int Index) const
	{
		return Index < Num() && Index >= 0;
	}

	inline FNameEntry const* const& operator[](int Index) const
	{
		return *GetItemPtr(Index);
	}

private:
	inline FNameEntry const* const* GetItemPtr(int Index) const
	{
		auto ChunkIndex = Index / 16384;
		auto WithinChunkIndex = Index % 16384;
		auto Chunk = Chunks[ChunkIndex];
		return Chunk + WithinChunkIndex;
	}
	int GetNumElements() const
	{
		return (int)this + 0x8 + 0x4;
	};
	FNameEntry** Chunks[];
};