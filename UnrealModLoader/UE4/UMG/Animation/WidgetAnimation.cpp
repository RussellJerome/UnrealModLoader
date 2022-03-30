#include "WidgetAnimation.h"

namespace UE4
{
	float UWidgetAnimation::GetStartTime()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetAnimation.GetStartTime");
		struct
		{
			float ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	float UWidgetAnimation::GetEndTime()
	{
		static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetAnimation.GetEndTime");
		struct
		{
			float ReturnValue;
		}params;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
};