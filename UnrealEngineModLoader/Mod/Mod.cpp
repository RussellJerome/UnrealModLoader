#include "Mod.h"
#include "Utilities/MinHook.h"
#include "Utilities/Version.h"

void Mod::InitGameState()
{
}

void Mod::OnModMenuButtonPressed()
{
}

void Mod::BeginPlay(UE4::AActor *Actor)
{
}

void Mod::PostBeginPlay(std::wstring ModActorName, UE4::AActor *Actor)
{
}

void Mod::DX11Present(ID3D11Device *pDevice, ID3D11DeviceContext *pContext, ID3D11RenderTargetView *pRenderTargetView)
{
}

void Mod::DrawImGui()
{
}

void Mod::SetupHooks()
{
    Global::GetGlobals()->eventSystem.registerEvent(
        new Event<UE4::AActor *>("BeginPlay", [&](auto *Actor) { this->BeginPlay(Actor); }));

    Global::GetGlobals()->eventSystem.registerEvent(new Event<>("InitGameState", [&]() { this->InitGameState(); }));

    Global::GetGlobals()->eventSystem.registerEvent(new Event<std::wstring, UE4::AActor *>(
        "PostBeginPlay", [&](auto Name, auto *Actor) { this->PostBeginPlay(Name, Actor); }));

    Global::GetGlobals()->eventSystem.registerEvent(new Event<>("DrawImGui", [&]() { this->DrawImGui(); }));

    Global::GetGlobals()->eventSystem.registerEvent(
        new Event<ID3D11Device *, ID3D11DeviceContext *, ID3D11RenderTargetView *>(
            "DX11Present", [&](auto *pDevice, auto *pContext, auto *pRenderTargetView) {
                this->DX11Present(pDevice, pContext, pRenderTargetView);
            }));
}

void Mod::CompleteModCreation()
{
    IsFinishedCreating = true;
    Global::GetGlobals()->AddToCoreMods(this);
    LOG_INFO("Core Mod Created: {}", ModName.c_str());
    if (ModLoaderVersion != MODLOADER_VERSION)
    {
        LOG_WARN("Mod: {} was created with a different version of the Unreal Mod Loader. This mod may be unstable.",
                 ModName.c_str());
    }
}

void Mod::InitializeMod()
{
}