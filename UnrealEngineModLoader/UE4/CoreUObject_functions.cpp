#ifdef _MSC_VER
#pragma pack(push, 0x8)
#endif

#include "CoreUObject_parameters.hpp"
namespace UE4
{
//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// UObject Functions
//---------------------------------------------------------------------------

LOADER_API std::string UObject::GetName() const
{
    auto Name = *reinterpret_cast<FName *>((byte *)this + GameProfile::SelectedGameProfile.defs.UObject.Name);
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

LOADER_API std::string UObject::GetFullName() const
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

LOADER_API int32_t UObject::GetIndex() const
{
    return Read<int32_t>((byte *)this + GameProfile::SelectedGameProfile.defs.UObject.Index);
};

LOADER_API UClass *UObject::GetClass() const
{
    return Read<class UClass *>((byte *)this + GameProfile::SelectedGameProfile.defs.UObject.Class);
};

LOADER_API UObject *UObject::GetOuter() const
{
    return Read<UObject *>((byte *)this + GameProfile::SelectedGameProfile.defs.UObject.Outer);
};

LOADER_API bool UObject::IsA(UClass *cmp) const
{
    for (auto super = GetClass(); super; super = static_cast<UClass *>(super->GetSuperField()))
    {
        if (super == cmp)
        {
            return true;
        }
    }

    return false;
}

LOADER_API void UObject::ExecuteUbergraph(int EntryPoint)
{
    static auto fn = UObject::FindObject<UFunction>("Function CoreUObject.Object.ExecuteUbergraph");

    UObject_ExecuteUbergraph_Params params;
    params.EntryPoint = EntryPoint;

    // auto flags = fn->FunctionFlags;

    UObject::ProcessEvent(fn, &params);

    // fn->FunctionFlags = flags;
}

LOADER_API bool UObject::DoesObjectContainFunction(std::string Function)
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

LOADER_API class UFunction *UObject::GetFunction(std::string Function)
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
                    return (UFunction *)object;
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
                    return (UFunction *)object;
                }
            }
        }
        return nullptr;
    }
    return nullptr;
}

LOADER_API void UObject::ProcessEvent(class UFunction *function, void *parms)
{
    return reinterpret_cast<void (*)(UObject *, class UFunction *, void *)>(
        GameProfile::SelectedGameProfile.ProcessEvent)(this, function, parms);
}

LOADER_API UObject *UObject::StaticLoadObject(class UClass *uclass, UObject *InOuter, const wchar_t *InName,
                                              const wchar_t *Filename, unsigned int LoadFlags, void *Sandbox,
                                              bool bAllowObjectReconciliation)
{
    return reinterpret_cast<UObject *(__fastcall *)(class UClass *, UObject *, const wchar_t *, const wchar_t *,
                                                    unsigned int, void *, bool)>(
        GameProfile::SelectedGameProfile.StaticLoadObject)(uclass, InOuter, InName, Filename, LoadFlags, Sandbox,
                                                           bAllowObjectReconciliation);
}

LOADER_API UObject *UObject::StaticConstructObject_Internal(UClass *Class, UObject *InOuter, FName Name,
                                                            unsigned int SetFlags,
                                                            EInternalObjectFlags InternalSetFlags, UObject *Template,
                                                            bool bCopyTransientsFromClassDefaults, void *InstanceGraph,
                                                            bool bAssumeTemplateIsArchetype)
{
    if (GameProfile::SelectedGameProfile.StaticConstructObject_Internal)
    {
        if (GameProfile::SelectedGameProfile.IsUsingUpdatedStaticConstruct)
        {
            FStaticConstructObjectParameters StaticConstructObjectParameters;
            StaticConstructObjectParameters.Class = Class;
            StaticConstructObjectParameters.Outer = InOuter;
            StaticConstructObjectParameters.Name = Name;
            StaticConstructObjectParameters.SetFlags = SetFlags;
            StaticConstructObjectParameters.InternalSetFlags = InternalSetFlags;
            StaticConstructObjectParameters.Template = Template;
            StaticConstructObjectParameters.bCopyTransientsFromClassDefaults = bCopyTransientsFromClassDefaults;
            StaticConstructObjectParameters.InstanceGraph = InstanceGraph;
            StaticConstructObjectParameters.bAssumeTemplateIsArchetype = bAssumeTemplateIsArchetype;
            return reinterpret_cast<UObject *(__fastcall *)(const FStaticConstructObjectParameters *)>(
                GameProfile::SelectedGameProfile.StaticConstructObject_Internal)(&StaticConstructObjectParameters);
        }
        else
        {
            return reinterpret_cast<UObject *(__fastcall *)(UClass *, UObject *, FName, unsigned int, unsigned int,
                                                            UObject *, bool, void *, bool)>(
                GameProfile::SelectedGameProfile.StaticConstructObject_Internal)(
                Class, InOuter, Name, SetFlags, InternalSetFlags, Template, bCopyTransientsFromClassDefaults,
                InstanceGraph, bAssumeTemplateIsArchetype);
        }
    }
    else
    {
        Log::Error("StaticConstructObject_Internal Called But Not Found!");
    }
    return nullptr;
}

