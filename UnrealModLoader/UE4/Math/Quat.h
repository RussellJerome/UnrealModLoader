#pragma once

namespace UE4
{
	struct alignas(16) FQuat
	{
		float X;
		float Y;
		float Z;
		float W;

		inline FQuat()
			: X(0), Y(0), Z(0), W(0)
		{ }

		inline FQuat(float X, float Y, float Z, float W)
			: X(X), Y(Y), Z(Z), W(W)
		{ }
	};
};