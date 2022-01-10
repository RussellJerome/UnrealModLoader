#Games Basic Information
[GameInfo]

#Set to 1 (true) if the games engine version is 4.23 and up
UsesFNamePool=1

#Set to 1 (true) if the game engine version is 4.18 and up (this can vary)
IsUsingFChunkedFixedUObjectArray=1

#Fallback if Spawn Actor can't be found or refuses to work. You should almost NEVER use.
IsUsingDeferedSpawn=0

#GName, GWorld, and GObject patterns with op code (EXAMPLE BELOW, FILL OUT PATTERNS YOURSELF IF NEEDED)
[GInfo]

#Set to 1 if you are manually defining GName, GObject, and GWorld by Patterns. Set to 0 if manually defining via offsets.
IsGInfoPatterns=1

GName=74 09 48 8D 15 ? ? ? ? EB 16
GNameFirstOpCodes=5
GNameTotalByteInstruction=9

GObject=89 2D ? ? ? ? 74 05 E8 ? ? ? ? C6 05 ? ? ? ? ? 
GObjectFirstOpCodes=2
GObjectTotalByteInstruction=6

GWorld=48 8B 05 ? ? ? ? 48 85 C0 74 33 48 8B 40 30 
GWorldFirstOpCodes=3
GWorldTotalByteInstruction=7

#EngineDefs via their offsets found in reclass
#UObject
[UObjectDef]
Index=0xC
Class=0x10
Name=0x18
Outer=0x20

#UField
[UFieldDef]
Next=0x28

#UStruct
[UStructDef]
SuperStruct=0x40
Children=0x48
PropertiesSize=0x58

#UFunction
[UFunctionDef]
FunctionFlags=0xB0
NumParms=0x0
ParmSize=0x0
Func=0xD8

#Function direct patterns or offsets in the event auto finder fails.

[FunctionInfo]

#Set to 1 (true) in the event you wish to define with direct patterns
IsFunctionPatterns=1

GameStateInit=40 53 48 83 EC 20 48 8B 41 10 48 8B D9 48 8B 91
BeginPlay=48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B 01 48 8B F1 
StaticLoadObject=40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 44 8B A5 ? ? ? ? 33 C0 
SpawnActorFTrans=48 8B C4 55 53 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 44 0F 29 40 ? 44 0F 29 88 ? ? ? ? 44 0F 29 B8 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 
CallFunctionByNameWithArguments=40 55 53 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 ? 48 8B 05 ? ? ? ? 48 33 C5 48 89 85 ? ? ? ? 4C 89 85 ? ? ? ? 48 8B D9 
ProcessEvent=40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 ? 48 89 9D ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C5 48 89 85 ? ? ? ? 8B 41 0C 45 33 F6 
CreateDefaultObject=4C 8B DC 55 57 49 8D AB ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 83 B9