#include "Widget.h"
#include "Internationalization/Text.h"
#include "../Slate/WidgetTransform.h"
#include "UObject/NameType.h"

namespace UE4
{
	void UWidget::SetVisibility(ESlateVisibility InVisibility)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetVisibility");
		struct
		{
			ESlateVisibility InVisibility;
		}params;
		params.InVisibility = InVisibility;
		UObject::ProcessEvent(fn, &params);
	}
	/*void UWidget::SetToolTipText(const FText& InToolTipText)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetToolTipText");
		struct
		{
			FText InToolTipText;
		}params;
		params.InToolTipText = InToolTipText;
		UObject::ProcessEvent(fn, &params);
	}*/
	void UWidget::SetToolTip(UWidget* Widget)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetToolTip");
		struct
		{
			UWidget* Widget;
		}params;
		params.Widget = Widget;
		UObject::ProcessEvent(fn, &params);
	}
	void UWidget::SetRenderTranslation(const FVector2D& Translation)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetRenderTranslation");
		struct
		{
			FVector2D Translation;
		}params;
		params.Translation = Translation;
		UObject::ProcessEvent(fn, &params);
	}
	void UWidget::SetRenderTransformPivot(const FVector2D& Pivot)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetRenderTransformPivot");
		struct
		{
			FVector2D Pivot;
		}params;
		params.Pivot = Pivot;
		UObject::ProcessEvent(fn, &params);
	}
	void UWidget::SetRenderTransform(const FWidgetTransform& InTransform)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetRenderTransform");
		struct
		{
			FWidgetTransform InTransform;
		}params;
		params.InTransform = InTransform;
		UObject::ProcessEvent(fn, &params);
	}
	void UWidget::SetRenderShear(const FVector2D& Shear)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetRenderShear");
		struct
		{
			FVector2D Shear;
		}params;
		params.Shear = Shear;
		UObject::ProcessEvent(fn, &params);
	}
	void UWidget::SetRenderScale(const FVector2D& Scale)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetRenderScale");
		struct
		{
			FVector2D Scale;
		}params;
		params.Scale = Scale;
		UObject::ProcessEvent(fn, &params);
	}
	void UWidget::SetRenderAngle(float Angle)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetRenderAngle");
		struct
		{
			float Angle;
		}params;
		params.Angle = Angle;
		UObject::ProcessEvent(fn, &params);
	}
	void UWidget::SetNavigationRule(EUINavigation Direction, EUINavigationRule Rule, const FName& WidgetToFocus)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetNavigationRule");
		struct
		{
			EUINavigation Direction;
			EUINavigationRule Rule;
			FName WidgetToFocus;
		}params;
		params.Direction = Direction;
		params.Rule = Rule;
		params.WidgetToFocus = WidgetToFocus;
		UObject::ProcessEvent(fn, &params);
	}
	void UWidget::SetKeyboardFocus()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetKeyboardFocus");
		struct 
		{
		}params;
		UObject::ProcessEvent(fn, &params);
	}
	void UWidget::SetIsEnabled(bool bInIsEnabled)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetIsEnabled");
		struct
		{
			bool bInIsEnabled;
		}params;
		params.bInIsEnabled = bInIsEnabled;
		UObject::ProcessEvent(fn, &params);
	}
	void UWidget::SetCursor(TEnumAsByte<EMouseCursor> InCursor)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetCursor");
		struct
		{
			TEnumAsByte<EMouseCursor> InCursor;
		}params;
		params.InCursor = InCursor;
		UObject::ProcessEvent(fn, &params);
	}
	void UWidget::SetAllNavigationRules(EUINavigationRule Rule, const FName& WidgetToFocus)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetAllNavigationRules");
		struct
		{
			EUINavigationRule Rule;
			FName WidgetToFocus;
		}params;
		params.Rule = Rule;
		params.WidgetToFocus = WidgetToFocus;
		UObject::ProcessEvent(fn, &params);
	}
	void UWidget::ResetCursor()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.ResetCursor");
		struct
		{
		}params;
		UObject::ProcessEvent(fn, &params);
	}
	void UWidget::RemoveFromParent()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.RemoveFromParent");
		struct
		{
		}params;
		UObject::ProcessEvent(fn, &params);
	}
	bool UWidget::IsVisible()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.IsVisible");
		struct
		{
			bool ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	bool UWidget::IsHovered()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.IsHovered");
		struct
		{
			bool ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	void UWidget::InvalidateLayoutAndVolatility()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.InvalidateLayoutAndVolatility");
		struct
		{
		}params;
		UObject::ProcessEvent(fn, &params);
	}
	bool UWidget::HasMouseCapture()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.HasMouseCapture");
		struct
		{
			bool ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	bool UWidget::HasKeyboardFocus()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.HasKeyboardFocus");
		struct
		{
			bool ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	bool UWidget::HasFocusedDescendants()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.HasFocusedDescendants");
		struct
		{
			bool ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	bool UWidget::HasAnyUserFocus()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.HasAnyUserFocus");
		struct
		{
			bool ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	ESlateVisibility UWidget::GetVisibility()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.GetVisibility");
		struct
		{
			ESlateVisibility ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	UPanelWidget* UWidget::GetParent()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.GetParent");
		struct
		{
			class UPanelWidget* ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	bool UWidget::GetIsEnabled()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.GetIsEnabled");
		struct
		{
			bool ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	FVector2D UWidget::GetDesiredSize()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.GetDesiredSize");
		struct
		{
			FVector2D ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	void UWidget::ForceVolatile(bool bForce)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.ForceVolatile");
		struct
		{
			bool bForce;
		}params;
		params.bForce = bForce;
		UObject::ProcessEvent(fn, &params);
	}
	void UWidget::ForceLayoutPrepass()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.ForceLayoutPrepass");
		struct
		{
		}params;
		UObject::ProcessEvent(fn, &params);
	}
};