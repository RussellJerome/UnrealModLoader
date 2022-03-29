#pragma once
#include "Widget.h"

namespace UE4
{
	class UPanelWidget : public UWidget
	{
	public:
		bool RemoveChildAt(int Index);
		bool RemoveChild(class UWidget* Content);
		bool HasChild(class UWidget* Content);
		bool HasAnyChildren();
		int GetChildrenCount();
		int GetChildIndex(class UWidget* Content);
		class UWidget* GetChildAt(int Index);
		void ClearChildren();
		class UPanelSlot* AddChild(class UWidget* Content);

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class UMG.PanelWidget");
			return ptr;
		}
	};

};