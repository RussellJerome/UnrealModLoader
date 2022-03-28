#pragma once
#include "UObject/Object.h"
#include "UObject/NameType.h"
#include "Math/TransformNonVectorized.h"

namespace UE4
{
	struct FActorSpawnParameters
	{
		FActorSpawnParameters()
			: Name("")
			, Template(NULL)
			, Owner(NULL)
			, Instigator(NULL)
			, OverrideLevel(NULL)
			, bNoCollisionFail(false)
			, bRemoteOwned(false)
			, bNoFail(false)
			, bDeferConstruction(false)
			, bAllowDuringConstructionScript(false)
			, ObjectFlags(0x00000008)
		{
		}
		FName Name;
		class AActor* Template;
		class AActor* Owner;
		class AActor* Instigator;
		class	ULevel* OverrideLevel;
		int	bNoCollisionFail : 1;
		int	bRemoteOwned : 1;
		int	bNoFail : 1;
		int	bDeferConstruction : 1;
		int	bAllowDuringConstructionScript : 1;
		int ObjectFlags;
	};

	class UWorld : public UObject
	{
	public:
		class AActor* SpawnActor(UClass* uclass, const  FTransform* transform, const FActorSpawnParameters* params);

		static UWorld** GWorld;
		static inline UWorld* GetWorld()
		{
			return *GWorld;
		};

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.World");
			return ptr;
		}
	};
};