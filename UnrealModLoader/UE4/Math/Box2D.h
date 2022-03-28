#pragma once
#include "Vector2D.h"

namespace UE4
{
	struct FBox2D
	{
		struct FVector2D Min;
		struct FVector2D Max;
		unsigned char bIsValid;
		unsigned char UnknownData00[0x3];
	};
};