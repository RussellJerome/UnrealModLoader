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
				CoreModLoader::LoadCoreMods();
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
				if (CurrentModActor->IsA(UE4::AActor::StaticClass()))
				{
					CurrentModActor->CallFunctionByNameWithArguments(L"ModCleanUp", nullptr, NULL, true);
				}
				Global::ModInfoList[i].CurrentModActor = nullptr;
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
										if (GameProfile::SelectedGameProfile.UsesFNamePool)
										{
											DWORD64 ProcessAddy = (DWORD64)Pattern::Find("41 F6 C7 02 74 10 4C 8B C7 48 8B D5 48 8B CB E8 ? ? ? ? EB 79");
											auto ProcessAddyOffset = *reinterpret_cast<uint32_t*>(ProcessAddy + 16);
											GameProfile::SelectedGameProfile.ProcessInternals = (ProcessAddy + 20 + ProcessAddyOffset);
										}
										else
										{
											if (ModActor->DoesObjectContainFunction("PostBeginPlay"))
											{
												GameProfile::SelectedGameProfile.ProcessInternals = (DWORD64)ModActor->GetFunction("PostBeginPlay")->GetFunction();
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
												Global::ModInfoList[i].WasInitialized = true;
											}
										}
									}
									ModActor->CallFunctionByNameWithArguments(L"PreBeginPlay", nullptr, NULL, true);
									Log::Info("Sucessfully Loaded %s", str);
								}
							}
							else
							{
								Log::Info("Could not locate ModActor for %s", str);
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

	HRESULT hookResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
	{
		return LoaderUI::GetUI()->LoaderResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
	}

	HRESULT(*D3D11Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	HRESULT __stdcall hookD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		LoaderUI::GetUI()->LoaderD3D11Present(pSwapChain, SyncInterval, Flags);
		return D3D11Present(pSwapChain, SyncInterval, Flags);
	}

	DWORD __stdcall InitDX11Hook(LPVOID)
	{
		Log::Info("Setting up D3D11Present hook");

		HMODULE hDXGIDLL = 0;
		do
		{
			hDXGIDLL = GetModuleHandle(L"dxgi.dll");
			Sleep(100);
		} while (!hDXGIDLL);
		Sleep(100);

		IDXGISwapChain* pSwapChain;

		WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DefWindowProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
		RegisterClassExA(&wc);

		HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);

		D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
		D3D_FEATURE_LEVEL obtainedLevel;
		ID3D11Device* d3dDevice = nullptr;
		ID3D11DeviceContext* d3dContext = nullptr;

		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(scd));
		scd.BufferCount = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		scd.OutputWindow = hWnd;
		scd.SampleDesc.Count = 1;
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		scd.Windowed = ((GetWindowLongPtr(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;

		scd.BufferDesc.Width = 1;
		scd.BufferDesc.Height = 1;
		scd.BufferDesc.RefreshRate.Numerator = 0;
		scd.BufferDesc.RefreshRate.Denominator = 1;

		UINT createFlags = 0;
#ifdef _DEBUG
		createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		IDXGISwapChain* d3dSwapChain = 0;

		if (FAILED(D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			createFlags,
			requestedLevels,
			sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL),
			D3D11_SDK_VERSION,
			&scd,
			&pSwapChain,
			&LoaderUI::GetUI()->pDevice,
			&obtainedLevel,
			&LoaderUI::GetUI()->pContext)))
		{
			Log::Error("Failed to create D3D device and swapchain");
			return NULL;
		}

		LoaderUI::GetUI()->pSwapChainVtable = (DWORD_PTR*)pSwapChain;
		LoaderUI::GetUI()->pSwapChainVtable = (DWORD_PTR*)LoaderUI::GetUI()->pSwapChainVtable[0];
		LoaderUI::GetUI()->phookD3D11Present = (LoaderUI::D3D11PresentHook)LoaderUI::GetUI()->pSwapChainVtable[8];
		MinHook::Add((DWORD64)LoaderUI::GetUI()->phookD3D11Present, &hookD3D11Present, &D3D11Present, "DX11");
		MinHook::Add((DWORD64)LoaderUI::GetUI()->pSwapChainVtable[13], &hookResizeBuffers, &LoaderUI::GetUI()->ResizeBuffers, "DX11");

		DWORD dPresentwOld;
		DWORD dResizeOld;
		VirtualProtect(LoaderUI::GetUI()->phookD3D11Present, 2, PAGE_EXECUTE_READWRITE, &dPresentwOld);
		VirtualProtect((LPVOID)LoaderUI::GetUI()->pSwapChainVtable[13], 2, PAGE_EXECUTE_READWRITE, &dResizeOld);

		while (true)
		{
			Sleep(10);
		}

		LoaderUI::GetUI()->pDevice->Release();
		LoaderUI::GetUI()->pContext->Release();
		pSwapChain->Release();
		return NULL;
	}

	DWORD __stdcall InitHooks(LPVOID)
	{
		MinHook::Init();
		Log::Info("MinHook Setup");
		PakLoader::ScanLoadedPaks();
		Log::Info("ScanLoadedPaks Setup");
		MinHook::Add(GameProfile::SelectedGameProfile.GameStateInit, &HookedFunctions::hookInitGameState, &HookedFunctions::origInitGameState, "AGameModeBase::InitGameState");
		MinHook::Add(GameProfile::SelectedGameProfile.BeginPlay, &HookedFunctions::hookBeginPlay, &HookedFunctions::origBeginPlay, "AActor::BeginPlay");
		CreateThread(NULL, 0, InitDX11Hook, NULL, 0, NULL);
		return NULL;
	}

	void SetupHooks()
	{
		Log::Info("Setting Up Loader");
		CreateThread(0, 0, InitHooks, 0, 0, 0);
		Dumper::BeginKeyThread();
	}
};