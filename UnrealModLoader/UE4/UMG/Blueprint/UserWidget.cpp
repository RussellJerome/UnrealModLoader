#include "UserWidget.h"
#include "UObject/NameType.h"
#include "Math/Vector2D.h"
#include "SlateCore/Layout/Margin.h"
#include "SlateCore/Styling/SlateColor.h"
#include "UMG/Slate/Anchors.h"
#include "UMG/Animation/WidgetAnimation.h"

namespace UE4
{
	void UUserWidget::UnregisterInputComponent()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.UnregisterInputComponent");
		struct
		{
		}params;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::StopListeningForInputAction(const FName& ActionName, TEnumAsByte<EInputEvent> EventType)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.StopListeningForInputAction");
		struct
		{
			FName ActionName;
			TEnumAsByte<EInputEvent> EventType;
		}params;
		params.ActionName = ActionName;
		params.EventType = EventType;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::StopListeningForAllInputActions()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.StopListeningForAllInputActions");
		struct
		{
		}params;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::StopAnimation(UWidgetAnimation* InAnimation)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.StopAnimation");
		struct
		{
			UWidgetAnimation* InAnimation;
		}params;
		params.InAnimation = InAnimation;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::SetPositionInViewport(const FVector2D& Position, bool bRemoveDPIScale)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetPositionInViewport");
		struct
		{
			FVector2D Position;
			bool bRemoveDPIScale;
		}params;
		params.Position = Position;
		params.bRemoveDPIScale = bRemoveDPIScale;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::SetPlaybackSpeed(UWidgetAnimation* InAnimation, float PlaybackSpeed)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetPlaybackSpeed");
		struct
		{
			UWidgetAnimation* InAnimation;
			float PlaybackSpeed;
		}params;
		params.InAnimation = InAnimation;
		params.PlaybackSpeed = PlaybackSpeed;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::SetPadding(const FMargin& InPadding)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetPadding");
		struct
		{
			FMargin InPadding;
		}params;
		params.InPadding = InPadding;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::SetOwningPlayer(APlayerController* LocalPlayerController)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetOwningPlayer");
		struct
		{
			APlayerController* LocalPlayerController;
		}params;
		params.LocalPlayerController = LocalPlayerController;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::SetOwningLocalPlayer(ULocalPlayer* LocalPlayer)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetOwningLocalPlayer");
		struct
		{
			ULocalPlayer* LocalPlayer;
		}params;
		params.LocalPlayer = LocalPlayer;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::SetNumLoopsToPlay(UWidgetAnimation* InAnimation, int NumLoopsToPlay)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetNumLoopsToPlay");
		struct
		{
			UWidgetAnimation* InAnimation;
			int NumLoopsToPlay;
		}params;
		params.InAnimation = InAnimation;
		params.NumLoopsToPlay = NumLoopsToPlay;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::SetInputActionPriority(int NewPriority)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetInputActionPriority");
		struct
		{
			int NewPriority;
		}params;
		params.NewPriority = NewPriority;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::SetInputActionBlocking(bool bShouldBlock)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetInputActionBlocking");
		struct
		{
			bool bShouldBlock;
		}params;
		params.bShouldBlock = bShouldBlock;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::SetForegroundColor(const FSlateColor& InForegroundColor)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetForegroundColor");
		struct
		{
			FSlateColor InForegroundColor;
		}params;
		params.InForegroundColor = InForegroundColor;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::SetDesiredSizeInViewport(const FVector2D& Size)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetDesiredSizeInViewport");
		struct
		{
			FVector2D Size;
		}params;
		params.Size = Size;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::SetColorAndOpacity(const FLinearColor& InColorAndOpacity)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetColorAndOpacity");
		struct
		{
			FLinearColor InColorAndOpacity;
		}params;
		params.InColorAndOpacity = InColorAndOpacity;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::SetAnchorsInViewport(const FAnchors& Anchors)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetAnchorsInViewport");
		struct
		{
			FAnchors Anchors;
		}params;
		params.Anchors = Anchors;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::SetAlignmentInViewport(const FVector2D& Alignment)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetAlignmentInViewport");
		struct
		{
			FVector2D Alignment;
		}params;
		params.Alignment = Alignment;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::ReverseAnimation(UWidgetAnimation* InAnimation)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.ReverseAnimation");
		struct
		{
			UWidgetAnimation* InAnimation;
		}params;
		params.InAnimation = InAnimation;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::RemoveFromViewport()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.RemoveFromViewport");
		struct
		{
		}params;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::RegisterInputComponent()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.RegisterInputComponent");
		struct
		{
		}params;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::PreConstruct(bool IsDesignTime)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.PreConstruct");
		struct
		{
			bool IsDesignTime;
		}params;
		params.IsDesignTime = IsDesignTime;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::PlaySoundBase(USoundBase* SoundToPlay)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.PlaySound");
		struct 
		{
			USoundBase* SoundToPlay;
		}params;
		params.SoundToPlay = SoundToPlay;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::PlayAnimationTo(UWidgetAnimation* InAnimation, float StartAtTime, float EndAtTime, int NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode> PlayMode, float PlaybackSpeed)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.PlayAnimationTo");
		struct
		{
			UWidgetAnimation* InAnimation;
			float StartAtTime;
			float EndAtTime;
			int NumLoopsToPlay;
			TEnumAsByte<EUMGSequencePlayMode> PlayMode;
			float PlaybackSpeed;
		}params;
		params.InAnimation = InAnimation;
		params.StartAtTime = StartAtTime;
		params.EndAtTime = EndAtTime;
		params.NumLoopsToPlay = NumLoopsToPlay;
		params.PlayMode = PlayMode;
		params.PlaybackSpeed = PlaybackSpeed;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::PlayAnimation(UWidgetAnimation* InAnimation, float StartAtTime, int NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode> PlayMode, float PlaybackSpeed)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.PlayAnimation");
		struct
		{
			UWidgetAnimation* InAnimation;
			float StartAtTime;
			int NumLoopsToPlay;
			TEnumAsByte<EUMGSequencePlayMode> PlayMode;
			float PlaybackSpeed;
		}params;
		params.InAnimation = InAnimation;
		params.StartAtTime = StartAtTime;
		params.NumLoopsToPlay = NumLoopsToPlay;
		params.PlayMode = PlayMode;
		params.PlaybackSpeed = PlaybackSpeed;
		UObject::ProcessEvent(fn, &params);
	}
	float UUserWidget::PauseAnimation(UWidgetAnimation* InAnimation)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.PauseAnimation");
		struct
		{
			UWidgetAnimation* InAnimation;
			bool ReturnValue;
		}params;
		params.InAnimation = InAnimation;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	bool UUserWidget::IsPlayingAnimation()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.IsPlayingAnimation");
		struct
		{
			bool ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	bool UUserWidget::IsInViewport()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.IsInViewport");
		struct
		{
			bool ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	bool UUserWidget::IsInteractable()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.IsInteractable");
		struct
		{
			bool ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	bool UUserWidget::IsAnyAnimationPlaying()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.IsAnyAnimationPlaying");
		struct
		{
			bool ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	bool UUserWidget::IsAnimationPlayingForward(UWidgetAnimation* InAnimation)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.IsAnimationPlayingForward");
		struct
		{
			UWidgetAnimation* InAnimation;
			bool ReturnValue;
		}params;
		params.InAnimation = InAnimation;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	bool UUserWidget::IsAnimationPlaying(UWidgetAnimation* InAnimation)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.IsAnimationPlaying");
		struct
		{
			UWidgetAnimation* InAnimation;
			bool ReturnValue;
		}params;
		params.InAnimation = InAnimation;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	bool UUserWidget::GetIsVisible()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.GetIsVisible");
		struct
		{
			bool ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	float UUserWidget::GetAnimationCurrentTime(UWidgetAnimation* InAnimation)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.GetAnimationCurrentTime");
		struct
		{
			UWidgetAnimation* InAnimation;
			bool ReturnValue;
		}params;
		params.InAnimation = InAnimation;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	FAnchors UUserWidget::GetAnchorsInViewport()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.GetAnchorsInViewport");
		struct
		{
			FAnchors ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	FVector2D UUserWidget::GetAlignmentInViewport()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.GetAlignmentInViewport");
		struct
		{
			FVector2D ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	void UUserWidget::Destruct()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.Destruct");
		struct
		{
		}params;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::Construct()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.Construct");
		struct 
		{
		}params;
		UObject::ProcessEvent(fn, &params);
	}
	void UUserWidget::AddToViewport(int ZOrder)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.AddToViewport");
		struct
		{
			int ZOrder;
		}params;
		params.ZOrder = ZOrder;
		UObject::ProcessEvent(fn, &params);
	}
	bool UUserWidget::AddToPlayerScreen(int ZOrder)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.AddToPlayerScreen");
		struct
		{
			int ZOrder;
			bool ReturnValue;
		}params;
		params.ZOrder = ZOrder;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
};