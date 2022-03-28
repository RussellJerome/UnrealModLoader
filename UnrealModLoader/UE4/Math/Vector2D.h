#pragma once

namespace UE4
{
	struct FVector2D
	{
		float X;
		float Y;

		inline FVector2D()
			: X(0), Y(0)
		{ }

		inline FVector2D(float x, float y)
			: X(x),
			Y(y)
		{ }

	};
};