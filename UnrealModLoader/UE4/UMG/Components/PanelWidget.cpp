#include "PanelWidget.h"
#include "PanelSlot.h"

namespace UE4
{
	bool UPanelWidget::RemoveChildAt(int Index)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.RemoveChildAt");
		struct
		{
			int Index;
			bool ReturnValue;
		}params;
		params.Index = Index;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	bool UPanelWidget::RemoveChild(UWidget* Content)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.RemoveChild");
		struct
		{
			UWidget* Content;
			bool ReturnValue;
		}params;
		params.Content = Content;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	bool UPanelWidget::HasChild(UWidget* Content)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.HasChild");
		struct
		{
			UWidget* Content;
			bool ReturnValue;
		}params;
		params.Content = Content;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	bool UPanelWidget::HasAnyChildren()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.HasAnyChildren");
		struct
		{
			bool ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	int UPanelWidget::GetChildrenCount()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.GetChildrenCount");
		struct
		{
			bool ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	int UPanelWidget::GetChildIndex(UWidget* Content)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.GetChildIndex");
		struct
		{
			UWidget* Content;
			int ReturnValue;
		}params;
		params.Content = Content;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	UWidget* UPanelWidget::GetChildAt(int Index)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.GetChildAt");
		struct
		{
			int Index;
			UWidget* ReturnValue;
		}params;
		params.Index = Index;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	void UPanelWidget::ClearChildren()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.ClearChildren");
		struct
		{
		}params;
		UObject::ProcessEvent(fn, &params);
	}
	UPanelSlot* UPanelWidget::AddChild(UWidget* Content)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.AddChild");
		struct
		{
			UWidget* Content;
			UPanelSlot* ReturnValue;
		}params;
		params.Content = Content;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
};