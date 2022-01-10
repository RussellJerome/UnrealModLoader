#include "Hooks.h"
#include "Utilities/MinHook.h"
#include "GameInfo/GameInfo.h"
#include "PakLoader.h"
#include "Utilities/Dumper.h"
#include "Memory/mem.h"
#include "UnrealEngineModLoader/Utilities/Globals.h"
#include "UnrealEngineModLoader/Memory/CoreModLoader.h"
#include "UE4/Ue4.hpp"
#include "LoaderUI.h"
bool bIsProcessInternalsHooked = false;
bool GameStateClassInitNotRan = true;

namespace Hooks
{
	namespace HookedFunctions
	{
		struct PrintStringParams
		{
			UE4::FString Message;
		};

		struct GetPersistentObject
		{
			UE4::FString ModName;
		};

		PVOID(*origProcessFunction)(UE4::UObject*, UE4::FFrame*, void* const);
		PVOID hookProcessFunction(UE4::UObject* obj, UE4::FFrame* Frame, void* const Result)
		{
			if (!GameStateClassInitNotRan)
			{
				if (Frame->Node->GetName() == "PrintToModLoader")
				{
					auto msg = Frame->GetParams<PrintStringParams>()->Message;
					if (msg.IsValid())
					{
						Log::Print("%s", msg.ToString().c_str());
					}
				}
				if (Frame->Node->GetName() == "GetPersistentObject")
				{
					auto ModName = Frame->GetParams<GetPersistentObject>()->ModName;
					for (size_t i = 0; i < Global::ModInfoList.size(); i++)
					{
						auto ModInfo = Global::ModInfoList[i];
						if (ModName.c_str() == ModInfo.ModName)
						{
							if (ModInfo.PersistentObject)
							{
								UE4::SetVariable<UE4::UObject*>(obj, "GetPersistentObjectReturnValue", ModInfo.PersistentObject);
							}
						}
					}
				}
				Global::eventSystem.dispatchEvent("ProcessFunction", obj, Frame);
			}
			return origProcessFunction(obj, Frame, Result);

		}