LOADER_API bool UObject::CallFunctionByNameWithArguments(const wchar_t *Str, void *Ar, UE4::UObject *Executor,
                                                         bool bForceCallWithNonExec)
{
    return reinterpret_cast<bool (*)(UE4::UObject *, const wchar_t *, void *, UE4::UObject *, bool)>(
        GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments)(this, Str, Ar, Executor,
                                                                          bForceCallWithNonExec);
}

//---------------------------------------------------------------------------
// UField Functions
//---------------------------------------------------------------------------

LOADER_API UField *UField::GetNext() const
{
    return Read<UField *>((byte *)this + GameProfile::SelectedGameProfile.defs.UField.Next);
};

//---------------------------------------------------------------------------
// UClass Functions
//---------------------------------------------------------------------------

LOADER_API UClass *UClass::LoadClassFromString(const wchar_t *InName, bool bAllowObjectReconciliation)
{
    return (UClass *)UObject::StaticLoadObject(UClass::StaticClass(), nullptr, InName, nullptr, 0, nullptr,
                                               bAllowObjectReconciliation);
}

//---------------------------------------------------------------------------
// UStruct Functions
//---------------------------------------------------------------------------

LOADER_API UStruct *UStruct::GetSuperField() const
{
    return Read<UStruct *>((byte *)this + GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct);
};

LOADER_API UField *UStruct::GetChildren() const
{
    return Read<UField *>((byte *)this + GameProfile::SelectedGameProfile.defs.UStruct.Children);
};

LOADER_API int32_t UStruct::GetPropertySize() const
{
    return Read<int32_t>((byte *)this + GameProfile::SelectedGameProfile.defs.UStruct.PropertiesSize);
};

//---------------------------------------------------------------------------
// UFunction Functions
//---------------------------------------------------------------------------

LOADER_API int32_t UFunction::GetFunctionFlags() const
{
    return Read<int32_t>((byte *)this + GameProfile::SelectedGameProfile.defs.UFunction.FunctionFlags);
};
LOADER_API void *UFunction::GetFunction() const
{
    return Read<void *>((byte *)this + GameProfile::SelectedGameProfile.defs.UFunction.Func);
};

//---------------------------------------------------------------------------
// UEProperty Functions
//---------------------------------------------------------------------------

LOADER_API int32_t UEProperty::GetArrayDim() const
{
    return Read<int32_t>((byte *)this + GameProfile::SelectedGameProfile.defs.Property.ArrayDim);
};
/*
int32_t UEProperty::GetElementSize() const
{
    return Read<int32_t>((byte*)this + GameProfile::SelectedGameProfile.defs.Property.ElementSize);
};
*/

LOADER_API int32_t UEProperty::GetOffset() const
{
    return Read<int32_t>((byte *)this + GameProfile::SelectedGameProfile.defs.Property.Offset);
};

//---------------------------------------------------------------------------
// FField Functions
//---------------------------------------------------------------------------

