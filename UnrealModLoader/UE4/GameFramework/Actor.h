#pragma once
#include "UObject/Object.h"
#include "Containers/EnumAsByte.h"
#include "Engine/EngineBaseTypes.h"

namespace UE4
{
	/*
	TODO
	====
	FINISH FILLING OUT THIS CLASS
	*/
	class AActor : public UObject
	{
	public:
		bool WasRecentlyRendered(float Tolerance);
		void UserConstructionScript();
		void TearOff();
		void SnapRootComponentTo(class AActor* InParentActor, const class FName& InSocketName);
		void SetTickGroup(TEnumAsByte<ETickingGroup> NewTickGroup);
		void SetTickableWhenPaused(bool bTickableWhenPaused);
		void SetReplicates(bool bInReplicates);
		void SetReplicateMovement(bool bInReplicateMovement);
		void SetOwner(class AActor* NewOwner);
		void SetNetDormancy(TEnumAsByte<ENetDormancy> NewDormancy);
		void SetLifeSpan(float InLifespan);
		void SetActorTickInterval(float TickInterval);
		void SetActorTickEnabled(bool bEnabled);
		void SetActorScale3D(const struct FVector& NewScale3D);
		void SetActorRelativeScale3D(const struct FVector& NewRelativeScale);
		void SetActorHiddenInGame(bool bNewHidden);
		void SetActorEnableCollision(bool bNewActorEnableCollision);
		//void RemoveTickPrerequisiteComponent(class UActorComponent* PrerequisiteComponent);
		void RemoveTickPrerequisiteActor(class AActor* PrerequisiteActor);
		void ReceiveTick(float DeltaSeconds);

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.Actor");
			return ptr;
		}
	};
};