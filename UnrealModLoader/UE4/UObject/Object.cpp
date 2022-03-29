#include "../Memory/Memory.h"
#include "Object.h"
#include "Class.h"
#include "NameType.h"

namespace UE4
{
	//Define Global Objects
	FUObjectArray* UObject::GObjects = nullptr;
	DWORD* FName::GNames = nullptr;

	int32_t UObject::GetIndex() const
	{
		return UML::Memory::Read<int32_t>((byte*)this + UML::GetGameInfo()->defs->UObject.Index);
	};

	UClass* UObject::GetClass() const
	{
		return UML::Memory::Read<class UClass*>((byte*)this + UML::GetGameInfo()->defs->UObject.Class);
	};

	UObject* UObject::GetOuter() const
	{
		return UML::Memory::Read<UObject*>((byte*)this + UML::GetGameInfo()->defs->UObject.Outer);
	};

	std::string UObject::GetName() const
	{
		auto Name = *reinterpret_cast<FName*>((byte*)this + UML::GetGameInfo()->defs->UObject.Name);
		std::string name(Name.GetName());
		if (Name.Number > 0)
		{
			name += '_' + std::to_string(Name.Number);
		}

		auto pos = name.rfind('/');
		if (pos == std::string::npos)
		{
			return name;
		}

		return name.substr(pos + 1);
	}

	std::string UObject::GetFullName() const
	{
		std::string name;
		auto Class = GetClass();
		if (Class != nullptr)
		{
			std::string temp;
			for (auto p = GetOuter(); p; p = p->GetOuter())
			{
				temp = p->GetName() + "." + temp;
			}

			name = Class->GetName();
			name += " ";
			name += temp;
			name += GetName();
		}

		return name;
	}

	bool UObject::IsA(UClass* cmp) const
	{
		for (auto super = GetClass(); super; super = static_cast<UClass*>(super->GetSuperField()))
		{
			if (super == cmp)
			{
				return true;
			}
		}

		return false;
	}

	void UObject::ExecuteUbergraph(int EntryPoint)
	{
		static auto fn = UObject::FindObject<UFunction>("Function CoreUObject.Object.ExecuteUbergraph");
		struct
		{
			int EntryPoint;
		}params;
		params.EntryPoint = EntryPoint;
		UObject::ProcessEvent(fn, &params);
	}

	bool UObject::DoesObjectContainFunction(std::string Function)
	{
		if (IsChunkedArray())
		{
			for (int i = 0; i < GObjects->GetAsChunckArray().Num(); ++i)
			{
				auto object = GObjects->GetAsChunckArray().GetByIndex(i).Object;

				if (object == nullptr)
				{
					continue;
				}

				if (object->GetName() == Function)
				{
					if (object->GetOuter() == this->GetClass())
					{
						return true;
					}
				}
			}
			return false;
		}
		else
		{
			for (int i = 0; i < GObjects->GetAsTUArray().Num(); ++i)
			{
				auto object = GObjects->GetAsTUArray().GetByIndex(i).Object;

				if (object == nullptr)
				{
					continue;
				}

				if (object->GetName() == Function)
				{
					if (object->GetOuter() == this->GetClass())
					{
						return true;
					}
				}
			}
			return false;
		}
		return false;
	}

	class UFunction* UObject::GetFunction(std::string Function)
	{
		if (IsChunkedArray())
		{
			for (int i = 0; i < GObjects->GetAsChunckArray().Num(); ++i)
			{
				auto object = GObjects->GetAsChunckArray().GetByIndex(i).Object;

				if (object == nullptr)
				{
					continue;
				}

				if (object->GetName() == Function)
				{
					if (object->GetOuter() == this->GetClass())
					{
						return (UFunction*)object;
					}
				}
			}
			return nullptr;
		}
		else
		{
			for (int i = 0; i < GObjects->GetAsTUArray().Num(); ++i)
			{
				auto object = GObjects->GetAsTUArray().GetByIndex(i).Object;

				if (object == nullptr)
				{
					continue;
				}

				if (object->GetName() == Function)
				{
					if (object->GetOuter() == this->GetClass())
					{
						return (UFunction*)object;
					}
				}
			}
			return nullptr;
		}
		return nullptr;
	}

	void UObject::ProcessEvent(class UFunction* function, void* parms)
	{
		return reinterpret_cast<void(*)(UObject*, class UFunction*, void*)>(UML::GetGameInfo()->ProcessEvent)(this, function, parms);
	}

	UObject* UObject::StaticLoadObject(class UClass* uclass, UObject* InOuter, const wchar_t* InName, const wchar_t* Filename, unsigned int LoadFlags, void* Sandbox, bool bAllowObjectReconciliation)
	{
		return reinterpret_cast<UObject * (__fastcall*)(class UClass*, UObject*, const wchar_t*, const wchar_t*, unsigned int, void*, bool)>(UML::GetGameInfo()->StaticLoadObject)(uclass, InOuter, InName, Filename, LoadFlags, Sandbox, bAllowObjectReconciliation);
	}

	//UObject* UObject::StaticConstructObject_Internal(UClass* Class, UObject* InOuter, FName Name, unsigned int SetFlags, EInternalObjectFlags InternalSetFlags, UObject* Template, bool bCopyTransientsFromClassDefaults, void* InstanceGraph, bool bAssumeTemplateIsArchetype)
	//{
	//	if (UML::GetGameInfo()->StaticConstructObject_Internal)
	//	{
	//		if (UML::GetGameInfo()->IsUsingUpdatedStaticConstruct)
	//		{
	//			FStaticConstructObjectParameters StaticConstructObjectParameters;
	//			StaticConstructObjectParameters.Class = Class;
	//			StaticConstructObjectParameters.Outer = InOuter;
	//			StaticConstructObjectParameters.Name = Name;
	//			StaticConstructObjectParameters.SetFlags = SetFlags;
	//			StaticConstructObjectParameters.InternalSetFlags = InternalSetFlags;
	//			StaticConstructObjectParameters.Template = Template;
	//			StaticConstructObjectParameters.bCopyTransientsFromClassDefaults = bCopyTransientsFromClassDefaults;
	//			StaticConstructObjectParameters.InstanceGraph = InstanceGraph;
	//			StaticConstructObjectParameters.bAssumeTemplateIsArchetype = bAssumeTemplateIsArchetype;
	//			return reinterpret_cast<UObject * (__fastcall*)(const FStaticConstructObjectParameters*)>(UML::GetGameInfo()->StaticConstructObject_Internal)(&StaticConstructObjectParameters);
	//		}
	//		else
	//		{
	//			return reinterpret_cast<UObject * (__fastcall*)(UClass*, UObject*, FName, unsigned int, unsigned int, UObject*, bool, void*, bool)>(UML::GetGameInfo()->StaticConstructObject_Internal)(Class, InOuter, Name, SetFlags, InternalSetFlags, Template, bCopyTransientsFromClassDefaults, InstanceGraph, bAssumeTemplateIsArchetype);
	//		}
	//	}
	//	else
	//	{
	//		//LOG_ERROR("StaticConstructObject_Internal Called But Not Found!");
	//	}
	//	return nullptr;
	//}

	bool UObject::CallFunctionByNameWithArguments(const wchar_t* Str, void* Ar, UE4::UObject* Executor, bool bForceCallWithNonExec)
	{
		return reinterpret_cast<bool (*)(UE4::UObject*, const wchar_t*, void*, UE4::UObject*, bool)>(UML::GetGameInfo()->CallFunctionByNameWithArguments)(this, Str, Ar, Executor, bForceCallWithNonExec);
	}
};