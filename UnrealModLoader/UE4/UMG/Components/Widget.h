#pragma once
#include "Containers/EnumAsByte.h"
#include "../UMGBaseTypes.h"
#include "UObject/CoreTypes.h"
#include "SlateCore/Styling/SlateTypes.h"
#include "Visual.h"

/*
TODO
====
ADD FUNCTIONS WITH MISSING TYPES IN THE FUTURE
*/
namespace UE4
{
	class UWidget : public UVisual
	{
	public:
		void SetVisibility(ESlateVisibility InVisibility);
		//void SetUserFocus(class APlayerController* PlayerController);
		//void SetToolTipText(const struct FText& InToolTipText);
		void SetToolTip(class UWidget* Widget);
		void SetRenderTranslation(const struct FVector2D& Translation);
		void SetRenderTransformPivot(const struct FVector2D& Pivot);
		void SetRenderTransform(const struct FWidgetTransform& InTransform);
		void SetRenderShear(const struct FVector2D& Shear);
		void SetRenderScale(const struct FVector2D& Scale);
		void SetRenderAngle(float Angle);
		void SetNavigationRule(EUINavigation Direction, EUINavigationRule Rule, const class FName& WidgetToFocus);
		void SetKeyboardFocus();
		void SetIsEnabled(bool bInIsEnabled);
		void SetCursor(TEnumAsByte<EMouseCursor> InCursor);
		void SetAllNavigationRules(EUINavigationRule Rule, const class FName& WidgetToFocus);
		void ResetCursor();
		void RemoveFromParent();
		bool IsVisible();
		bool IsHovered();
		void InvalidateLayoutAndVolatility();
		//bool HasUserFocusedDescendants(class APlayerController* PlayerController);
		//bool HasUserFocus(class APlayerController* PlayerController);
		bool HasMouseCapture();
		bool HasKeyboardFocus();
		bool HasFocusedDescendants();
		bool HasAnyUserFocus();
		ESlateVisibility GetVisibility();
		class UPanelWidget* GetParent();
		//class APlayerController* GetOwningPlayer();
		bool GetIsEnabled();
		struct FVector2D GetDesiredSize();
		void ForceVolatile(bool bForce);
		void ForceLayoutPrepass();

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class UMG.Widget");
			return ptr;
		}
	};
};