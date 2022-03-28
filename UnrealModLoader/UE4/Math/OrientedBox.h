#pragma once
#include "Vector.h"

namespace UE4
{
	struct FOrientedBox
	{
		struct FVector Center;
		struct FVector AxisX;
		struct FVector AxisY;
		struct FVector AxisZ;
		float ExtentX;
		float ExtentY;
		float ExtentZ;
	};
};