#include "Class.h"

namespace UE4
{
	UField* UField::GetNext() const
	{
		return (UField*)this + UML::GetGameInfo()->defs->UField.Next;
	};

	UStruct* UStruct::GetSuperField() const
	{
		return (UStruct*)this + UML::GetGameInfo()->defs->UStruct.SuperStruct;
	};

	UField* UStruct::GetChildren() const
	{
		return (UField*)this + UML::GetGameInfo()->defs->UStruct.Children;
	};

	int32_t UStruct::GetPropertySize() const
	{
		return (int32_t)this + UML::GetGameInfo()->defs->UStruct.PropertiesSize;
	};

	UClass* UClass::LoadClassFromString(const wchar_t* InName, bool bAllowObjectReconciliation)
	{
		return (UClass*)UObject::StaticLoadObject(UClass::StaticClass(), nullptr, InName, nullptr, 0, nullptr, bAllowObjectReconciliation);
	}

	int32_t UFunction::GetFunctionFlags() const
	{
		return (int32_t)this + UML::GetGameInfo()->defs->UFunction.FunctionFlags;
	};

	void* UFunction::GetFunction() const
	{
		return (void*)(this + UML::GetGameInfo()->defs->UFunction.Func);
	};
};