		PVOID(*origInitGameState)(void*);
		PVOID hookInitGameState(void* Ret)
		{
			Log::Info("GameStateHook");
			if (GameStateClassInitNotRan)
			{
				UE4::InitSDK();
				Log::Info("Engine Classes Loaded");
				if (Global::CoreMods.size() > 0)
				{
					for (size_t i = 0; i < Global::CoreMods.size(); i++)
					{
						auto CurrentCoreMod = Global::CoreMods[i];
						if (CurrentCoreMod->IsFinishedCreating)
						{
							Log::Info("InitializeMod Called For %s", CurrentCoreMod->ModName.c_str());
							CurrentCoreMod->InitializeMod();
						}
						else
						{
							Log::Error("Mod %s wasnt setup in time"), CurrentCoreMod->ModName;
						}
					}
				}

				UE4::FTransform transform = UE4::FTransform::FTransform();
				UE4::FActorSpawnParameters spawnParams = UE4::FActorSpawnParameters::FActorSpawnParameters();
				if (GameProfile::SelectedGameProfile.StaticLoadObject)
				{
					Log::Info("StaticLoadObject Found");
				}
				else
				{
					Log::Error("StaticLoadObject Not Found");
				}
				GameStateClassInitNotRan = false;
			}
			for (int i = 0; i < Global::ModInfoList.size(); i++)
			{
				UE4::AActor* CurrentModActor = Global::ModInfoList[i].CurrentModActor;
				if (CurrentModActor)
				{
					if (CurrentModActor->IsA(UE4::AActor::StaticClass()))
					{
						CurrentModActor->CallFunctionByNameWithArguments(L"ModCleanUp", nullptr, NULL, true);
					}
				}
				
				Global::ModInfoList[i].CurrentModActor = nullptr;
				Global::ModInfoList[i].ModButtons.clear();
			}
			if (GameProfile::SelectedGameProfile.StaticLoadObject)
			{
				UE4::FTransform transform;
				transform.Translation = UE4::FVector(0, 0, 0);
				transform.Rotation = UE4::FQuat(0, 0, 0, 0);
				transform.Scale3D = UE4::FVector(1, 1, 1);
				UE4::FActorSpawnParameters spawnParams = UE4::FActorSpawnParameters::FActorSpawnParameters();
				for (int i = 0; i < Global::ModInfoList.size(); i++)
				{
					std::wstring CurrentMod;
					//StartSpawningMods
					CurrentMod = Global::ModInfoList[i].ModName;
					if (Global::ModInfoList[i].IsEnabled)
					{
						if (GameProfile::SelectedGameProfile.StaticLoadObject)
						{
							std::string str(CurrentMod.begin(), CurrentMod.end());
							const std::wstring Path = L"/Game/Mods/" + CurrentMod + L"/ModActor.ModActor_C";
							UE4::UClass* ModObject = UE4::UClass::LoadClassFromString(Path.c_str(), false);
							if (ModObject)
							{
								UE4::AActor* ModActor = nullptr;
								if (!GameProfile::SelectedGameProfile.IsUsingDeferedSpawn)
								{
									ModActor = UE4::UWorld::GetWorld()->SpawnActor(ModObject, &transform, &spawnParams);
								}
								else
								{
									ModActor = UE4::UGameplayStatics::BeginDeferredActorSpawnFromClass(ModObject, transform, UE4::ESpawnActorCollisionHandlingMethod::AlwaysSpawn, nullptr);
								}
								if (ModActor)
								{
									if (!bIsProcessInternalsHooked)
									{
										if (!GameProfile::SelectedGameProfile.ProcessInternals)
										{
											if (!GameProfile::SelectedGameProfile.UsesFNamePool || !GameProfile::SelectedGameProfile.IsUsing4_22)
											{
												if (ModActor->DoesObjectContainFunction("PostBeginPlay"))
												{
													GameProfile::SelectedGameProfile.ProcessInternals = (DWORD64)ModActor->GetFunction("PostBeginPlay")->GetFunction();
												}
												else if (ModActor->DoesObjectContainFunction("ModMenuButtonPressed"))
												{
													GameProfile::SelectedGameProfile.ProcessInternals = (DWORD64)ModActor->GetFunction("ModMenuButtonPressed")->GetFunction();
												}
											}
										}
										bIsProcessInternalsHooked = true;
										if (GameProfile::SelectedGameProfile.ProcessInternals)
											MinHook::Add(GameProfile::SelectedGameProfile.ProcessInternals, &HookedFunctions::hookProcessFunction, &HookedFunctions::origProcessFunction, "ProcessBlueprintFunctions");
										else
											Log::Warn("ProcessBlueprintFunctions could not be located! Mod Loader Functionality Will be Limited!");
									}

									for (size_t i = 0; i < Global::ModInfoList.size(); i++)
									{
										if (Global::ModInfoList[i].ModName == CurrentMod)
										{
											Global::ModInfoList[i].CurrentModActor = ModActor;
											if (!Global::ModInfoList[i].WasInitialized)
											{
												Global::ModInfoList[i].ContainsButton = ModActor->DoesObjectContainFunction("ModMenuButtonPressed");
												UE4::FString Author;
												UE4::FString Description;
												UE4::FString Version;
												if (UE4::GetVariable<UE4::FString>(ModActor, "ModAuthor", Author))
												{
													if (Author.IsValid())
													{
														Global::ModInfoList[i].ModAuthor = Author.ToString();
													}
												}
												if (UE4::GetVariable<UE4::FString>(ModActor, "ModDescription", Description))
												{
													if (Description.IsValid())
													{
														Global::ModInfoList[i].ModDescription = Description.ToString();
													}
												}
												if (UE4::GetVariable<UE4::FString>(ModActor, "ModVersion", Version))
												{
													if (Version.IsValid())
													{
														Global::ModInfoList[i].ModVersion = Version.ToString();
													}
												}
												const std::wstring ModInstancePath = L"/Game/Mods/" + CurrentMod + L"/ModInstanceObject.ModInstanceObject_C";
												UE4::UClass* ModObjectInstanceClass = UE4::UClass::LoadClassFromString(ModInstancePath.c_str(), false);
												if (ModObjectInstanceClass)	// Check if ModInstanceObject Exists
												{
													Global::ModInfoList[i].PersistentObject = UE4::UObject::StaticConstructObject_Internal(ModObjectInstanceClass, UE4::UGameplayStatics::GetGameInstance(), "", 0, UE4::EInternalObjectFlags::GarbageCollectionKeepFlags, nullptr, false, nullptr, false);
												}
												Global::ModInfoList[i].WasInitialized = true;
											}
										}
									}
									ModActor->CallFunctionByNameWithArguments(L"PreBeginPlay", nullptr, NULL, true);
									Log::Info("Sucessfully Loaded %s", str.c_str());
								}
							}
							else
							{
								Log::Info("Could not locate ModActor for %s", str.c_str());
							}
						}
					}
				}
				Log::Info("Finished Spawning PakMods");
				Global::eventSystem.dispatchEvent("InitGameState");
			}
			Log::Info("Returning to GameState --------------------------------------------------------");
			return origInitGameState(Ret);
		}

