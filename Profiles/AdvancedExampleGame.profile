#Games Basic Information
#[GameInfo]

#Set to 1 (true) if the games engine version is 4.23 and up
#UsesFNamePool=1

#Set to 1 (true) if the game engine version is 4.18 and up (this can vary)
#IsUsingFChunkedFixedUObjectArray=1

#Fallback if Spawn Actor can't be found or refuses to work. You should almost NEVER use.
#IsUsingDeferedSpawn=0

#Overwrites the BeginPlay hook which calls PostBeginPlay and PostLoaderStart. To use PlayerController default leave empty.
#BeginPlayOverwrite=

#UE4.22 changes the namepool weird, only set this to 1 if the game uses 4.22
#IsUsing4_22=0

#If you get any Direct X errors such as resizing, enable this to delay the hook and prevent most issues.
#DelayGUISpawn=1

#GName, GWorld, and GObject patterns with op code (EXAMPLE BELOW, FILL OUT PATTERNS YOURSELF IF NEEDED)
#[GInfo]

#Set to 1 if you are manually defining GName, GObject, and GWorld by Patterns. Set to 0 if manually defining via offsets.
#IsGInfoPatterns=1

#Patten Example

#GName=48 8B 05 ? ? ? ? 48 85 C0 75 5F
#GNameFirstOpCodes=3
#GNameTotalByteInstruction=7

#GObject=85 ED 7E 0F 48 8B D6 48 8D 0D ? ? ? ? E8
#GObjectFirstOpCodes=10
#GObjectTotalByteInstruction=14

#GWorld=48 8B 1D ? ? ? ? 48 85 DB 74 3B
#GWorldFirstOpCodes=3
#GWorldTotalByteInstruction=7

#Offset Example

#GName=0x371DC98
#GObject=0x3875CD0
#GWorld=0x396BAB8


#In the event the Base Engine Def auto finder fails, you can manually set them here.

#UObject
#[UObjectDef]
#Index=0xC
#Class=0x10
#Name=0x18
#Outer=0x20

#UField
#[UFieldDef]
#Next=0x28

#UStruct
#[UStructDef]
#SuperStruct=0x30
#Children=0x38
#PropertiesSize=0x40

#UFunction
#[UFunctionDef]
#FunctionFlags=0x88
#NumParms=0x8C
#ParmSize=0x8E
#Func=0x0B

#In the event the Property Based Engine Def auto finder fails, you can manually set them here.

#Only need to define for 4.25 and up
#[FField]
#Name=0x0
#Next=0x0

#Represents UProperty or FProperty depending on what you set IsFProperty to.
#[Property]

#Set to 1 (true) if on 4.25 or newer, 0 (false) assumes it is using UProperty.

#IsFProperty=1
#ArrayDim=0x0
#Offset=0x0


#Function direct patterns or offsets in the event auto finder fails.

#[FunctionInfo]

#Set to 1 (true) in the event you wish to define with direct patterns
#IsFunctionPatterns=1

#GameStateInit=
#BeginPlay=
#StaticLoadObject=
#SpawnActorFTrans=
#CallFunctionByNameWithArguments
#ProcessEvent=
#CreateDefaultObject=