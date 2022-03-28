#pragma once
#include <unordered_set>
#include "NameEntryArray.h"
#include "NamePool.h"

namespace UE4
{
	class FName
	{
	public:
		int ComparisonIndex;
		int Number;

		inline FName()
			: ComparisonIndex(0),
			Number(0)
		{
		};

		inline FName(int i)
			: ComparisonIndex(i),
			Number(0)
		{
		};

		FName(const char* nameToFind)
			: ComparisonIndex(0),
			Number(0)
		{
			static std::unordered_set<int> cache;

			for (auto i : cache)
			{
				if (IsUsingNamePool())
				{
					if (!std::strcmp(GetFNamePool()[i]->GetAnsiName().c_str(), nameToFind))
					{
						ComparisonIndex = i;

						return;
					}
				}
				else
				{
					if (!std::strcmp(GetTNameArray()[i]->GetAnsiName(), nameToFind))
					{
						ComparisonIndex = i;

						return;
					}
				}
			}

			if (IsUsingNamePool())
			{
				for (auto i = 0; i < GetFNamePool().Num(); ++i)
				{
					if (GetFNamePool()[i] != nullptr)
					{
						if (!std::strcmp(GetFNamePool()[i]->GetAnsiName().c_str(), nameToFind))
						{
							cache.insert(i);

							ComparisonIndex = i;

							return;
						}
					}
				}
			}
			else
			{
				for (auto i = 0; i < GetTNameArray().Num(); ++i)
				{
					if (GetTNameArray()[i] != nullptr)
					{
						if (!std::strcmp(GetTNameArray()[i]->GetAnsiName(), nameToFind))
						{
							cache.insert(i);

							ComparisonIndex = i;

							return;
						}
					}
				}
			}

		};

		static DWORD* GNames;
		static inline DWORD& GetGlobalNames()
		{
			return *GNames;
		};

		static inline bool IsUsingNamePool()
		{
			return UML::GetGameInfo()->UsesFNamePool;
		};

		static inline TNameEntryArray& GetTNameArray()
		{
			return *(TNameEntryArray*)GNames;
		};

		static inline FNamePool& GetFNamePool()
		{
			return *(FNamePool*)GNames;
		};

		inline std::string GetName() const
		{
			if (IsUsingNamePool())
			{
				return GetFNamePool()[ComparisonIndex]->GetAnsiName();
			}
			else
			{
				return GetTNameArray()[ComparisonIndex]->GetAnsiName();
			}
		};

		inline bool operator==(const FName& other) const
		{
			return ComparisonIndex == other.ComparisonIndex;
		};
	};
};