LOADER_API FField *FField::GetNext() const
{
    return Read<class FField *>((byte *)this + GameProfile::SelectedGameProfile.defs.FField.Next);
};

LOADER_API std::string FField::GetName() const
{
    auto Name = *reinterpret_cast<FName *>((byte *)this + GameProfile::SelectedGameProfile.defs.FField.Name);
    if (UE4::FName::GetFNamePool().IsValidIndex(Name.ComparisonIndex))
    {
        return Name.GetName();
    }
    return "nullptr";
};

//---------------------------------------------------------------------------
// UWorld Functions
//---------------------------------------------------------------------------

LOADER_API AActor *UWorld::SpawnActor(UClass *uclass, const FTransform *transform, const FActorSpawnParameters *params)
{
    return reinterpret_cast<AActor *(*)(UWorld *, UClass *, const FTransform *, const FActorSpawnParameters *)>(
        GameProfile::SelectedGameProfile.SpawnActorFTrans)(this, uclass, transform, params);
}

//---------------------------------------------------------------------------
// Actor Functions
//---------------------------------------------------------------------------

LOADER_API FTransform AActor::GetTransform()
{
    static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetTransform");
    struct
    {
        FTransform ReturnValue;
    } params;
    UObject::ProcessEvent(fn, &params);
    return params.ReturnValue;
}

LOADER_API FRotator AActor::GetActorRotation()
{
    static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.K2_GetActorRotation");
    struct
    {
        FRotator ReturnValue;
    } params;
    UObject::ProcessEvent(fn, &params);
    return params.ReturnValue;
}

LOADER_API FVector AActor::GetActorLocation()
{
    static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.K2_GetActorLocation");
    struct
    {
        FVector ReturnValue;
    } params;
    UObject::ProcessEvent(fn, &params);
    return params.ReturnValue;
}

LOADER_API FVector AActor::GetActorScale3D()
{
    static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetActorScale3D");
    struct
    {
        FVector ReturnValue;
    } params;
    UObject::ProcessEvent(fn, &params);
    return params.ReturnValue;
}

//---------------------------------------------------------------------------
// GameplayStatics Functions
//---------------------------------------------------------------------------

LOADER_API class AActor *UGameplayStatics::BeginDeferredActorSpawnFromClass(
    class UClass *ActorClass, const struct FTransform &SpawnTransform,
    ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, class AActor *Owner)
{
    static auto fn = UObject::FindObject<UFunction>("Function Engine.GameplayStatics.BeginDeferredActorSpawnFromClass");
    auto GameplayStatics = (UE4::UGameplayStatics *)UE4::UGameplayStatics::StaticClass()->CreateDefaultObject();
    struct
    {
        class UObject *WorldContextObject;
        class UClass *ActorClass;
        struct FTransform SpawnTransform;
        ESpawnActorCollisionHandlingMethod CollisionHandlingOverride;
        class AActor *Owner;
        class AActor *ReturnValue;
    } params;
    params.WorldContextObject = UWorld::GetWorld();
    params.ActorClass = ActorClass;
    params.SpawnTransform = SpawnTransform;
    params.CollisionHandlingOverride = CollisionHandlingOverride;
    params.Owner = Owner;
    GameplayStatics->UObject::ProcessEvent(fn, &params);
    return params.ReturnValue;
}

LOADER_API class FString UGameplayStatics::GetCurrentLevelName(bool bRemovePrefixString)
{
    static auto fn = UObject::FindObject<UFunction>("Function Engine.GameplayStatics.GetCurrentLevelName");
    // auto GameplayStatics = (UE4::UGameplayStatics*)UE4::UGameplayStatics::StaticClass()->CreateDefaultObject();
    auto GameplayStatics =
        UE4::UObject::GetDefaultObjectFromArray<UE4::UGameplayStatics>(UE4::UGameplayStatics::StaticClass());
    struct
    {
        class UObject *WorldContextObject;
        bool bRemovePrefixString;
        class FString ReturnValue;
    } params;
    params.WorldContextObject = UWorld::GetWorld();
    params.bRemovePrefixString = bRemovePrefixString;
    GameplayStatics->UObject::ProcessEvent(fn, &params);
    return params.ReturnValue;
}

