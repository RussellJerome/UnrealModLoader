#pragma once
#include "Visual.h"

namespace UE4
{
	class UPanelSlot : public UVisual
	{
	public:
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class UMG.PanelSlot");
			return ptr;
		}
	};
};