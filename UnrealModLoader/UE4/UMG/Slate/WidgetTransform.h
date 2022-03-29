#pragma once
#include "Math/Vector2D.h"

namespace UE4
{
	struct FWidgetTransform
	{
		struct FVector2D Translation;
		struct FVector2D Scale;
		struct FVector2D Shear;
		float Angle;
	};
};