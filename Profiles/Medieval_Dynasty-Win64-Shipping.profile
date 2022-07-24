#Games Basic Information
[GameInfo]

#Set to 1 (true) if the games engine version is 4.23 and up
UsesFNamePool=1

#Set to 1 (true) if the game engine version is 4.18 and up (this can vary)
IsUsingFChunkedFixedUObjectArray=1

#Fallback if Spawn Actor can't be found or refuses to work. You should almost NEVER use.
IsUsingDeferedSpawn=0

#UE4.22 changes the namepool weird, only set this to 1 if the game uses 4.22
#IsUsing4_22=0

[FunctionInfo]
IsFunctionPatterns=1
GameStateInit=40 53 48 83 EC 20 48 8B 41 10 48 8B D9 48 8B 91
BeginPlay=48 89 5C 24 10 48 89 6C 24 18 48 89 74 24 20 57 41 56 41 57 48 81 EC 10 01 00 00 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 08 01 00 00 48 8B 01 48 8B F9 F3 0F 10 89 ? ? ? ? FF 90 ? ? ? ? BA 30 00 00 00 48 8B CF
StaticLoadObject=40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 F8 F7 FF FF 48 81 EC 08 09 00 00 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 F0 07 00 00 48 8B 85 88 08 00 00 33 F6 
SpawnActorFTrans=48 8B C4 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 88 48 81 EC 78 01 00 00 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 88 ? ? ? ? 44 0F 29 90 ? ? ? ? 44 0F 29 98 ? ? ? ? 44 0F 29 A8 ? ? ? ? 48 8B 05 ? ? ? ?
CallFunctionByNameWithArguments=40 55 53 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 ? 48 8B 05 ? ? ? ? 48 33 C5 48 89 85 ? ? ? ? 4C 89 85 ? ? ? ? 48 8B F1
ProcessEvent=40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 ? 48 89 9D ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C5 48 89 85 ? ? ? ? 8B 41 0C 45 33 F6 3B 05
CreateDefualtObject=4C 8B DC 53 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 83 B9