#pragma once
#include "PanelWidget.h"
namespace UE4
{
	class UContentWidget : public UPanelWidget
	{
	public:

		class UPanelSlot* SetContent(class UWidget* Content);
		class UPanelSlot* GetContentSlot();

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class UMG.ContentWidget");
			return ptr;
		}
	};
};