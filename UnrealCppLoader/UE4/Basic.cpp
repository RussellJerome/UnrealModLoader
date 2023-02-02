#ifdef _MSC_VER
#pragma pack(push, 0x8)
#endif

#include "Basic.hpp"
#include "CoreUObject_classes.hpp"

namespace UE4
{
LOADER_API DWORD *FName::GNames = nullptr;
LOADER_API FUObjectArray *UObject::GObjects = nullptr;
LOADER_API UWorld **UWorld::GWorld = nullptr;
} // namespace UE4

#ifdef _MSC_VER
#pragma pack(pop)
#endif
