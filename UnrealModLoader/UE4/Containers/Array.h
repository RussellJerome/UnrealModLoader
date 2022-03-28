#pragma once
/*
TODO
====
Rewrite array to use FMemory Allocators
*/
namespace UE4
{
	template<class T>
	class TArray
	{
		friend class FString;

	public:
		inline TArray()
		{
			Data = nullptr;
			Count = Max = 0;
		};

		inline int Num() const
		{
			return Count;
		};

		inline T& operator[](int i)
		{
			return Data[i];
		};

		inline const T& operator[](int i) const
		{
			return Data[i];
		};

		void Add(T InputData)
		{
			Data = (T*)realloc(Data, sizeof(T) * (Count + 1));
			Data[Count++] = InputData;
			Max = Count;
		};

		inline bool IsValidIndex(int i) const
		{
			return i < Num();
		}

	public:
		T* Data;
		int Count;
		int Max;
	};
};