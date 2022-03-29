#pragma once
#include <string>
#include <vector>
#include "UObjectArray.h"
#include "../UnrealModLoader.h"

namespace UE4
{
	class UObject
	{
	public:
		static FUObjectArray* GObjects;
		int32_t GetIndex() const;
		class UClass* GetClass() const;
		class UObject* GetOuter() const;

		static inline bool IsChunkedArray()
		{
			return UML::GetGameInfo()->IsUsingFChunkedFixedUObjectArray;
		}

		std::string GetName() const;

		std::string GetFullName() const;

		template<typename T>
		static T* FindObject(const std::string& name)
		{
			if (IsChunkedArray())
			{
				for (int i = 0; i < GObjects->GetAsChunckArray().Num(); ++i)
				{
					UE4::UObject* object = GObjects->GetAsChunckArray().GetByIndex(i).Object;

					if (object == nullptr)
					{
						continue;
					}

					if (object->GetFullName() == name)
					{
						return (T*)object;
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

					if (object->GetFullName() == name)
					{
						return (T*)object;
					}
				}
				return nullptr;
			}
		}

		template<typename T>
		static std::vector<T*> GetAllObjectsOfType(UClass* Class, bool filterDefualts)
		{
			if (IsChunkedArray())
			{
				std::vector<T*> ret;
				//auto v = T::StaticClass();
				for (int i = 0; i < GObjects->GetAsChunckArray().Num(); ++i)
				{
					auto object = GObjects->GetAsChunckArray().GetByIndex(i).Object;

					if (object == nullptr)
					{
						continue;
					}

					if (object->IsA(Class))
					{
						if (filterDefualts)
						{
							if (object->GetName().find("Default__") != std::string::npos) {
								continue;
							}
						}
						ret.push_back(static_cast<T*>(object));
					}
				}
				return ret;
			}
			else
			{
				std::vector<T*> ret;
				for (int i = 0; i < GObjects->GetAsTUArray().Num(); ++i)
				{
					auto object = GObjects->GetAsTUArray().GetByIndex(i).Object;

					if (object == nullptr)
					{
						continue;
					}

					if (object->IsA(Class))
					{
						if (filterDefualts)
						{
							if (object->GetName().find("Default__") != std::string::npos) {
								continue;
							}
						}
						ret.push_back(static_cast<T*>(object));
					}
				}
				return ret;
			}
		}

		template<typename T>
		static T* GetDefaultObjectFromArray(UClass* Class)
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

					if (object->IsA(Class))
					{
						if (object->GetName().find("Default__") != std::string::npos)
						{
							return static_cast<T*>(object);
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

					if (object->IsA(Class))
					{
						if (object->GetName().find("Default__") != std::string::npos)
						{
							return static_cast<T*>(object);
						}
					}
				}
				return nullptr;
			}
		}

		static UClass* FindClass(const std::string& name)
		{
			return FindObject<UClass>(name);
		}

		bool IsA(UClass* cmp) const;

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class CoreUObject.Object");
			return ptr;
		}

		bool DoesObjectContainFunction(std::string Function);

		class UFunction* GetFunction(std::string Function);

		void ProcessEvent(class UFunction* function, void* parms);

		static UObject* StaticLoadObject(class UClass* uclass, UObject* InOuter, const wchar_t* InName, const wchar_t* Filename, unsigned int LoadFlags, void* Sandbox, bool bAllowObjectReconciliation);

		//static class UObject* StaticConstructObject_Internal(class UClass* Class, class UObject* InOuter, class FName Name, unsigned int SetFlags, EInternalObjectFlags InternalSetFlags, class UObject* Template, bool bCopyTransientsFromClassDefaults, void* InstanceGraph, bool bAssumeTemplateIsArchetype);

		bool CallFunctionByNameWithArguments(const wchar_t* Str, void* Ar, UE4::UObject* Executor, bool bForceCallWithNonExec);

		void ExecuteUbergraph(int EntryPoint);
	};
};