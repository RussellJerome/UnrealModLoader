#pragma once

namespace UE4
{
	struct FRotator
	{
		float Pitch;
		float Yaw;
		float Roll;

		inline FRotator()
			: Pitch(0), Yaw(0), Roll(0)
		{ }

		inline FRotator(float pitch, float yaw, float roll)
			: Pitch(pitch), Yaw(yaw), Roll(roll)
		{ }
	};
};