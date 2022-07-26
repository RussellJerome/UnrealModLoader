#pragma once
#include "Object.h"
#include "UnrealType.h"
#include "../Memory/Memory.h"

namespace UE4
{
	class UField : public UObject
	{
	public:
		UField* GetNext() const;

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class CoreUObject.Field");
			return ptr;
		}
	};

	class UStruct : public UField
	{
	public:
		UStruct* GetSuperField() const;
		UField* GetChildren() const;
		int32_t GetPropertySize() const;

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class CoreUObject.Struct");
			return ptr;
		}
	};

	class UClass : public UStruct
	{
	public:
		template<typename T>
		inline T* CreateDefaultObject()
		{
			return static_cast<T*>(CreateDefaultObject());
		}

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class CoreUObject.Class");
			return ptr;
		}

		inline UObject* CreateDefaultObject()
		{
			return reinterpret_cast<UObject * (*)(UClass*)>(this, UML::GetGameInfo()->CreateDefaultObject)(this);
		}

		static UClass* LoadClassFromString(const wchar_t* InName, bool bAllowObjectReconciliation);
	};

	class UFunction : public UStruct
	{
	public:
		int32_t GetFunctionFlags() const;
		void* GetFunction() const;

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class CoreUObject.Function");
			return ptr;
		}
	};

	template<typename T>
	bool SetVariable(UObject* Object, std::string Name, T Value)
	{
		UClass* ObjectClass = Object->GetClass();
		if (UML::GetGameInfo()->bIsFProperty)
		{
			auto Children = (FField*)ObjectClass->GetChildren();
			bool VarFound = false;
			while (!VarFound)
			{
				if (!Children)
					break;
				if (Children->GetName() == Name)
				{
					VarFound = true;
					auto varProperty = (UEProperty*)Children;
					UML::Memory::Write<T>((byte*)Object + varProperty->GetOffset(), Value);
					return true;
				}
				Children = Children->GetNext();
			}

		}
		else
		{
			auto Children = (UField*)ObjectClass->GetChildren();
			bool VarFound = false;
			while (!VarFound)
			{
				if (!Children)
					break;
				if (Children->GetName() == Name)
				{
					VarFound = true;
					auto varProperty = (UEProperty*)Children;

					UML::Memory::Write<T>((byte*)Object + varProperty->GetOffset(), Value);
					return true;
				}
				Children = Children->GetNext();
			}
		}
		return false;
	}
};