		PVOID(*origBeginPlay)(UE4::AActor*);
		PVOID hookBeginPlay(UE4::AActor* Actor)
		{
			if (!GameStateClassInitNotRan)
			{
				if (Actor->IsA(UE4::ACustomClass::StaticClass(GameProfile::SelectedGameProfile.BeginPlayOverwrite)))
				{
					Log::Info("Beginplay Called");
					for (int i = 0; i < Global::ModInfoList.size(); i++)
					{
						UE4::AActor* CurrentModActor = Global::ModInfoList[i].CurrentModActor;
						if (CurrentModActor != nullptr)
						{
							UE4::TArray<UE4::FString> ModButtons;
							if (UE4::GetVariable<UE4::TArray<UE4::FString>>(CurrentModActor, "ModButtons", ModButtons))
							{
								for (size_t bi = 0; bi < ModButtons.Num(); bi++)
								{
									auto CurrentButton = ModButtons[bi];
									if (CurrentButton.IsValid())
									{
										Global::ModInfoList[i].ModButtons.push_back(CurrentButton.ToString());
									}
								}
							}
							CurrentModActor->CallFunctionByNameWithArguments(L"PostBeginPlay", nullptr, NULL, true);
							Global::eventSystem.dispatchEvent("PostBeginPlay", Global::ModInfoList[i].ModName, CurrentModActor);
						}
					}
				}
				Global::eventSystem.dispatchEvent("BeginPlay", Actor);
			}
			return origBeginPlay(Actor);
		}
	};

	DWORD __stdcall InitHooks(LPVOID)
	{
		MinHook::Init();
		Log::Info("MinHook Setup");
		Log::Info("Loading Core Mods");
		CoreModLoader::LoadCoreMods();
		Sleep(10);
		PakLoader::ScanLoadedPaks();
		Log::Info("ScanLoadedPaks Setup");
		MinHook::Add(GameProfile::SelectedGameProfile.GameStateInit, &HookedFunctions::hookInitGameState, &HookedFunctions::origInitGameState, "AGameModeBase::InitGameState");
		MinHook::Add(GameProfile::SelectedGameProfile.BeginPlay, &HookedFunctions::hookBeginPlay, &HookedFunctions::origBeginPlay, "AActor::BeginPlay");
		LoaderUI::GetUI()->CreateUILogicThread();
		if (!GameProfile::SelectedGameProfile.bDelayGUISpawn)
		{
			LoaderUI::HookDX();
		}
		return NULL;
	}

	void SetupHooks()
	{
		Log::Info("Setting Up Loader");
		CreateThread(0, 0, InitHooks, 0, 0, 0);
	}
};