#pragma once

namespace UE4
{
	struct FVector
	{
		float X;
		float Y;
		float Z;

		inline FVector()
			: X(0), Y(0), Z(0)
		{ }

		inline FVector(float x, float y, float z)
			: X(x), Y(y), Z(z)
		{ }
	};
};