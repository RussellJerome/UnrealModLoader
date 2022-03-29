#include "Class.h"
#include "../Memory/Memory.h"
namespace UE4
{
	UField* UField::GetNext() const
	{
		return UML::Memory::Read<UField*>((byte*)this + UML::GetGameInfo()->defs->UField.Next);
	};

	UStruct* UStruct::GetSuperField() const
	{
		return UML::Memory::Read<UStruct*>((byte*)this + UML::GetGameInfo()->defs->UStruct.SuperStruct);
	};

	UField* UStruct::GetChildren() const
	{
		return UML::Memory::Read<UField*>((byte*)this + UML::GetGameInfo()->defs->UStruct.Children);
	};

	int32_t UStruct::GetPropertySize() const
	{
		return UML::Memory::Read<int32_t>((byte*)this + UML::GetGameInfo()->defs->UStruct.PropertiesSize);
	};

	UClass* UClass::LoadClassFromString(const wchar_t* InName, bool bAllowObjectReconciliation)
	{
		return (UClass*)UObject::StaticLoadObject(UClass::StaticClass(), nullptr, InName, nullptr, 0, nullptr, bAllowObjectReconciliation);
	}

	int32_t UFunction::GetFunctionFlags() const
	{
		return UML::Memory::Read<int32_t>((byte*)this + UML::GetGameInfo()->defs->UFunction.FunctionFlags);
	};

	void* UFunction::GetFunction() const
	{
		return UML::Memory::Read<void*>((byte*)this + UML::GetGameInfo()->defs->UFunction.Func);
	};
};