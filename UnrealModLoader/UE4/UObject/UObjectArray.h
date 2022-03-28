#pragma once
#include <Windows.h>

namespace UE4
{
	class UObject;

	class FUObjectItem
	{
	public:
		UObject* Object;
		int Flags;
		int ClusterRootIndex;
		int SerialNumber;
	};

	class TUObjectArray
	{
	public:
		inline int Num() const
		{
			return NumElements;
		}

		inline FUObjectItem const& GetByIndex(int Index) const
		{
			return Objects[Index];
		}

		class FUObjectItem* Objects;
		int MaxElements;
		int NumElements;
	};

	class FChunkedFixedUObjectArray
	{
	public:
		inline int Num() const
		{
			return NumElements;
		}

		inline FUObjectItem const* GetObjectPtr(int Index) const
		{
			auto ElementsPerChunk = MaxElements / MaxChunks;
			auto ChunkIndex = Index / ElementsPerChunk;
			auto WithinChunkIndex = Index % ElementsPerChunk;
			auto Chunk = Objects[ChunkIndex];
			return Chunk + WithinChunkIndex;
		}

		inline FUObjectItem const& GetByIndex(int Index) const
		{
			return *GetObjectPtr(Index);
		}

	private:
		class FUObjectItem** Objects;
		class FUObjectItem* PreAllocatedObjects;
		int MaxElements;
		int NumElements;
		int MaxChunks;
		int NumChunks;
	};

	class FUObjectArray
	{
	public:
		int ObjFirstGCIndex;
		int ObjLastNonGCIndex;
		int MaxObjectsNotConsideredByGC;
		bool OpenForDisregardForGC;
		DWORD ObjObjects;

		inline class TUObjectArray GetAsTUArray() const
		{
			return (TUObjectArray&)ObjObjects;
		}

		inline class FChunkedFixedUObjectArray GetAsChunckArray() const
		{
			return (FChunkedFixedUObjectArray&)ObjObjects;
		}
	};
};