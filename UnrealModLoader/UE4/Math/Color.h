#pragma once

namespace UE4
{
	struct FColor
	{
		unsigned char B;
		unsigned char G;
		unsigned char R;
		unsigned char A;
	};

	struct FLinearColor
	{
		float R;
		float G;
		float B;
		float A;

		inline FLinearColor()
			: R(0), G(0), B(0), A(0)
		{ }

		inline FLinearColor(float r, float g, float b, float a)
			: R(r),
			G(g),
			B(b),
			A(a)
		{ }

	};
};