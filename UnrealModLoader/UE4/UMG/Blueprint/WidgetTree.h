#pragma once
#include "UObject/Object.h"
namespace UE4
{
	class UWidgetTree : public UObject
	{
	public:
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class UMG.WidgetTree");
			return ptr;
		}
	};
};