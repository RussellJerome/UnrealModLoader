#pragma once
#include <GameInfo/GameInfo.h>
#include <Log/Log.h>
#ifdef ENABLE_GUI
#include <Shared/LoaderUI.h>
#endif
#include <UE4/Ue4.hpp>
#include <Utilities/Globals.h>
#include <string>

class LOADER_API Mod
{
  public:
    // Mod Default Variables
    std::string ModName;
    std::string ModVersion;
    std::string ModDescription;
    std::string ModAuthors;
    std::string ModLoaderVersion;
    // ModInternals
    bool IsFinishedCreating = 0;

    // Used Internally to setup Hook Event System
    void SetupHooks();

    // Called after each mod is injected, Looped through via gloabals
    virtual void InitializeMod();

    // InitGameState Call
    virtual void InitGameState();

    // Beginplay Hook of Every Actor
    virtual void BeginPlay(UE4::AActor *Actor);

    // PostBeginPlay of EVERY Blueprint ModActor
    virtual void PostBeginPlay(std::wstring ModActorName, UE4::AActor *Actor);

#ifdef ENABLE_GUI
    // DX11 hook for when an image will be presented to the screen
    virtual void DX11Present(ID3D11Device *pDevice, ID3D11DeviceContext *pContext,
                             ID3D11RenderTargetView *pRenderTargetView);

    // Call ImGui Here
    virtual void DrawImGui();
#endif

  protected:
    // Call to initialize the mod
    Mod(std::string &&ModName, std::string &&ModVersion, std::string &&ModDescription, std::string &&ModAuthors,
        std::string &&ModLoaderVersion);
};