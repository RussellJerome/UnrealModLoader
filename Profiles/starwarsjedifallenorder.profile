#Games Basic Information
[GameInfo]
UsesFNamePool=0
IsUsingFChunkedFixedUObjectArray=1
IsUsingDeferedSpawn=0
#Overwrites the BeginPlay hook which calls PostBeginPlay and PostLoaderStart. To use PlayerController default leave empty.
BeginPlayOverwrite=BlueprintGeneratedClass BP_Hero.BP_Hero_C

#GName, GWorld, and GObject offsets
[GInfo]
IsGInfoPatterns=0
GName=0x371DC98
GObject=0x3875CD0
GWorld=0x396BAB8

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
SuperStruct=0x30
Children=0x38
PropertiesSize=0x40

#UFunction
[UFunctionDef]
FunctionFlags=0x88
NumParms=0x8C
ParmSize=0x8E
Func=0x0B

#Function Offsets needed for hooks ad calls
[FunctionInfo]
IsFunctionPatterns=0
GameStateInit=0x1A3AAF0
BeginPlay=0xA67CBB0
Say=0x1A439F0
StaticLoadObject=0x8894D70
SpawnActorFTrans=0x11C4A9F0
CallFunctionByNameWithArguments=0x88731A0
CreateDefualtObject=0x1A6FBC70
ProcessEvent=0x888D540