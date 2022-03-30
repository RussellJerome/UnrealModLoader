#pragma once
#include "Math/Color.h"
#include "Containers/EnumAsByte.h"
#include "SlateTypes.h"

namespace UE4
{
	struct FSlateColor
	{
		FLinearColor SpecifiedColor;
		TEnumAsByte<ESlateColorStylingMode> ColorUseRule;
		unsigned char UnknownData00[0x17];
	};
};