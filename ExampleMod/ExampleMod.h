#pragma once
#include <Mod/Mod.h>

class ExampleMod : public Mod
{
  public:
    // Basic Mod Info
    ExampleMod() : Mod("ExampleMod", "1.0.0", "HAHAHAHA MOD GO BURR", "RussellJ", MODLOADER_VERSION)
    {
    }

    // Called When Internal Mod Setup is finished
    virtual void InitializeMod() override;

    // InitGameState Call
    virtual void InitGameState() override;

    // Beginplay Hook of Every Actor
    virtual void BeginPlay(UE4::AActor *Actor) override;

    // PostBeginPlay of EVERY Blueprint ModActor
    virtual void PostBeginPlay(std::wstring ModActorName, UE4::AActor *Actor) override;

#ifdef ENABLE_GUI
    // DX11 hook for when an image will be presented to the screen
    virtual void DX11Present(ID3D11Device *pDevice, ID3D11DeviceContext *pContext,
                             ID3D11RenderTargetView *pRenderTargetView) override;

    // Call ImGui Here (CALLED EVERY FRAME ON DX HOOK)
    virtual void DrawImGui() override;
#endif

  private:
    // If you have a BP Mod Actor, This is a straight refrence to it
    UE4::AActor *ModActor;
};