#Games Basic Information
[GameInfo]
UsesFNamePool=0
IsUsingFChunkedFixedUObjectArray=1
IsUsingDeferedSpawn=1
#Overwrites the BeginPlay hook which calls PostBeginPlay and PostLoaderStart. To use PlayerController default leave empty.
BeginPlayOverwrite=

#GName, GWorld, and GObject offsets
[GInfo]
IsGInfoPatterns=1
GName=48 8B 05 ? ? ? ? 48 85 C0 75 5F
GNameFirstOpCodes=3
GNameTotalByteInstruction=7

GObject=85 ED 7E 0F 48 8B D6 48 8D 0D ? ? ? ? E8
GObjectFirstOpCodes=10
GObjectTotalByteInstruction=14

GWorld=48 8B 1D ? ? ? ? 48 85 DB 74 3B
GWorldFirstOpCodes=3
GWorldTotalByteInstruction=7

#Function Offsets needed for hooks ad calls
[FunctionInfo]
IsFunctionPatterns=1
GameStateInit=40 53 48 83 EC 20 48 8B 41 10 48 8B D9 48 8B 91
BeginPlay=4C 8B DC 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B 01 F3 0F 10 89
StaticLoadObject=40 55 53 56 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 0F B6 85
SpawnActorFTrans=48 8B C4 55 53 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 78 98 44 0F 29 40 ? 48 8B 05 ? ? ? ? 48 33 C4
CallFunctionByNameWithArguments=40 55 53 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 ? 48 8B 05 ? ? ? ? 48 33 C5 48 89 85 ? ? ? ? 4C 89 85 ? ? ? ? 48 8B F1 48 89 4D 38
CreateDefaultObject=4C 8B DC 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 83 B9
ProcessEvent=40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 ? 48 89 9D ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C5 48 89 85 ? ? ? ? 4D 8B F8 45 33 F6 44 8B 41 0C 48 8B F2 44 3B 05