LOADER_API class AGameState *UGameplayStatics::GetGameState()
{
    static auto fn = UObject::FindObject<UFunction>("Function Engine.GameplayStatics.GetGameState");
    auto GameplayStatics = (UE4::UGameplayStatics *)UE4::UGameplayStatics::StaticClass()->CreateDefaultObject();
    struct UGameplayStatics_GetGameState_Params
    {
        class UObject *WorldContextObject;
        class AGameState *ReturnValue;
    } params;
    params.WorldContextObject = UWorld::GetWorld();
    GameplayStatics->ProcessEvent(fn, &params);
    return params.ReturnValue;
}

LOADER_API class AGameMode *UGameplayStatics::GetGameMode()
{
    static auto fn = UObject::FindObject<UFunction>("Function Engine.GameplayStatics.GetGameMode");
    auto GameplayStatics = (UE4::UGameplayStatics *)UE4::UGameplayStatics::StaticClass()->CreateDefaultObject();
    struct
    {
        class UObject *WorldContextObject;
        class AGameMode *ReturnValue;
    } params;
    params.WorldContextObject = UWorld::GetWorld();
    GameplayStatics->ProcessEvent(fn, &params);
    return params.ReturnValue;
}

LOADER_API class UGameInstance *UGameplayStatics::GetGameInstance()
{
    static auto fn = UObject::FindObject<UFunction>("Function Engine.GameplayStatics.GetGameInstance");
    auto GameplayStatics = (UE4::UGameplayStatics *)UE4::UGameplayStatics::StaticClass()->CreateDefaultObject();
    struct
    {
        class UObject *WorldContextObject;
        class UGameInstance *ReturnValue;
    } params;
    params.WorldContextObject = UWorld::GetWorld();
    GameplayStatics->ProcessEvent(fn, &params);
    return params.ReturnValue;
}

LOADER_API class APawn *UGameplayStatics::GetPlayerPawn(int PlayerIndex)
{
    static auto fn = UObject::FindObject<UFunction>("Function Engine.GameplayStatics.GetPlayerPawn");
    auto GameplayStatics = (UE4::UGameplayStatics *)UE4::UGameplayStatics::StaticClass()->CreateDefaultObject();
    struct
    {
        class UObject *WorldContextObject;
        int PlayerIndex;
        class APawn *ReturnValue;
    } params;
    params.WorldContextObject = UWorld::GetWorld();
    params.PlayerIndex = PlayerIndex;
    GameplayStatics->ProcessEvent(fn, &params);
    return params.ReturnValue;
}

LOADER_API class APlayerController *UGameplayStatics::GetPlayerController(int PlayerIndex)
{
    static auto fn = UObject::FindObject<UFunction>("Function Engine.GameplayStatics.GetPlayerController");
    auto GameplayStatics = (UE4::UGameplayStatics *)UE4::UGameplayStatics::StaticClass()->CreateDefaultObject();
    struct
    {
        class UObject *WorldContextObject;
        int PlayerIndex;
        class APlayerController *ReturnValue;
    } params;

    params.WorldContextObject = UWorld::GetWorld();
    params.PlayerIndex = PlayerIndex;
    GameplayStatics->ProcessEvent(fn, &params);
    return params.ReturnValue;
}

LOADER_API void UGameplayStatics::ExecuteConsoleCommand(const class FString &Command,
                                                        class APlayerController *SpecificPlayer)
{
    static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetSystemLibrary.ExecuteConsoleCommand");
    auto GameplayStatics = (UE4::UGameplayStatics *)UE4::UGameplayStatics::StaticClass()->CreateDefaultObject();
    struct
    {
        class UObject *WorldContextObject;
        class FString Command;
        class APlayerController *SpecificPlayer;
    } params;
    params.WorldContextObject = UWorld::GetWorld();
    params.Command = Command;
    params.SpecificPlayer = SpecificPlayer;
    GameplayStatics->ProcessEvent(fn, &params);
}

} // namespace UE4

#ifdef _MSC_VER
#pragma pack(pop)
#endif
