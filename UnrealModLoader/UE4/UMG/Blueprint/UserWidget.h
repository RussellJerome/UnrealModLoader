#pragma once
#include "../Components/Widget.h"
#include "Engine/EngineBaseTypes.h"
namespace UE4
{
	class UUserWidget : public UWidget
	{
	public:
		void UnregisterInputComponent();
		void StopListeningForInputAction(const struct FName& ActionName, TEnumAsByte<EInputEvent> EventType);
		void StopListeningForAllInputActions();
		void StopAnimation(class UWidgetAnimation* InAnimation);
		void SetPositionInViewport(const struct FVector2D& Position, bool bRemoveDPIScale);
		void SetPlaybackSpeed(class UWidgetAnimation* InAnimation, float PlaybackSpeed);
		void SetPadding(const struct FMargin& InPadding);
		void SetOwningPlayer(class APlayerController* LocalPlayerController);
		void SetOwningLocalPlayer(class ULocalPlayer* LocalPlayer);
		void SetNumLoopsToPlay(class UWidgetAnimation* InAnimation, int NumLoopsToPlay);
		void SetInputActionPriority(int NewPriority);
		void SetInputActionBlocking(bool bShouldBlock);
		void SetForegroundColor(const struct FSlateColor& InForegroundColor);
		void SetDesiredSizeInViewport(const struct FVector2D& Size);
		void SetColorAndOpacity(const struct FLinearColor& InColorAndOpacity);
		void SetAnchorsInViewport(const struct FAnchors& Anchors);
		void SetAlignmentInViewport(const struct FVector2D& Alignment);
		void ReverseAnimation(class UWidgetAnimation* InAnimation);
		void RemoveFromViewport();
		void RegisterInputComponent();
		void PreConstruct(bool IsDesignTime);
		void PlaySoundBase(class USoundBase* SoundToPlay);
		void PlayAnimationTo(class UWidgetAnimation* InAnimation, float StartAtTime, float EndAtTime, int NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode> PlayMode, float PlaybackSpeed);
		void PlayAnimation(class UWidgetAnimation* InAnimation, float StartAtTime, int NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode> PlayMode, float PlaybackSpeed);
		float PauseAnimation(class UWidgetAnimation* InAnimation);
		bool IsPlayingAnimation();
		bool IsInViewport();
		bool IsInteractable();
		bool IsAnyAnimationPlaying();
		bool IsAnimationPlayingForward(class UWidgetAnimation* InAnimation);
		bool IsAnimationPlaying(class UWidgetAnimation* InAnimation);
		//class APawn* GetOwningPlayerPawn();
		//class ULocalPlayer* GetOwningLocalPlayer();
		bool GetIsVisible();
		float GetAnimationCurrentTime(class UWidgetAnimation* InAnimation);
		struct FAnchors GetAnchorsInViewport();
		struct FVector2D GetAlignmentInViewport();
		void Destruct();
		void Construct();
		void AddToViewport(int ZOrder);
		bool AddToPlayerScreen(int ZOrder);

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class UMG.UserWidget");
			return ptr;
		}
	};
};