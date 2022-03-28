#pragma once
#include "Object.h"

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
};