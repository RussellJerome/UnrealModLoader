#Games Basic Information
[GameInfo]

#Set to 1 (true) if the games engine version is 4.23 and up
UsesFNamePool=0

#Set to 1 (true) if the game engine version is 4.18 and up (this can vary)
IsUsingFChunkedFixedUObjectArray=1

#UE4.22 changes the namepool weird, only set this to 1 if the game uses 4.22
IsUsing4_22=1

#Function direct patterns or offsets in the event auto finder fails.

[FunctionInfo]

#Set to 1 (true) in the event you wish to define with direct patterns
IsFunctionPatterns=1

GameStateInit=40 53 48 83 EC 20 48 8B 41 10 48 8B D9 48 8B 91
BeginPlay=48 8B C4 56 57 41 56 48 81 EC ? ? ? ? 48 C7 44 24 ? ? ? ? ? 48 89 58 10 48 89 68 18 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 4C 8B F1 
StaticLoadObject=40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 C7 45 ? ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E1 4D 8B F0 48 8B FA 4C 8B F9 48 89 54 24 ? 8B 85
SpawnActorFTrans=48 8B C4 55 53 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 C7 45 ? ? ? ? ? 0F 29 70 A8 0F 29 78 98 44 0F 29 40 ? 44 0F 29 88 ? ? ? ? 44 0F 29 90 ? ? ? ? 44 0F 29 98 ? ? ? ? 44 0F 29 A0 ? ? ? ? 44 0F 29 A8 ? ? ? ? 44 0F 29 B0 ? ? ? ? 44 0F 29 B8 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 30 49 8B F1 4D 8B E0 
CallFunctionByNameWithArguments=40 55 53 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 ? 48 C7 85 ? ? ? ? ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C5 
ProcessEvent=40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 ? 48 C7 45 ? ? ? ? ? 48 89 9D ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C5 48 89 85 ? ? ? ? 4D 8B F8 

#Wasnt going to take the time to find this when it is virutally useless now
CreateDefaultObject= 00 00 00