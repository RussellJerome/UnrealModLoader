#pragma once
#include "Vector.h"

namespace UE4
{
	struct alignas(16) FPlane : public FVector
	{
		float W;
	};
};