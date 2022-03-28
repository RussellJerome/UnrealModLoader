#pragma once
#include "Vector.h"

namespace UE4
{
	struct FBox
	{
		struct FVector Min;
		struct FVector Max;
		unsigned char IsValid;
		unsigned char UnknownData00[0x3];
	};
};