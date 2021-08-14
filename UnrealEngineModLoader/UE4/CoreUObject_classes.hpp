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
		int32_t GetIndex() const { return Read<int32_t>((byte*)this + GameProfile::SelectedGameProfile.defs.UObject.Index); };
		UClass* GetClass() const { return Read<class UClass*>((byte*)this + GameProfile::SelectedGameProfile.defs.UObject.Class); };
		UObject* GetOuter() const { return Read<UObject*>((byte*)this + GameProfile::SelectedGameProfile.defs.UObject.Outer); };

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

		inline void ProcessEvent(class UFunction* function, void* parms)
		{
			return reinterpret_cast<void(*)(UObject*, class UFunction*, void*)>(GameProfile::SelectedGameProfile.ProcessEvent)(this, function, parms);
		}

		static inline UObject* StaticLoadObject(class UClass* uclass, UObject* InOuter, const wchar_t* InName, const wchar_t* Filename, unsigned int LoadFlags, void* Sandbox, bool bAllowObjectReconciliation)
		{
			return reinterpret_cast<UObject* (__fastcall*)(class UClass*, UObject*, const wchar_t*, const wchar_t*, unsigned int, void*, bool)>(GameProfile::SelectedGameProfile.StaticLoadObject)(uclass, InOuter, InName, Filename, LoadFlags, Sandbox, bAllowObjectReconciliation);
		}

		inline UObject* CallFunctionByNameWithArguments(const wchar_t* Str, void* Ar, UE4::UObject* Executor, bool bForceCallWithNonExec)
		{
			return reinterpret_cast<UE4::UObject*(*)(UE4::UObject*, const wchar_t*, void*, UE4::UObject*, bool)>(GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments)(this, Str, Ar, Executor, bForceCallWithNonExec);
		}

		void ExecuteUbergraph(int EntryPoint);
	};

	class UField : public UObject
	{
	public:
		UField* GetNext() const { return Read<UField*>((byte*)this + GameProfile::SelectedGameProfile.defs.UField.Next); };

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class CoreUObject.Field");
			return ptr;
		}

	};

	class UStruct : public UField
	{
	public:
		UStruct* GetSuperField() const { return Read<UStruct*>((byte*)this + GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct); };
		UField* GetChildren() const { return Read<UField*>((byte*)this + GameProfile::SelectedGameProfile.defs.UStruct.Children); };
		int32_t GetPropertySize() const { return Read<int32_t>((byte*)this + GameProfile::SelectedGameProfile.defs.UStruct.PropertiesSize); };
		
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

		static inline UClass* LoadClassFromString(const wchar_t* InName, bool bAllowObjectReconciliation)
		{
			return (UClass*)UObject::StaticLoadObject(UClass::StaticClass(), nullptr, InName, nullptr, 0, nullptr, bAllowObjectReconciliation);
		}

	};

	class UFunction : public UStruct
	{
	public:
		int32_t GetFunctionFlags() const { return Read<int32_t>((byte*)this + GameProfile::SelectedGameProfile.defs.UFunction.FunctionFlags); };
		void* GetFunction() const { return Read<void*>((byte*)this + GameProfile::SelectedGameProfile.defs.UFunction.Func); };
		
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class CoreUObject.Function");
			return ptr;
		}

	};

	class ULevel : public UObject
	{
	public:
		TArray<class AActor*> GetWorldActors() const { return Read<TArray<class AActor*>>((byte*)this + GameProfile::SelectedGameProfile.defs.ULevel.WorldArray); };

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.Level");
			return ptr;
		}
	};

	class ULevelStreaming : public UObject
	{
	public:

		struct FName GetWorldAssetPackageFName()
		{
			static auto fn = UObject::FindObject<UFunction>("Function Engine.LevelStreaming.GetWorldAssetPackageFName");
			struct
			{
				struct FName ReturnValue;
			}params;
			UObject::ProcessEvent(fn, &params);
			return params.ReturnValue;
		}

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.LevelStreaming");
			return ptr;
		}
	};

	class UWorld : public UObject
	{
	public:
		ULevel* GetPersistentLevel() const { return Read<ULevel*>((byte*)this + GameProfile::SelectedGameProfile.defs.UWorld.PersistentLevel); };
		class AGameModeBase* GetAuthorityGameMode() const { return Read<class AGameModeBase*>((byte*)this + GameProfile::SelectedGameProfile.defs.UWorld.AuthorityGameMode); };

		inline AActor* SpawnActor(UClass* uclass, const  FTransform* transform, const FActorSpawnParameters* params)
		{
			return reinterpret_cast<AActor* (*)(UWorld*, UClass*, const FTransform*, const FActorSpawnParameters*)>(GameProfile::SelectedGameProfile.SpawnActorFTrans)(this, uclass, transform, params);
		}

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

		FTransform GetTransform()
		{
			static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetTransform");
			struct
			{
				FTransform ReturnValue;
			}params;
			UObject::ProcessEvent(fn, &params);
			return params.ReturnValue;
		}

		FRotator GetActorRotation()
		{
			static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.K2_GetActorRotation");
			struct
			{
				FRotator ReturnValue;
			}params;
			UObject::ProcessEvent(fn, &params);
			return params.ReturnValue;
		}

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

		class AActor* BeginDeferredActorSpawnFromClass(class UClass* ActorClass, const struct FTransform& SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, class AActor* Owner)
		{
			static auto fn = UObject::FindObject<UFunction>("Function Engine.GameplayStatics.BeginDeferredActorSpawnFromClass");
			struct
			{
				class UObject* WorldContextObject;
				class UClass* ActorClass;
				struct FTransform SpawnTransform;
				ESpawnActorCollisionHandlingMethod CollisionHandlingOverride;
				class AActor* Owner;
				class AActor* ReturnValue;
			}params;
			params.WorldContextObject = UWorld::GetWorld();
			params.ActorClass = ActorClass;
			params.SpawnTransform = SpawnTransform;
			params.CollisionHandlingOverride = CollisionHandlingOverride;
			params.Owner = Owner;
			UObject::ProcessEvent(fn, &params);
			return params.ReturnValue;
		};

		class FString GetCurrentLevelName(bool bRemovePrefixString)
		{
			static auto fn = UObject::FindObject<UFunction>("Function Engine.GameplayStatics.GetCurrentLevelName");
			struct
			{
				class UObject* WorldContextObject;
				bool bRemovePrefixString;
				class FString ReturnValue;
			}params;
			params.WorldContextObject = UWorld::GetWorld();
			params.bRemovePrefixString = bRemovePrefixString;
			UObject::ProcessEvent(fn, &params);
			return params.ReturnValue;
		}

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
