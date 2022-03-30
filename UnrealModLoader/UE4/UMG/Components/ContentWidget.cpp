#include "ContentWidget.h"
#include "Widget.h"
#include "PanelSlot.h"

namespace UE4
{
	UPanelSlot* UContentWidget::SetContent(UWidget* Content)
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.ContentWidget.SetContent");
		struct
		{
			UWidget* Content;
			UPanelSlot* ReturnValue;
		}params;
		params.Content = Content;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	UPanelSlot* UContentWidget::GetContentSlot()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.ContentWidget.GetContentSlot");
		struct
		{
			UPanelSlot* ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
};