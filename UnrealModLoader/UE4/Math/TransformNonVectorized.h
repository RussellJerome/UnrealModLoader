#pragma once
#include "Quat.h"
#include "Vector.h"

namespace UE4
{
	struct alignas(16) FTransform
	{
		struct FQuat Rotation;
		struct FVector Translation;
		unsigned char UnknownData00[0x4];
		struct FVector Scale3D;
		unsigned char UnknownData01[0x4];

		inline FTransform()
			: Rotation(FQuat::FQuat()), Translation(FVector::FVector()), Scale3D(FVector::FVector(1, 1, 1)), UnknownData00(""), UnknownData01("")
		{ }

		inline FTransform(FVector Trans, FQuat Rot, FVector Scale)
			: Rotation(Rot), Translation(Trans), Scale3D(Scale), UnknownData00(""), UnknownData01("")
		{ }
	};
};