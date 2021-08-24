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

namespace Hooks
{
	namespace HookedFunctions
	{
		bool GameStateClassInitNotRan = true;
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
					UE4::UClass* ModActorObject = UE4::UClass::LoadClassFromString(L"/Game/ModLoaderContent/ModLoaderActor.ModLoaderActor_C", false);
					if (ModActorObject)
					{
						Log::Info("Sucessfully Loaded ModLoader Pak");
						if (!GameProfile::SelectedGameProfile.IsUsingDeferedSpawn)
						{
							Global::ModLoaderActor = UE4::UWorld::GetWorld()->SpawnActor(ModActorObject, &transform, &spawnParams);
						}
						else
						{
							auto Gameplay = (UE4::UGameplayStatics*)UE4::UGameplayStatics::StaticClass()->CreateDefaultObject();
							Global::ModLoaderActor = Gameplay->BeginDeferredActorSpawnFromClass(ModActorObject, transform, UE4::ESpawnActorCollisionHandlingMethod::AlwaysSpawn, nullptr);
						}

					}
					else
					{
						Log::Warn("ModLoader Pak Not Found");
					}
				}
				else
				{
					Log::Error("StaticLoadObject Not Found");
				}
				GameStateClassInitNotRan = false;
			}
			for (int i = 0; i < Global::ModInfo.size(); i++)
			{
				UE4::AActor* CurrentModActor = Global::ModInfo[i].CurrentModActor;
				if (CurrentModActor->IsA(UE4::AActor::StaticClass()))
				{
					CurrentModActor->CallFunctionByNameWithArguments(L"ModCleanUp", nullptr, NULL, true);
				}
				Global::ModInfo[i].CurrentModActor = nullptr;
			}
			//Global::ModActors.clear();
			if (Global::ModLoaderActor->IsA(UE4::AActor::StaticClass()))
			{
				Global::ModLoaderActor->CallFunctionByNameWithArguments(L"CleanLoader", nullptr, NULL, true);
			}
			if (GameProfile::SelectedGameProfile.StaticLoadObject)
			{
				UE4::FTransform transform;
				transform.Translation = UE4::FVector(0, 0, 0);
				transform.Rotation = UE4::FQuat(0, 0, 0, 0);
				transform.Scale3D = UE4::FVector(1, 1, 1);
				UE4::FActorSpawnParameters spawnParams = UE4::FActorSpawnParameters::FActorSpawnParameters();
				for (int i = 0; i < Global::ModInfo.size(); i++)
				{
					std::wstring CurrentMod;
					//StartSpawningMods
					CurrentMod = Global::ModInfo[i].ModName;
					if (Global::ModInfo[i].IsEnabled)
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
									auto Gameplay = (UE4::UGameplayStatics*)UE4::UGameplayStatics::StaticClass()->CreateDefaultObject();
									ModActor = Gameplay->BeginDeferredActorSpawnFromClass(ModObject, transform, UE4::ESpawnActorCollisionHandlingMethod::AlwaysSpawn, nullptr);
								}
								if (ModActor)
								{
									for (size_t i = 0; i < Global::ModInfo.size(); i++)
									{
										if (Global::ModInfo[i].ModName == CurrentMod)
										{
											Global::ModInfo[i].CurrentModActor = ModActor;
											if (!Global::ModInfo[i].WasInitialized)
											{
												Global::ModInfo[i].ContainsButton = ModActor->DoesObjectContainFunction("ModMenuButtonPressed");
												//std::cout << str << ": " << Global::ModInfo[i].ContainsButton << std::endl;
												Global::ModInfo[i].WasInitialized = true;
											}
										}
									}
									//Global::ModActors.push_back(ModActor);
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
					Global::ModLoaderActor->CallFunctionByNameWithArguments(L"PostLoaderStart", nullptr, NULL, true);
					for (int i = 0; i < Global::ModInfo.size(); i++)
					{
						UE4::AActor* CurrentModActor = Global::ModInfo[i].CurrentModActor;
						if (CurrentModActor != nullptr)
						{
							CurrentModActor->CallFunctionByNameWithArguments(L"PostBeginPlay", nullptr, NULL, true);
						}
					}
				}
			}
			return origBeginPlay(Actor);
		}

		PVOID(*origSay)(void*, UE4::FString*);
		PVOID hookSay(void* GM, UE4::FString* Message)
		{
			Log::Info("Hook Say Called");
			std::wstring WStrMsg = Message->c_str();
			if (WStrMsg.substr(WStrMsg.length() - 6, 6) == L"/Print") // check if message ends with /Print
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				WStrMsg = WStrMsg.substr(0, WStrMsg.length() - 6); // remove /Print extension
				std::string str(WStrMsg.begin(), WStrMsg.end());
				SetConsoleTextAttribute(hConsole, 13);
				std::cout << "Print: " << str << std::endl;
				SetConsoleTextAttribute(hConsole, 7);
			}
			return origSay(GM, Message);
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
		/*
		Log::Info("BaseAddr:               0x%" PRIXPTR, (DWORD_PTR)GetModuleHandle(NULL));
		Log::Info("SwapChain:              0x%" PRIXPTR, pSwapChain);
		Log::Info("SwapChainVtable:        0x%" PRIXPTR, LoaderUI::GetUI()->pSwapChainVtable);
		Log::Info("Device:                 0x%" PRIXPTR, LoaderUI::GetUI()->pDevice);
		Log::Info("DeviceContext:          0x%" PRIXPTR, LoaderUI::GetUI()->pContext);
		Log::Info("D3D11Present:           0x%" PRIXPTR, LoaderUI::GetUI()->pSwapChainVtable[8]);
		*/
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

	UE4::FString*(*origPrintfImpl)(void*, wchar_t*, int);
	UE4::FString* hookPrintfImpl(void* a1, wchar_t* a2, int args)
	{
		//UE4::FString* Tester = (UE4::FString*)a1;
		//std::cout << Tester->ToString() << std::endl;
		//Log::Info("Hook Say Called");
		//std::wstring string((wchar_t*) a1);
		//std::string str(string.begin(), string.end());
		/*
		auto result = origPrintfImpl(a1, a2, args);
		if (result->IsValid() && result->Count <= result->Max)
		{
			std::cout << result << std::endl;
			std::cout << result->ToString() << std::endl;
			/*
			if (result->c_str() == L"CUNT")
			{
				std::cout << result->ToString() << std::endl;
			}
			*/
			//if (result.ToString() == "CUNT")
			//{
				//Log::Info("CUNT FOUND");
			//}
		//}
		return origPrintfImpl(a1, a2, args);
	}

	DWORD __stdcall InitHooks(LPVOID)
	{
		MinHook::Init();
		Log::Info("MinHook Setup");
		PakLoader::ScanLoadedPaks();
		Log::Info("ScanLoadedPaks Setup");
		MinHook::Add(GameProfile::SelectedGameProfile.GameStateInit, &HookedFunctions::hookInitGameState, &HookedFunctions::origInitGameState, "AGameModeBase::InitGameState");
		MinHook::Add(GameProfile::SelectedGameProfile.BeginPlay, &HookedFunctions::hookBeginPlay, &HookedFunctions::origBeginPlay, "AActor::BeginPlay");
		MinHook::Add(GameProfile::SelectedGameProfile.Say, &HookedFunctions::hookSay, &HookedFunctions::origSay, "AGameMode::Say");

		//MinHook::Add((DWORD64)Pattern::Find("4C 8B DC 49 89 53 10 4D 89 43 18 4D 89 4B 20 53 55 56 57 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B DA 48 8D 7C 24 ? 48 8B F1 49 8D 6B 18 41 BE ? ? ? ? E8 ? ? ? ? 48 89 6C 24 ? 45 8D 46 FF 33 ED 48 8D 54 24 ? ") , &hookPrintfImpl, &origPrintfImpl, "FString::PrintfImpl");
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