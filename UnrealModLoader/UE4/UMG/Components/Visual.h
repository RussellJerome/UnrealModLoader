#pragma once
#include "UObject/Object.h"

namespace UE4
{
	class UVisual : public UObject
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class UMG.Visual");
			return ptr;
		}

	};
};