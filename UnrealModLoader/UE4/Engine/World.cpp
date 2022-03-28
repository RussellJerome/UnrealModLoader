#include "World.h"

namespace UE4
{
	UWorld** UWorld::GWorld = nullptr;


	AActor* UWorld::SpawnActor(UClass* uclass, const  FTransform* transform, const FActorSpawnParameters* params)
	{
		return reinterpret_cast<AActor * (*)(UWorld*, UClass*, const FTransform*, const FActorSpawnParameters*)>(UML::GetGameInfo()->SpawnActorFTrans)(this, uclass, transform, params);
	}
};