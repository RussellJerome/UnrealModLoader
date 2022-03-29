#include "Actor.h"
#include "UObject/NameType.h"
#include "Math/Vector.h"

namespace UE4
{
	bool AActor::WasRecentlyRendered(float Tolerance)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.WasRecentlyRendered");
		struct
		{
			float Tolerance;
			bool ReturnValue;
		}params;
		params.Tolerance = Tolerance;
		UObject::ProcessEvent(fn, &params);
		return params.ReturnValue;
	}
	void AActor::UserConstructionScript()
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.UserConstructionScript");
		struct{
		}params;
		UObject::ProcessEvent(fn, &params);
	}
	void AActor::TearOff()
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.TearOff");
		struct
		{
		}params;
		UObject::ProcessEvent(fn, &params);
	}
	void AActor::SnapRootComponentTo(AActor* InParentActor, const FName& InSocketName)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.SnapRootComponentTo");
		struct
		{
			AActor* InParentActor;
			struct FName InSocketName;
		}params;
		params.InParentActor = InParentActor;
		params.InSocketName = InSocketName;
		UObject::ProcessEvent(fn, &params);
	}
	void AActor::SetTickGroup(TEnumAsByte<ETickingGroup> NewTickGroup)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.SetTickGroup");
		struct
		{
			TEnumAsByte<ETickingGroup> NewTickGroup;
		}params;
		params.NewTickGroup = NewTickGroup;
		UObject::ProcessEvent(fn, &params);
	}
	void AActor::SetTickableWhenPaused(bool bTickableWhenPaused)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.SetTickableWhenPaused");
		struct
		{
			bool bTickableWhenPaused;
		}params;
		params.bTickableWhenPaused = bTickableWhenPaused;
		UObject::ProcessEvent(fn, &params);
	}
	void AActor::SetReplicates(bool bInReplicates)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.SetReplicates");
		struct
		{
			bool bInReplicates;
		}params;
		params.bInReplicates = bInReplicates;
		UObject::ProcessEvent(fn, &params);
	}
	void AActor::SetReplicateMovement(bool bInReplicateMovement)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.SetReplicateMovement");

		struct
		{
			bool bInReplicateMovement;
		}params;
		params.bInReplicateMovement = bInReplicateMovement;
		UObject::ProcessEvent(fn, &params);
	}
	void AActor::SetOwner(AActor* NewOwner)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.SetOwner");
		struct
		{
			AActor* NewOwner;
		}params;
		params.NewOwner = NewOwner;
		UObject::ProcessEvent(fn, &params);
	}
	void AActor::SetNetDormancy(TEnumAsByte<ENetDormancy> NewDormancy)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.SetNetDormancy");
		struct
		{
			TEnumAsByte<ENetDormancy> NewDormancy;
		}params;
		params.NewDormancy = NewDormancy;
		UObject::ProcessEvent(fn, &params);
	}
	void AActor::SetLifeSpan(float InLifespan)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.SetLifeSpan");
		struct
		{
			float InLifespan;
		}params;
		params.InLifespan = InLifespan;
		UObject::ProcessEvent(fn, &params);
	}
	void AActor::SetActorTickInterval(float TickInterval)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.SetActorTickInterval");
		struct
		{
			float TickInterval;
		}params;
		params.TickInterval = TickInterval;
		UObject::ProcessEvent(fn, &params);
	}
	void AActor::SetActorTickEnabled(bool bEnabled)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.SetActorTickEnabled");
		struct
		{
			bool bEnabled;
		}params;
		params.bEnabled = bEnabled;
		UObject::ProcessEvent(fn, &params);
	}
	void AActor::SetActorScale3D(const FVector& NewScale3D)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.SetActorScale3D");
		struct
		{
			struct FVector NewScale3D;
		}params;
		params.NewScale3D = NewScale3D;
		UObject::ProcessEvent(fn, &params);
	}
	void AActor::SetActorRelativeScale3D(const FVector& NewRelativeScale)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.SetActorRelativeScale3D");
		struct
		{
			struct FVector NewRelativeScale;
		}params;
		params.NewRelativeScale = NewRelativeScale;
		UObject::ProcessEvent(fn, &params);
	}
	void AActor::SetActorHiddenInGame(bool bNewHidden)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.SetActorHiddenInGame");
		struct
		{
			bool bNewHidden;
		}params;
		params.bNewHidden = bNewHidden;

		UObject::ProcessEvent(fn, &params);
	}
	void AActor::SetActorEnableCollision(bool bNewActorEnableCollision)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.SetActorEnableCollision");
		struct
		{
			bool bNewActorEnableCollision;
		}params;
		params.bNewActorEnableCollision = bNewActorEnableCollision;
		UObject::ProcessEvent(fn, &params);
	}
	void AActor::RemoveTickPrerequisiteActor(AActor* PrerequisiteActor)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.RemoveTickPrerequisiteActor");
		struct
		{
			AActor* PrerequisiteActor;
		}params;
		params.PrerequisiteActor = PrerequisiteActor;
		UObject::ProcessEvent(fn, &params);
	}
	void AActor::ReceiveTick(float DeltaSeconds)
	{
		static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.ReceiveTick");
		struct
		{
			float DeltaSeconds;
		}params;
		params.DeltaSeconds = DeltaSeconds;
		UObject::ProcessEvent(fn, &params);
	}
};