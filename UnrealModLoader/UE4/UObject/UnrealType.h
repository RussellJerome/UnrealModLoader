#pragma once
#include <string>

namespace UE4
{
	class FField
	{
	public:
		//FName* GetClass() const;
		FField* GetNext() const;
		std::string GetName() const;
	};

	class UEProperty
	{
	public:
		FField* GetParentFProperty();
		class UField* GetParentUProperty();
		int32_t GetArrayDim() const;
		//int32_t GetElementSize() const;
		int32_t GetOffset() const;
	};
};