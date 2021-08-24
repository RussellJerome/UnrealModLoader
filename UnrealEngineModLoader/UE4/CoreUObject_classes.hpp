#pragma once

#ifdef _MSC_VER
#pragma pack(push, 0x8)
#endif

#include "CoreUObject_structs.hpp"
#include "GameInfo/GameInfo.h"
#include "Memory/mem.h"

namespace UE4
{
	//---------------------------------------------------------------------------
	//Classes
	//---------------------------------------------------------------------------

	class UObject
	{
	public:
		static FUObjectArray* GObjects;
		int32_t GetIndex() const;
		UClass* GetClass() const;
		UObject* GetOuter() const;

		static inline bool IsChunkedArray()
		{
			return GameProfile::SelectedGameProfile.IsUsingFChunkedFixedUObjectArray;
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
					auto object = GObjects->GetAsChunckArray().GetByIndex(i).Object;

					if (object == nullptr)
					{
						continue;
					}

					if (object->GetFullName() == name)
					{
						return static_cast<T*>(object);
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
						return static_cast<T*>(object);
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

		void ProcessEvent(class UFunction* function, void* parms);

		static UObject* StaticLoadObject(class UClass* uclass, UObject* InOuter, const wchar_t* InName, const wchar_t* Filename, unsigned int LoadFlags, void* Sandbox, bool bAllowObjectReconciliation);

		bool CallFunctionByNameWithArguments(const wchar_t* Str, void* Ar, UE4::UObject* Executor, bool bForceCallWithNonExec);

		void ExecuteUbergraph(int EntryPoint);
	};

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
			return reinterpret_cast<UObject*(*)(UClass*)>(this, GameProfile::SelectedGameProfile.CreateDefualtObject)(this);
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

	class ULevel : public UObject
	{
	public:
		TArray<class AActor*> GetWorldActors() const;

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.Level");
			return ptr;
		}
	};

	class UWorld : public UObject
	{
	public:
		ULevel* GetPersistentLevel() const;
		//class AGameModeBase* GetAuthorityGameMode() const { return Read<class AGameModeBase*>((byte*)this + GameProfile::SelectedGameProfile.defs.UWorld.AuthorityGameMode); };

		AActor* SpawnActor(UClass* uclass, const  FTransform* transform, const FActorSpawnParameters* params);

		static UWorld** GWorld;
		static inline UWorld* GetWorld()
		{
			return *GWorld;
		};

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.World");
			return ptr;
		}
	};

	class AActor : public UObject
	{
	public:

		FTransform GetTransform();

		FRotator GetActorRotation();

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.Actor");
			return ptr;
		}
	};

	class APlayerController : public AActor
	{
	public:
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.PlayerController");
			return ptr;
		}
	};

	class AGameModeBase : public AActor
	{
	public:
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.GameModeBase");
			return ptr;
		}
	};

	class ACustomClass : public UObject
	{
	public:
		static UClass* StaticClass(std::string Class)
		{
			static auto ptr = UObject::FindClass(Class);
			return ptr;
		}
	};

	class UBlueprintFunctionLibrary : public UObject
	{
	public:
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.BlueprintFunctionLibrary");
			return ptr;
		}
	};

	class UGameplayStatics : public UBlueprintFunctionLibrary
	{
	public:

		class AActor* BeginDeferredActorSpawnFromClass(class UClass* ActorClass, const struct FTransform& SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, class AActor* Owner);

		class FString GetCurrentLevelName(bool bRemovePrefixString);

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.GameplayStatics");
			return ptr;
		}
	};
}

#ifdef _MSC_VER
#pragma pack(pop)
#endif
