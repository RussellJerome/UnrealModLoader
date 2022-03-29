#pragma once
#include <cstdint>

namespace UE4
{
	enum class ETextGender : uint8_t
	{
		Masculine = 0,
		Feminine = 1,
		Neuter = 2,
		ETextGender_MAX = 3
	};

	enum class EFormatArgumentType : uint8_t
	{
		Int = 0,
		UInt = 1,
		Float = 2,
		Double = 3,
		Text = 4,
		Gender = 5,
		EFormatArgumentType_MAX = 6
	};

	enum class EEndPlayReason : uint8_t
	{
		Destroyed = 0,
		LevelTransition = 1,
		EndPlayInEditor = 2,
		RemovedFromWorld = 3,
		Quit = 4,
		EEndPlayReason_MAX = 5
	};

	enum class ENavPathEvent : uint8_t
	{
		Cleared = 0,
		NewPath = 1,
		UpdatedDueToGoalMoved = 2,
		UpdatedDueToNavigationChanged = 3,
		Invalidated = 4,
		RePathFailed = 5,
		MetaPathUpdate = 6,
		Custom = 7,
		ENavPathEvent_MAX = 8
	};

	enum class ETickingGroup : uint8_t
	{
		TG_PrePhysics = 0,
		TG_StartPhysics = 1,
		TG_DuringPhysics = 2,
		TG_EndPhysics = 3,
		TG_PostPhysics = 4,
		TG_PostUpdateWork = 5,
		TG_LastDemotable = 6,
		TG_NewlySpawned = 7,
		TG_MAX = 8
	};

	enum class EComponentCreationMethod : uint8_t
	{
		Native = 0,
		SimpleConstructionScript = 1,
		UserConstructionScript = 2,
		Instance = 3,
		EComponentCreationMethod_MAX = 4
	};

	enum class EPlaneConstraintAxisSetting : uint8_t
	{
		Custom = 0,
		X = 1,
		Y = 2,
		Z = 3,
		UseGlobalPhysicsSetting = 4,
		EPlaneConstraintAxisSetting_MAX = 5
	};

	enum class EInterpToBehaviourType : uint8_t
	{
		OneShot = 0,
		OneShot_Reverse = 1,
		Loop_Reset = 2,
		PingPong = 3,
		EInterpToBehaviourType_MAX = 4
	};

	enum class EPlatformInterfaceDataType : uint8_t
	{
		PIDT_None = 0,
		PIDT_Int = 1,
		PIDT_Float = 2,
		PIDT_String = 3,
		PIDT_Object = 4,
		PIDT_Custom = 5,
		PIDT_MAX = 6
	};

	enum class EMovementMode : uint8_t
	{
		MOVE_None = 0,
		MOVE_Walking = 1,
		MOVE_NavWalking = 2,
		MOVE_Falling = 3,
		MOVE_Swimming = 4,
		MOVE_Flying = 5,
		MOVE_Custom = 6,
		MOVE_MAX = 7
	};

	enum class ENetworkFailure : uint8_t
	{
		NetDriverAlreadyExists = 0,
		NetDriverCreateFailure = 1,
		NetDriverListenFailure = 2,
		ConnectionLost = 3,
		ConnectionTimeout = 4,
		FailureReceived = 5,
		OutdatedClient = 6,
		OutdatedServer = 7,
		PendingConnectionFailure = 8,
		NetGuidMismatch = 9,
		NetChecksumMismatch = 10,
		ENetworkFailure_MAX = 11
	};

	enum class ETravelFailure : uint8_t
	{
		NoLevel = 0,
		LoadMapFailure = 1,
		InvalidURL = 2,
		PackageMissing = 3,
		PackageVersion = 4,
		NoDownload = 5,
		TravelFailure = 6,
		CheatCommands = 7,
		PendingNetGameCreateFailure = 8,
		CloudSaveFailure = 9,
		ServerTravelFailure = 10,
		ClientTravelFailure = 11,
		ETravelFailure_MAX = 12
	};

	enum class EScreenOrientation : uint8_t
	{
		Unknown = 0,
		Portrait = 1,
		PortraitUpsideDown = 2,
		LandscapeLeft = 3,
		LandscapeRight = 4,
		FaceUp = 5,
		FaceDown = 6,
		EScreenOrientation_MAX = 7
	};

	enum class EObjectTypeQuery : uint8_t
	{
		ObjectTypeQuery1 = 0,
		ObjectTypeQuery2 = 1,
		ObjectTypeQuery3 = 2,
		ObjectTypeQuery4 = 3,
		ObjectTypeQuery5 = 4,
		ObjectTypeQuery6 = 5,
		ObjectTypeQuery7 = 6,
		ObjectTypeQuery8 = 7,
		ObjectTypeQuery9 = 8,
		ObjectTypeQuery10 = 9,
		ObjectTypeQuery11 = 10,
		ObjectTypeQuery12 = 11,
		ObjectTypeQuery13 = 12,
		ObjectTypeQuery14 = 13,
		ObjectTypeQuery15 = 14,
		ObjectTypeQuery16 = 15,
		ObjectTypeQuery17 = 16,
		ObjectTypeQuery18 = 17,
		ObjectTypeQuery19 = 18,
		ObjectTypeQuery20 = 19,
		ObjectTypeQuery21 = 20,
		ObjectTypeQuery22 = 21,
		ObjectTypeQuery23 = 22,
		ObjectTypeQuery24 = 23,
		ObjectTypeQuery25 = 24,
		ObjectTypeQuery26 = 25,
		ObjectTypeQuery27 = 26,
		ObjectTypeQuery28 = 27,
		ObjectTypeQuery29 = 28,
		ObjectTypeQuery30 = 29,
		ObjectTypeQuery31 = 30,
		ObjectTypeQuery32 = 31,
		ObjectTypeQuery_MAX = 32,
		EObjectTypeQuery_MAX = 33
	};

	enum class EDrawDebugTrace : uint8_t
	{
		None = 0,
		ForOneFrame = 1,
		ForDuration = 2,
		Persistent = 3,
		EDrawDebugTrace_MAX = 4
	};

	enum class ETraceTypeQuery : uint8_t
	{
		TraceTypeQuery1 = 0,
		TraceTypeQuery2 = 1,
		TraceTypeQuery3 = 2,
		TraceTypeQuery4 = 3,
		TraceTypeQuery5 = 4,
		TraceTypeQuery6 = 5,
		TraceTypeQuery7 = 6,
		TraceTypeQuery8 = 7,
		TraceTypeQuery9 = 8,
		TraceTypeQuery10 = 9,
		TraceTypeQuery11 = 10,
		TraceTypeQuery12 = 11,
		TraceTypeQuery13 = 12,
		TraceTypeQuery14 = 13,
		TraceTypeQuery15 = 14,
		TraceTypeQuery16 = 15,
		TraceTypeQuery17 = 16,
		TraceTypeQuery18 = 17,
		TraceTypeQuery19 = 18,
		TraceTypeQuery20 = 19,
		TraceTypeQuery21 = 20,
		TraceTypeQuery22 = 21,
		TraceTypeQuery23 = 22,
		TraceTypeQuery24 = 23,
		TraceTypeQuery25 = 24,
		TraceTypeQuery26 = 25,
		TraceTypeQuery27 = 26,
		TraceTypeQuery28 = 27,
		TraceTypeQuery29 = 28,
		TraceTypeQuery30 = 29,
		TraceTypeQuery31 = 30,
		TraceTypeQuery32 = 31,
		TraceTypeQuery_MAX = 32,
		ETraceTypeQuery_MAX = 33
	};

	enum class EMoveComponentAction : uint8_t
	{
		Move = 0,
		Stop = 1,
		Return = 2,
		EMoveComponentAction_MAX = 3
	};

	enum class EQuitPreference : uint8_t
	{
		Quit = 0,
		Background = 1,
		EQuitPreference_MAX = 2
	};

	enum class ENetRole : uint8_t
	{
		ROLE_None = 0,
		ROLE_SimulatedProxy = 1,
		ROLE_AutonomousProxy = 2,
		ROLE_Authority = 3,
		ROLE_MAX = 4
	};

	enum class EAttachLocation : uint8_t
	{
		KeepRelativeOffset = 0,
		KeepWorldPosition = 1,
		SnapToTarget = 2,
		SnapToTargetIncludingScale = 3,
		EAttachLocation_MAX = 4
	};

	enum class EAttachmentRule : uint8_t
	{
		KeepRelative = 0,
		KeepWorld = 1,
		SnapToTarget = 2,
		EAttachmentRule_MAX = 3
	};

	enum class EDetachmentRule : uint8_t
	{
		KeepRelative = 0,
		KeepWorld = 1,
		EDetachmentRule_MAX = 2
	};

	enum class ENetDormancy : uint8_t
	{
		DORM_Never = 0,
		DORM_Awake = 1,
		DORM_DormantAll = 2,
		DORM_DormantPartial = 3,
		DORM_Initial = 4,
		DORN_MAX = 5,
		ENetDormancy_MAX = 6
	};

	enum class ESpawnActorCollisionHandlingMethod : uint8_t
	{
		Undefined = 0,
		AlwaysSpawn = 1,
		AdjustIfPossibleButAlwaysSpawn = 2,
		AdjustIfPossibleButDontSpawnIfColliding = 3,
		DontSpawnIfColliding = 4,
		ESpawnActorCollisionHandlingMethod_MAX = 5
	};

	enum class EInputConsumeOptions : uint8_t
	{
		ICO_ConsumeAll = 0,
		ICO_ConsumeBoundKeys = 1,
		ICO_ConsumeNone = 2,
		ICO_MAX = 3
	};

	enum class EAutoReceiveInput : uint8_t
	{
		Disabled = 0,
		Player0 = 1,
		Player1 = 2,
		Player2 = 3,
		Player3 = 4,
		Player4 = 5,
		Player5 = 6,
		Player6 = 7,
		Player7 = 8,
		EAutoReceiveInput_MAX = 9
	};

	enum class ERotatorQuantization : uint8_t
	{
		ByteComponents = 0,
		ShortComponents = 1,
		ERotatorQuantization_MAX = 2
	};

	enum class EVectorQuantization : uint8_t
	{
		RoundWholeNumber = 0,
		RoundOneDecimal = 1,
		RoundTwoDecimals = 2,
		EVectorQuantization_MAX = 3
	};

	enum class EMeshBufferAccess : uint8_t
	{
		Default = 0,
		ForceCPUAndGPU = 1,
		EMeshBufferAccess_MAX = 2
	};

	enum class EConstraintFrame : uint8_t
	{
		Frame1 = 0,
		Frame2 = 1,
		EConstraintFrame_MAX = 2
	};

	enum class EAngularConstraintMotion : uint8_t
	{
		ACM_Free = 0,
		ACM_Limited = 1,
		ACM_Locked = 2,
		ACM_MAX = 3
	};

	enum class EComponentSocketType : uint8_t
	{
		Invalid = 0,
		Bone = 1,
		Socket = 2,
		EComponentSocketType_MAX = 3
	};

	enum class EComponentMobility : uint8_t
	{
		Static = 0,
		Stationary = 1,
		Movable = 2,
		EComponentMobility_MAX = 3
	};

	enum class EPhysicalSurface : uint8_t
	{
		SurfaceType_Default = 0,
		SurfaceType1 = 1,
		SurfaceType2 = 2,
		SurfaceType3 = 3,
		SurfaceType4 = 4,
		SurfaceType5 = 5,
		SurfaceType6 = 6,
		SurfaceType7 = 7,
		SurfaceType8 = 8,
		SurfaceType9 = 9,
		SurfaceType10 = 10,
		SurfaceType11 = 11,
		SurfaceType12 = 12,
		SurfaceType13 = 13,
		SurfaceType14 = 14,
		SurfaceType15 = 15,
		SurfaceType16 = 16,
		SurfaceType17 = 17,
		SurfaceType18 = 18,
		SurfaceType19 = 19,
		SurfaceType20 = 20,
		SurfaceType21 = 21,
		SurfaceType22 = 22,
		SurfaceType23 = 23,
		SurfaceType24 = 24,
		SurfaceType25 = 25,
		SurfaceType26 = 26,
		SurfaceType27 = 27,
		SurfaceType28 = 28,
		SurfaceType29 = 29,
		SurfaceType30 = 30,
		SurfaceType31 = 31,
		SurfaceType32 = 32,
		SurfaceType33 = 33,
		SurfaceType34 = 34,
		SurfaceType35 = 35,
		SurfaceType36 = 36,
		SurfaceType37 = 37,
		SurfaceType38 = 38,
		SurfaceType39 = 39,
		SurfaceType40 = 40,
		SurfaceType41 = 41,
		SurfaceType42 = 42,
		SurfaceType43 = 43,
		SurfaceType44 = 44,
		SurfaceType45 = 45,
		SurfaceType46 = 46,
		SurfaceType47 = 47,
		SurfaceType48 = 48,
		SurfaceType49 = 49,
		SurfaceType50 = 50,
		SurfaceType51 = 51,
		SurfaceType52 = 52,
		SurfaceType53 = 53,
		SurfaceType54 = 54,
		SurfaceType55 = 55,
		SurfaceType56 = 56,
		SurfaceType57 = 57,
		SurfaceType58 = 58,
		SurfaceType59 = 59,
		SurfaceType60 = 60,
		SurfaceType61 = 61,
		SurfaceType62 = 62,
		SurfaceType_Max = 63,
		EPhysicalSurface_MAX = 64
	};

	enum class EWalkableSlopeBehavior : uint8_t
	{
		WalkableSlope_Default = 0,
		WalkableSlope_Increase = 1,
		WalkableSlope_Decrease = 2,
		WalkableSlope_Unwalkable = 3,
		WalkableSlope_Max = 4
	};

	enum class EAutoPossessAI : uint8_t
	{
		Disabled = 0,
		PlacedInWorld = 1,
		Spawned = 2,
		PlacedInWorldOrSpawned = 3,
		EAutoPossessAI_MAX = 4
	};

	enum class EUpdateRateShiftBucket : uint8_t
	{
		ShiftBucket0 = 0,
		ShiftBucket1 = 1,
		ShiftBucket2 = 2,
		ShiftBucket3 = 3,
		ShiftBucket4 = 4,
		ShiftBucket5 = 5,
		ShiftBucketMax = 6,
		EUpdateRateShiftBucket_MAX = 7
	};

	enum class EShadowMapFlags : uint8_t
	{
		SMF_None = 0,
		SMF_Streamed = 1,
		SMF_MAX = 2
	};

	enum class ELightMapPaddingType : uint8_t
	{
		LMPT_NormalPadding = 0,
		LMPT_PrePadding = 1,
		LMPT_NoPadding = 2,
		LMPT_MAX = 3
	};

	enum class ECollisionEnabled : uint8_t
	{
		NoCollision = 0,
		QueryOnly = 1,
		PhysicsOnly = 2,
		QueryAndPhysics = 3,
		ECollisionEnabled_MAX = 4
	};

	enum class ETimelineSigType : uint8_t
	{
		ETS_EventSignature = 0,
		ETS_FloatSignature = 1,
		ETS_VectorSignature = 2,
		ETS_LinearColorSignature = 3,
		ETS_InvalidSignature = 4,
		ETS_MAX = 5
	};

	enum class ESleepFamily : uint8_t
	{
		Normal = 0,
		Sensitive = 1,
		Custom = 2,
		ESleepFamily_MAX = 3
	};

	enum class ERadialImpulseFalloff : uint8_t
	{
		RIF_Constant = 0,
		RIF_Linear = 1,
		RIF_MAX = 2
	};

	enum class EFilterInterpolationType : uint8_t
	{
		BSIT_Average = 0,
		BSIT_Linear = 1,
		BSIT_Cubic = 2,
		BSIT_MAX = 3
	};

	enum class ECollisionResponse : uint8_t
	{
		ECR_Ignore = 0,
		ECR_Overlap = 1,
		ECR_Block = 2,
		ECR_MAX = 3
	};

	enum class EPhysicsSceneType : uint8_t
	{
		PST_Sync = 0,
		PST_Cloth = 1,
		PST_Async = 2,
		PST_MAX = 3
	};

	enum class EOverlapFilterOption : uint8_t
	{
		OverlapFilter_All = 0,
		OverlapFilter_DynamicOnly = 1,
		OverlapFilter_StaticOnly = 2,
		OverlapFilter_MAX = 3
	};

	enum class ECollisionChannel : uint8_t
	{
		ECC_WorldStatic = 0,
		ECC_WorldDynamic = 1,
		ECC_Pawn = 2,
		ECC_Visibility = 3,
		ECC_Camera = 4,
		ECC_PhysicsBody = 5,
		ECC_Vehicle = 6,
		ECC_Destructible = 7,
		ECC_EngineTraceChannel1 = 8,
		ECC_EngineTraceChannel2 = 9,
		ECC_EngineTraceChannel3 = 10,
		ECC_EngineTraceChannel4 = 11,
		ECC_EngineTraceChannel5 = 12,
		ECC_EngineTraceChannel6 = 13,
		ECC_GameTraceChannel1 = 14,
		ECC_GameTraceChannel2 = 15,
		ECC_GameTraceChannel3 = 16,
		ECC_GameTraceChannel4 = 17,
		ECC_GameTraceChannel5 = 18,
		ECC_GameTraceChannel6 = 19,
		ECC_GameTraceChannel7 = 20,
		ECC_GameTraceChannel8 = 21,
		ECC_GameTraceChannel9 = 22,
		ECC_GameTraceChannel10 = 23,
		ECC_GameTraceChannel11 = 24,
		ECC_GameTraceChannel12 = 25,
		ECC_GameTraceChannel13 = 26,
		ECC_GameTraceChannel14 = 27,
		ECC_GameTraceChannel15 = 28,
		ECC_GameTraceChannel16 = 29,
		ECC_GameTraceChannel17 = 30,
		ECC_GameTraceChannel18 = 31,
		ECC_OverlapAll_Deprecated = 32,
		ECC_MAX = 33
	};

	enum class ENetworkSmoothingMode : uint8_t
	{
		Disabled = 0,
		Linear = 1,
		Exponential = 2,
		Replay = 3,
		ENetworkSmoothingMode_MAX = 4
	};

	enum class ETriangleSortAxis : uint8_t
	{
		TSA_X_Axis = 0,
		TSA_Y_Axis = 1,
		TSA_Z_Axis = 2,
		TSA_MAX = 3
	};

	enum class ETriangleSortOption : uint8_t
	{
		TRISORT_None = 0,
		TRISORT_CenterRadialDistance = 1,
		TRISORT_Random = 2,
		TRISORT_MergeContiguous = 3,
		TRISORT_Custom = 4,
		TRISORT_CustomLeftRight = 5,
		TRISORT_MAX = 6
	};

	enum class ELightingBuildQuality : uint8_t
	{
		Quality_Preview = 0,
		Quality_Medium = 1,
		Quality_High = 2,
		Quality_Production = 3,
		Quality_MAX = 4
	};

	enum class EMaterialSamplerType : uint8_t
	{
		SAMPLERTYPE_Color = 0,
		SAMPLERTYPE_Grayscale = 1,
		SAMPLERTYPE_Alpha = 2,
		SAMPLERTYPE_Normal = 3,
		SAMPLERTYPE_Masks = 4,
		SAMPLERTYPE_DistanceFieldFont = 5,
		SAMPLERTYPE_LinearColor = 6,
		SAMPLERTYPE_LinearGrayscale = 7,
		SAMPLERTYPE_MAX = 8
	};

	enum class EMaterialTessellationMode : uint8_t
	{
		MTM_NoTessellation = 0,
		MTM_FlatTessellation = 1,
		MTM_PNTriangles = 2,
		MTM_MAX = 3
	};

	enum class EMaterialShadingModel : uint8_t
	{
		MSM_Unlit = 0,
		MSM_DefaultLit = 1,
		MSM_Subsurface = 2,
		MSM_PreintegratedSkin = 3,
		MSM_ClearCoat = 4,
		MSM_SubsurfaceProfile = 5,
		MSM_TwoSidedFoliage = 6,
		MSM_Hair = 7,
		MSM_Cloth = 8,
		MSM_Eye = 9,
		MSM_MAX = 10
	};

	enum class EParticleCollisionMode : uint8_t
	{
		SceneDepth = 0,
		DistanceField = 1,
		EParticleCollisionMode_MAX = 2
	};

	enum class ETrailWidthMode : uint8_t
	{
		ETrailWidthMode_FromCentre = 0,
		ETrailWidthMode_FromFirst = 1,
		ETrailWidthMode_FromSecond = 2,
		ETrailWidthMode_MAX = 3
	};

	enum class EGBufferFormat : uint8_t
	{
		Force8BitsPerChannel = 0,
		Default = 1,
		HighPrecisionNormals = 2,
		Force16BitsPerChannel = 3,
		EGBufferFormat_MAX = 4
	};

	enum class ESceneCaptureCompositeMode : uint8_t
	{
		SCCM_Overwrite = 0,
		SCCM_Additive = 1,
		SCCM_Composite = 2,
		SCCM_MAX = 3
	};

	enum class ESceneCaptureSource : uint8_t
	{
		SCS_SceneColorHDR = 0,
		SCS_SceneColorHDRNoAlpha = 1,
		SCS_FinalColorLDR = 2,
		SCS_SceneColorSceneDepth = 3,
		SCS_SceneDepth = 4,
		SCS_Normal = 5,
		SCS_BaseColor = 6,
		SCS_MAX = 7
	};

	enum class ETranslucentSortPolicy : uint8_t
	{
		SortByDistance = 0,
		SortByProjectedZ = 1,
		SortAlongAxis = 2,
		ETranslucentSortPolicy_MAX = 3
	};

	enum class ERefractionMode : uint8_t
	{
		RM_IndexOfRefraction = 0,
		RM_PixelNormalOffset = 1,
		RM_MAX = 2
	};

	enum class ETranslucencyLightingMode : uint8_t
	{
		TLM_VolumetricNonDirectional = 0,
		TLM_VolumetricDirectional = 1,
		TLM_VolumetricPerVertexNonDirectional = 2,
		TLM_VolumetricPerVertexDirectional = 3,
		TLM_Surface = 4,
		TLM_SurfacePerPixelLighting = 5,
		TLM_MAX = 6
	};

	enum class ESamplerSourceMode : uint8_t
	{
		SSM_FromTextureAsset = 0,
		SSM_Wrap_WorldGroupSettings = 1,
		SSM_Clamp_WorldGroupSettings = 2,
		SSM_MAX = 3
	};

	enum class EBlendMode : uint8_t
	{
		BLEND_Opaque = 0,
		BLEND_Masked = 1,
		BLEND_Translucent = 2,
		BLEND_Additive = 3,
		BLEND_Modulate = 4,
		BLEND_AlphaComposite = 5,
		BLEND_MAX = 6
	};

	enum class EOcclusionCombineMode : uint8_t
	{
		OCM_Minimum = 0,
		OCM_Multiply = 1,
		OCM_MAX = 2
	};

	enum class EIndirectLightingCacheQuality : uint8_t
	{
		ILCQ_Off = 0,
		ILCQ_Point = 1,
		ILCQ_Volume = 2,
		ILCQ_MAX = 3
	};

	enum class ESceneDepthPriorityGroup : uint8_t
	{
		SDPG_World = 0,
		SDPG_Foreground = 1,
		SDPG_MAX = 2
	};

	enum class EActorMetricsType : uint8_t
	{
		METRICS_VERTS = 0,
		METRICS_TRIS = 1,
		METRICS_SECTIONS = 2,
		METRICS_MAX = 3
	};

	enum class EAspectRatioAxisConstraint : uint8_t
	{
		AspectRatio_MaintainYFOV = 0,
		AspectRatio_MaintainXFOV = 1,
		AspectRatio_MajorAxisFOV = 2,
		AspectRatio_MAX = 3
	};

	enum class EViewModeIndex : uint8_t
	{
		VMI_BrushWireframe = 0,
		VMI_Wireframe = 1,
		VMI_Unlit = 2,
		VMI_Lit = 3,
		VMI_Lit_DetailLighting = 4,
		VMI_LightingOnly = 5,
		VMI_LightComplexity = 6,
		VMI_ShaderComplexity = 7,
		VMI_LightmapDensity = 8,
		VMI_LitLightmapDensity = 9,
		VMI_ReflectionOverride = 10,
		VMI_VisualizeBuffer = 11,
		VMI_StationaryLightOverlap = 12,
		VMI_CollisionPawn = 13,
		VMI_CollisionVisibility = 14,
		VMI_LODColoration = 15,
		VMI_QuadOverdraw = 16,
		VMI_PrimitiveDistanceAccuracy = 17,
		VMI_MeshUVDensityAccuracy = 18,
		VMI_ShaderComplexityWithQuadOverdraw = 19,
		VMI_HLODColoration = 20,
		VMI_GroupLODColoration = 21,
		VMI_MaterialTextureScaleAccuracy = 22,
		VMI_RequiredTextureResolution = 23,
		VMI_Max = 24,
		VMI_Unknown = 25
	};

	enum class EDemoPlayFailure : uint8_t
	{
		Generic = 0,
		DemoNotFound = 1,
		Corrupt = 2,
		InvalidVersion = 3,
		EDemoPlayFailure_MAX = 4
	};

	enum class ETravelType : uint8_t
	{
		TRAVEL_Absolute = 0,
		TRAVEL_Partial = 1,
		TRAVEL_Relative = 2,
		TRAVEL_MAX = 3
	};

	enum class ENetworkLagState : uint8_t
	{
		NotLagging = 0,
		Lagging = 1,
		ENetworkLagState_MAX = 2
	};

	enum class EMouseLockMode : uint8_t
	{
		DoNotLock = 0,
		LockOnCapture = 1,
		LockAlways = 2,
		EMouseLockMode_MAX = 3
	};

	enum class EMouseCaptureMode : uint8_t
	{
		NoCapture = 0,
		CapturePermanently = 1,
		CapturePermanently_IncludingInitialMouseDown = 2,
		CaptureDuringMouseDown = 3,
		CaptureDuringRightMouseDown = 4,
		EMouseCaptureMode_MAX = 5
	};

	enum class EInputEvent : uint8_t
	{
		IE_Pressed = 0,
		IE_Released = 1,
		IE_Repeat = 2,
		IE_DoubleClick = 3,
		IE_Axis = 4,
		IE_MAX = 5
	};

	enum class ENodeEnabledState : uint8_t
	{
		Enabled = 0,
		Disabled = 1,
		DevelopmentOnly = 2,
		ENodeEnabledState_MAX = 3
	};

	enum class ENodeAdvancedPins : uint8_t
	{
		NoPins = 0,
		Shown = 1,
		Hidden = 2,
		ENodeAdvancedPins_MAX = 3
	};

	enum class ENodeTitleType : uint8_t
	{
		FullTitle = 0,
		ListView = 1,
		EditableTitle = 2,
		MenuTitle = 3,
		MAX_TitleTypes = 4,
		ENodeTitleType_MAX = 5
	};

	enum class EEdGraphPinDirection : uint8_t
	{
		EGPD_Input = 0,
		EGPD_Output = 1,
		EGPD_MAX = 2
	};

	enum class EBlueprintPinStyleType : uint8_t
	{
		BPST_Original = 0,
		BPST_VariantA = 1,
		BPST_MAX = 2
	};

	enum class ERelativeTransformSpace : uint8_t
	{
		RTS_World = 0,
		RTS_Actor = 1,
		RTS_Component = 2,
		RTS_ParentBoneSpace = 3,
		RTS_MAX = 4
	};

	enum class EDetailMode : uint8_t
	{
		DM_Low = 0,
		DM_Medium = 1,
		DM_High = 2,
		DM_MAX = 3
	};

	enum class EMaterialMergeType : uint8_t
	{
		MaterialMergeType_Default = 0,
		MaterialMergeType_Simplygon = 1,
		MaterialMergeType_MAX = 2
	};

	enum class ETextureSizingType : uint8_t
	{
		TextureSizingType_UseSingleTextureSize = 0,
		TextureSizingType_UseAutomaticBiasedSizes = 1,
		TextureSizingType_UseManualOverrideTextureSize = 2,
		TextureSizingType_UseSimplygonAutomaticSizing = 3,
		TextureSizingType_MAX = 4
	};

	enum class EBrushType : uint8_t
	{
		Brush_Default = 0,
		Brush_Add = 1,
		Brush_Subtract = 2,
		Brush_MAX = 3
	};

	enum class ECsgOper : uint8_t
	{
		CSG_Active = 0,
		CSG_Add = 1,
		CSG_Subtract = 2,
		CSG_Intersect = 3,
		CSG_Deintersect = 4,
		CSG_None = 5,
		CSG_MAX = 6
	};

	enum class EReverbPreset : uint8_t
	{
		REVERB_Default = 0,
		REVERB_Bathroom = 1,
		REVERB_StoneRoom = 2,
		REVERB_Auditorium = 3,
		REVERB_ConcertHall = 4,
		REVERB_Cave = 5,
		REVERB_Hallway = 6,
		REVERB_StoneCorridor = 7,
		REVERB_Alley = 8,
		REVERB_Forest = 9,
		REVERB_City = 10,
		REVERB_Mountains = 11,
		REVERB_Quarry = 12,
		REVERB_Plain = 13,
		REVERB_ParkingLot = 14,
		REVERB_SewerPipe = 15,
		REVERB_Underwater = 16,
		REVERB_SmallRoom = 17,
		REVERB_MediumRoom = 18,
		REVERB_LargeRoom = 19,
		REVERB_MediumHall = 20,
		REVERB_LargeHall = 21,
		REVERB_Plate = 22,
		REVERB_MAX = 23
	};

	enum class EStreamingVolumeUsage : uint8_t
	{
		SVB_Loading = 0,
		SVB_LoadingAndVisibility = 1,
		SVB_VisibilityBlockingOnLoad = 2,
		SVB_BlockingOnLoad = 3,
		SVB_LoadingNotVisible = 4,
		SVB_MAX = 5
	};

	enum class ENavigationQueryResult : uint8_t
	{
		Invalid = 0,
		Error = 1,
		Fail = 2,
		Success = 3,
		ENavigationQueryResult_MAX = 4
	};

	enum class ENavDataGatheringModeConfig : uint8_t
	{
		Invalid = 0,
		Instant = 1,
		Lazy = 2,
		ENavDataGatheringModeConfig_MAX = 3
	};

	enum class ENavDataGatheringMode : uint8_t
	{
		Default = 0,
		Instant = 1,
		Lazy = 2,
		ENavDataGatheringMode_MAX = 3
	};

	enum class ENavigationOptionFlag : uint8_t
	{
		Default = 0,
		Enable = 1,
		Disable = 2,
		MAX = 3,
		ENavigationOptionFlag_MAX = 4
	};

	enum class EBlendableLocation : uint8_t
	{
		BL_AfterTonemapping = 0,
		BL_BeforeTonemapping = 1,
		BL_BeforeTranslucency = 2,
		BL_ReplacingTonemapper = 3,
		BL_MAX = 4
	};

	enum class EAutoExposureMethod : uint8_t
	{
		AEM_Histogram = 0,
		AEM_Basic = 1,
		AEM_MAX = 2
	};

	enum class EAntiAliasingMethod : uint8_t
	{
		AAM_None = 0,
		AAM_FXAA = 1,
		AAM_TemporalAA = 2,
		AAM_MSAA = 3,
		AAM_MAX = 4
	};

	enum class EDepthOfFieldMethod : uint8_t
	{
		DOFM_BokehDOF = 0,
		DOFM_Gaussian = 1,
		DOFM_CircleDOF = 2,
		DOFM_MAX = 3
	};

	enum class ECameraAnimPlaySpace : uint8_t
	{
		CameraLocal = 0,
		World = 1,
		UserDefined = 2,
		ECameraAnimPlaySpace_MAX = 3
	};

	enum class ECameraProjectionMode : uint8_t
	{
		Perspective = 0,
		Orthographic = 1,
		ECameraProjectionMode_MAX = 2
	};

	enum class EInitialOscillatorOffset : uint8_t
	{
		EOO_OffsetRandom = 0,
		EOO_OffsetZero = 1,
		EOO_MAX = 2
	};

	enum class EViewTargetBlendFunction : uint8_t
	{
		VTBlend_Linear = 0,
		VTBlend_Cubic = 1,
		VTBlend_EaseIn = 2,
		VTBlend_EaseOut = 3,
		VTBlend_EaseInOut = 4,
		VTBlend_MAX = 5
	};

	enum class EControllerAnalogStick : uint8_t
	{
		CAS_LeftStick = 0,
		CAS_RightStick = 1,
		CAS_MAX = 2
	};

	enum class ERichCurveExtrapolation : uint8_t
	{
		RCCE_Cycle = 0,
		RCCE_CycleWithOffset = 1,
		RCCE_Oscillate = 2,
		RCCE_Linear = 3,
		RCCE_Constant = 4,
		RCCE_None = 5,
		RCCE_MAX = 6
	};

	enum class ERichCurveTangentWeightMode : uint8_t
	{
		RCTWM_WeightedNone = 0,
		RCTWM_WeightedArrive = 1,
		RCTWM_WeightedLeave = 2,
		RCTWM_WeightedBoth = 3,
		RCTWM_MAX = 4
	};

	enum class ERichCurveTangentMode : uint8_t
	{
		RCTM_Auto = 0,
		RCTM_User = 1,
		RCTM_Break = 2,
		RCTM_None = 3,
		RCTM_MAX = 4
	};

	enum class ERichCurveInterpMode : uint8_t
	{
		RCIM_Linear = 0,
		RCIM_Constant = 1,
		RCIM_Cubic = 2,
		RCIM_None = 3,
		RCIM_MAX = 4
	};

	enum class EDynamicForceFeedbackAction : uint8_t
	{
		Start = 0,
		Update = 1,
		Stop = 2,
		EDynamicForceFeedbackAction_MAX = 3
	};

	enum class EStandbyType : uint8_t
	{
		STDBY_Rx = 0,
		STDBY_Tx = 1,
		STDBY_BadPing = 2,
		STDBY_MAX = 3
	};

	enum class EMeshMergeType : uint8_t
	{
		MeshMergeType_Default = 0,
		MeshMergeType_MergeActor = 1,
		MeshMergeType_MAX = 2
	};

	enum class EMeshLODSelectionType : uint8_t
	{
		AllLODs = 0,
		SpecificLOD = 1,
		CalculateLOD = 2,
		EMeshLODSelectionType_MAX = 3
	};

	enum class ELandscapeCullingPrecision : uint8_t
	{
		High = 0,
		Medium = 1,
		Low = 2,
		ELandscapeCullingPrecision_MAX = 3
	};

	enum class EMeshFeatureImportance : uint8_t
	{
		Off = 0,
		Lowest = 1,
		Low = 2,
		Normal = 3,
		High = 4,
		Highest = 5,
		EMeshFeatureImportance_MAX = 6
	};

	enum class EVisibilityAggressiveness : uint8_t
	{
		VIS_LeastAggressive = 0,
		VIS_ModeratelyAggressive = 1,
		VIS_MostAggressive = 2,
		VIS_Max = 3
	};

	enum class EDOFMode : uint8_t
	{
		Default = 0,
		SixDOF = 1,
		YZPlane = 2,
		XZPlane = 3,
		XYPlane = 4,
		CustomPlane = 5,
		None = 6,
		EDOFMode_MAX = 7
	};

	enum class EHasCustomNavigableGeometry : uint8_t
	{
		No = 0,
		Yes = 1,
		EvenIfNotCollidable = 2,
		DontExport = 3,
		EHasCustomNavigableGeometry_MAX = 4
	};

	enum class ECanBeCharacterBase : uint8_t
	{
		ECB_No = 0,
		ECB_Yes = 1,
		ECB_Owner = 2,
		ECB_MAX = 3
	};

	enum class ERuntimeGenerationType : uint8_t
	{
		Static = 0,
		DynamicModifiersOnly = 1,
		Dynamic = 2,
		LegacyGeneration = 3,
		ERuntimeGenerationType_MAX = 4
	};

	enum class ERecastPartitioning : uint8_t
	{
		Monotone = 0,
		Watershed = 1,
		ChunkyMonotone = 2,
		ERecastPartitioning_MAX = 3
	};

	enum class ENavCostDisplay : uint8_t
	{
		TotalCost = 0,
		HeuristicOnly = 1,
		RealCostOnly = 2,
		ENavCostDisplay_MAX = 3
	};

	enum class ENavLinkDirection : uint8_t
	{
		BothWays = 0,
		LeftToRight = 1,
		RightToLeft = 2,
		ENavLinkDirection_MAX = 3
	};

	enum class EParticleSystemOcclusionBoundsMethod : uint8_t
	{
		EPSOBM_None = 0,
		EPSOBM_ParticleBounds = 1,
		EPSOBM_CustomBounds = 2,
		EPSOBM_MAX = 3
	};

	enum class EParticleSystemLODMethod : uint8_t
	{
		PARTICLESYSTEMLODMETHOD_Automatic = 0,
		PARTICLESYSTEMLODMETHOD_DirectSet = 1,
		PARTICLESYSTEMLODMETHOD_ActivateAutomatic = 2,
		PARTICLESYSTEMLODMETHOD_MAX = 3
	};

	enum class EParticleSystemUpdateMode : uint8_t
	{
		EPSUM_RealTime = 0,
		EPSUM_FixedTime = 1,
		EPSUM_MAX = 2
	};

	enum class EParticleEventType : uint8_t
	{
		EPET_Any = 0,
		EPET_Spawn = 1,
		EPET_Death = 2,
		EPET_Collision = 3,
		EPET_Burst = 4,
		EPET_Blueprint = 5,
		EPET_MAX = 6
	};

	enum class EParticleReplayState : uint8_t
	{
		PRS_Disabled = 0,
		PRS_Capturing = 1,
		PRS_Replaying = 2,
		PRS_MAX = 3
	};

	enum class EParticleSysParamType : uint8_t
	{
		PSPT_None = 0,
		PSPT_Scalar = 1,
		PSPT_ScalarRand = 2,
		PSPT_Vector = 3,
		PSPT_VectorRand = 4,
		PSPT_Color = 5,
		PSPT_Actor = 6,
		PSPT_Material = 7,
		PSPT_MAX = 8
	};

	enum class EAnimLinkMethod : uint8_t
	{
		Absolute = 0,
		Relative = 1,
		Proportional = 2,
		EAnimLinkMethod_MAX = 3
	};

	enum class EAnimInterpolationType : uint8_t
	{
		Linear = 0,
		Step = 1,
		EAnimInterpolationType_MAX = 2
	};

	enum class ECurveBlendOption : uint8_t
	{
		MaxWeight = 0,
		NormalizeByWeight = 1,
		BlendByWeight = 2,
		ECurveBlendOption_MAX = 3
	};

	enum class EAdditiveAnimationType : uint8_t
	{
		AAT_None = 0,
		AAT_LocalSpaceBase = 1,
		AAT_RotationOffsetMeshSpace = 2,
		AAT_MAX = 3
	};

	enum class ENotifyFilterType : uint8_t
	{
		NoFiltering = 0,
		LOD = 1,
		ENotifyFilterType_MAX = 2
	};

	enum class EMontageNotifyTickType : uint8_t
	{
		Queued = 0,
		BranchingPoint = 1,
		EMontageNotifyTickType_MAX = 2
	};

	enum class EBoneRotationSource : uint8_t
	{
		BRS_KeepComponentSpaceRotation = 0,
		BRS_KeepLocalSpaceRotation = 1,
		BRS_CopyFromTarget = 2,
		BRS_MAX = 3
	};

	enum class EBoneControlSpace : uint8_t
	{
		BCS_WorldSpace = 0,
		BCS_ComponentSpace = 1,
		BCS_ParentBoneSpace = 2,
		BCS_BoneSpace = 3,
		BCS_MAX = 4
	};

	enum class EBoneAxis : uint8_t
	{
		BA_X = 0,
		BA_Y = 1,
		BA_Z = 2,
		BA_MAX = 3
	};

	enum class ESkeletalMeshOptimizationType : uint8_t
	{
		SMOT_NumOfTriangles = 0,
		SMOT_MaxDeviation = 1,
		SMOT_MAX = 2
	};

	enum class ESkeletalMeshOptimizationImportance : uint8_t
	{
		SMOI_Off = 0,
		SMOI_Lowest = 1,
		SMOI_Low = 2,
		SMOI_Normal = 3,
		SMOI_High = 4,
		SMOI_Highest = 5,
		SMOI_MAX = 6
	};

	enum class EAnimGroupRole : uint8_t
	{
		CanBeLeader = 0,
		AlwaysFollower = 1,
		AlwaysLeader = 2,
		TransitionLeader = 3,
		TransitionFollower = 4,
		EAnimGroupRole_MAX = 5
	};

	enum class ERootMotionMode : uint8_t
	{
		NoRootMotionExtraction = 0,
		IgnoreRootMotion = 1,
		RootMotionFromEverything = 2,
		RootMotionFromMontagesOnly = 3,
		ERootMotionMode_MAX = 4
	};

	enum class ERootMotionRootLock : uint8_t
	{
		RefPose = 0,
		AnimFirstFrame = 1,
		Zero = 2,
		ERootMotionRootLock_MAX = 3
	};

	enum class ERootMotionFinishVelocityMode : uint8_t
	{
		MaintainLastRootMotionVelocity = 0,
		SetVelocity = 1,
		ClampVelocity = 2,
		ERootMotionFinishVelocityMode_MAX = 3
	};

	enum class ERootMotionSourceSettingsFlags : uint8_t
	{
		UseSensitiveLiftoffCheck = 0,
		DisablePartialEndTick = 1,
		ERootMotionSourceSettingsFlags_MAX = 2
	};

	enum class ERootMotionSourceStatusFlags : uint8_t
	{
		Prepared = 0,
		Finished = 1,
		MarkedForRemoval = 2,
		ERootMotionSourceStatusFlags_MAX = 3
	};

	enum class ERootMotionAccumulateMode : uint8_t
	{
		Override = 0,
		Additive = 1,
		ERootMotionAccumulateMode_MAX = 2
	};

	enum class EBoneTranslationRetargetingMode : uint8_t
	{
		Animation = 0,
		Skeleton = 1,
		AnimationScaled = 2,
		AnimationRelative = 3,
		EBoneTranslationRetargetingMode_MAX = 4
	};

	enum class EAlphaBlendOption : uint8_t
	{
		Linear = 0,
		Cubic = 1,
		HermiteCubic = 2,
		Sinusoidal = 3,
		QuadraticInOut = 4,
		CubicInOut = 5,
		QuarticInOut = 6,
		QuinticInOut = 7,
		CircularIn = 8,
		CircularOut = 9,
		CircularInOut = 10,
		ExpIn = 11,
		ExpOut = 12,
		ExpInOut = 13,
		Custom = 14,
		EAlphaBlendOption_MAX = 15
	};

	enum class ETypeAdvanceAnim : uint8_t
	{
		ETAA_Default = 0,
		ETAA_Finished = 1,
		ETAA_Looped = 2,
		ETAA_MAX = 3
	};

	enum class EAnimNotifyEventType : uint8_t
	{
		Begin = 0,
		End = 1,
		EAnimNotifyEventType_MAX = 2
	};

	enum class ELinearConstraintMotion : uint8_t
	{
		LCM_Free = 0,
		LCM_Limited = 1,
		LCM_Locked = 2,
		LCM_MAX = 3
	};

	enum class EAngularDriveMode : uint8_t
	{
		SLERP = 0,
		TwistAndSwing = 1,
		EAngularDriveMode_MAX = 2
	};

	enum class EAttenuationShape : uint8_t
	{
		Sphere = 0,
		Capsule = 1,
		Box = 2,
		Cone = 3,
		EAttenuationShape_MAX = 4
	};

	enum class EAttenuationDistanceModel : uint8_t
	{
		Linear = 0,
		Logarithmic = 1,
		Inverse = 2,
		LogReverse = 3,
		NaturalSound = 4,
		Custom = 5,
		EAttenuationDistanceModel_MAX = 6
	};

	enum class ESoundSpatializationAlgorithm : uint8_t
	{
		SPATIALIZATION_Default = 0,
		SPATIALIZATION_HRTF = 1,
		SPATIALIZATION_MAX = 2
	};

	enum class ESoundDistanceCalc : uint8_t
	{
		SOUNDDISTANCE_Normal = 0,
		SOUNDDISTANCE_InfiniteXYPlane = 1,
		SOUNDDISTANCE_InfiniteXZPlane = 2,
		SOUNDDISTANCE_InfiniteYZPlane = 3,
		SOUNDDISTANCE_MAX = 4
	};

	enum class ESkyLightSourceType : uint8_t
	{
		SLS_CapturedScene = 0,
		SLS_SpecifiedCubemap = 1,
		SLS_MAX = 2
	};

	enum class EBoneSpaces : uint8_t
	{
		WorldSpace = 0,
		ComponentSpace = 1,
		EBoneSpaces_MAX = 2
	};

	enum class EMeshComponentUpdateFlag : uint8_t
	{
		AlwaysTickPoseAndRefreshBones = 0,
		AlwaysTickPose = 1,
		OnlyTickPoseWhenRendered = 2,
		EMeshComponentUpdateFlag_MAX = 3
	};
p
	enum class EPhysBodyOp : uint8_t
	{
		PBO_None = 0,
		PBO_Term = 1,
		PBO_Disable = 2,
		PBO_MAX = 3
	};

	enum class EBoneVisibilityStatus : uint8_t
	{
		BVS_HiddenByParent = 0,
		BVS_Visible = 1,
		BVS_ExplicitlyHidden = 2,
		BVS_MAX = 3
	};

	enum class EPhysicsTransformUpdateMode : uint8_t
	{
		SimulationUpatesComponentTransform = 0,
		ComponentTransformIsKinematic = 1,
		EPhysicsTransformUpdateMode_MAX = 2
	};

	enum class EAnimationMode : uint8_t
	{
		AnimationBlueprint = 0,
		AnimationSingleNode = 1,
		AnimationCustomMode = 2,
		EAnimationMode_MAX = 3
	};

	enum class EKinematicBonesUpdateToPhysics : uint8_t
	{
		SkipSimulatingBones = 0,
		SkipAllBones = 1,
		EKinematicBonesUpdateToPhysics_MAX = 2
	};

	enum class ESplineMeshAxis : uint8_t
	{
		X = 0,
		Y = 1,
		Z = 2,
		ESplineMeshAxis_MAX = 3
	};

	enum class ESplineCoordinateSpace : uint8_t
	{
		Local = 0,
		World = 1,
		ESplineCoordinateSpace_MAX = 2
	};

	enum class ESplinePointType : uint8_t
	{
		Linear = 0,
		Curve = 1,
		Constant = 2,
		CurveClamped = 3,
		CurveCustomTangent = 4,
		ESplinePointType_MAX = 5
	};

	enum class EVerticalTextAligment : uint8_t
	{
		EVRTA_TextTop = 0,
		EVRTA_TextCenter = 1,
		EVRTA_TextBottom = 2,
		EVRTA_QuadTop = 3,
		EVRTA_MAX = 4
	};

	enum class EHorizTextAligment : uint8_t
	{
		EHTA_Left = 0,
		EHTA_Center = 1,
		EHTA_Right = 2,
		EHTA_MAX = 3
	};

	enum class EReflectionSourceType : uint8_t
	{
		CapturedScene = 0,
		SpecifiedCubemap = 1,
		EReflectionSourceType_MAX = 2
	};

	enum class EStereoLayerShape : uint8_t
	{
		SLSH_QuadLayer = 0,
		SLSH_CylinderLayer = 1,
		SLSH_CubemapLayer = 2,
		SLSH_MAX = 3
	};

	enum class EStereoLayerType : uint8_t
	{
		SLT_WorldLocked = 0,
		SLT_TrackerLocked = 1,
		SLT_FaceLocked = 2,
		SLT_MAX = 3
	};

	enum class EWindSourceType : uint8_t
	{
		Directional = 0,
		Point = 1,
		EWindSourceType_MAX = 2
	};

	enum class ETimelineDirection : uint8_t
	{
		Forward = 0,
		Backward = 1,
		ETimelineDirection_MAX = 2
	};

	enum class ETimelineLengthMode : uint8_t
	{
		TL_TimelineLength = 0,
		TL_LastKeyFrame = 1,
		TL_MAX = 2
	};

	enum class EAdditiveBasePoseType : uint8_t
	{
		ABPT_None = 0,
		ABPT_RefPose = 1,
		ABPT_AnimScaled = 2,
		ABPT_AnimFrame = 3,
		ABPT_MAX = 4
	};

	enum class EAnimationKeyFormat : uint8_t
	{
		AKF_ConstantKeyLerp = 0,
		AKF_VariableKeyLerp = 1,
		AKF_PerTrackCompression = 2,
		AKF_MAX = 3
	};

	enum class EAnimationCompressionFormat : uint8_t
	{
		ACF_None = 0,
		ACF_Float96NoW = 1,
		ACF_Fixed48NoW = 2,
		ACF_IntervalFixed32NoW = 3,
		ACF_Fixed32NoW = 4,
		ACF_Float32NoW = 5,
		ACF_Identity = 6,
		ACF_MAX = 7
	};

	enum class ENotifyTriggerMode : uint8_t
	{
		AllAnimations = 0,
		HighestWeightedAnimation = 1,
		None = 2,
		ENotifyTriggerMode_MAX = 3
	};

	enum class EBlendSpaceAxis : uint8_t
	{
		BSA_None = 0,
		BSA_X = 1,
		BSA_Y = 2,
		BSA_Max = 3
	};

	enum class ETransitionLogicType : uint8_t
	{
		TLT_StandardBlend = 0,
		TLT_Custom = 1,
		TLT_MAX = 2
	};

	enum class ETransitionBlendMode : uint8_t
	{
		TBM_Linear = 0,
		TBM_Cubic = 1,
		TBM_MAX = 2
	};

	enum class EMontagePlayReturnType : uint8_t
	{
		MontageLength = 0,
		Duration = 1,
		EMontagePlayReturnType_MAX = 2
	};

	enum class EAnimCurveType : uint8_t
	{
		AttributeCurve = 0,
		MaterialCurve = 1,
		MorphTargetCurve = 2,
		MaxAnimCurveType = 3,
		EAnimCurveType_MAX = 4
	};

	enum class EPrimaryAssetCookRule : uint8_t
	{
		Unknown = 0,
		NeverCook = 1,
		DevelopmentCook = 2,
		AlwaysCook = 3,
		EPrimaryAssetCookRule_MAX = 4
	};

	enum class EBlueprintNativizationFlag : uint8_t
	{
		Disabled = 0,
		Dependency = 1,
		ExplicitlyEnabled = 2,
		EBlueprintNativizationFlag_MAX = 3
	};

	enum class EBlueprintCompileMode : uint8_t
	{
		Default = 0,
		Development = 1,
		FinalRelease = 2,
		EBlueprintCompileMode_MAX = 3
	};

	enum class EBlueprintType : uint8_t
	{
		BPTYPE_Normal = 0,
		BPTYPE_Const = 1,
		BPTYPE_MacroLibrary = 2,
		BPTYPE_Interface = 3,
		BPTYPE_LevelScript = 4,
		BPTYPE_FunctionLibrary = 5,
		BPTYPE_MAX = 6
	};

	enum class EBlueprintStatus : uint8_t
	{
		BS_Unknown = 0,
		BS_Dirty = 1,
		BS_Error = 2,
		BS_UpToDate = 3,
		BS_BeingCreated = 4,
		BS_UpToDateWithWarnings = 5,
		BS_MAX = 6
	};

	enum class EEvaluateCurveTableResult : uint8_t
	{
		RowFound = 0,
		RowNotFound = 1,
		EEvaluateCurveTableResult_MAX = 2
	};

	enum class EGrammaticalNumber : uint8_t
	{
		Singular = 0,
		Plural = 1,
		EGrammaticalNumber_MAX = 2
	};

	enum class EGrammaticalGender : uint8_t
	{
		Neuter = 0,
		Masculine = 1,
		Feminine = 2,
		Mixed = 3,
		EGrammaticalGender_MAX = 4
	};

	enum class ESuggestProjVelocityTraceOption : uint8_t
	{
		DoNotTrace = 0,
		TraceFullPath = 1,
		OnlyTraceWhileAscending = 2,
		ESuggestProjVelocityTraceOption_MAX = 3
	};

	enum class EHMDWornState : uint8_t
	{
		Unknown = 0,
		Worn = 1,
		NotWorn = 2,
		EHMDWornState_MAX = 3
	};

	enum class EHMDTrackingOrigin : uint8_t
	{
		Floor = 0,
		Eye = 1,
		EHMDTrackingOrigin_MAX = 2
	};

	enum class EOrientPositionSelector : uint8_t
	{
		Orientation = 0,
		Position = 1,
		OrientationAndPosition = 2,
		EOrientPositionSelector_MAX = 3
	};

	enum class ELerpInterpolationMode : uint8_t
	{
		QuatInterp = 0,
		EulerInterp = 1,
		DualQuatInterp = 2,
		ELerpInterpolationMode_MAX = 3
	};

	enum class EEasingFunc : uint8_t
	{
		Linear = 0,
		Step = 1,
		SinusoidalIn = 2,
		SinusoidalOut = 3,
		SinusoidalInOut = 4,
		EaseIn = 5,
		EaseOut = 6,
		EaseInOut = 7,
		ExpoIn = 8,
		ExpoOut = 9,
		ExpoInOut = 10,
		CircularIn = 11,
		CircularOut = 12,
		CircularInOut = 13,
		EEasingFunc_MAX = 14
	};

	enum class ERoundingMode : uint8_t
	{
		HalfToEven = 0,
		HalfFromZero = 1,
		HalfToZero = 2,
		FromZero = 3,
		ToZero = 4,
		ToNegativeInfinity = 5,
		ToPositiveInfinity = 6,
		ERoundingMode_MAX = 7
	};

	enum class EFNavigationSystemRunMode : uint8_t
	{
		InvalidMode = 0,
		GameMode = 1,
		EditorMode = 2,
		SimulationMode = 3,
		PIEMode = 4,
		FNavigationSystemRunMode_MAX = 5
	};

	enum class EBodyCollisionResponse : uint8_t
	{
		BodyCollision_Enabled = 0,
		BodyCollision_Disabled = 1,
		BodyCollision_MAX = 2
	};

	enum class EPhysicsType : uint8_t
	{
		PhysType_Default = 0,
		PhysType_Kinematic = 1,
		PhysType_Simulated = 2,
		PhysType_MAX = 3
	};

	enum class ECollisionTraceFlag : uint8_t
	{
		CTF_UseDefault = 0,
		CTF_UseSimpleAndComplex = 1,
		CTF_UseSimpleAsComplex = 2,
		CTF_UseComplexAsSimple = 3,
		CTF_MAX = 4
	};

	enum class EFrictionCombineMode : uint8_t
	{
		Average = 0,
		Min = 1,
		Multiply = 2,
		Max = 3,
		EFrictionCombineMode_MAX = 4
	};

	enum class ESettingsLockedAxis : uint8_t
	{
		None = 0,
		X = 1,
		Y = 2,
		Z = 3,
		Invalid = 4,
		ESettingsLockedAxis_MAX = 5
	};

	enum class ESettingsDOF : uint8_t
	{
		Full3D = 0,
		YZPlane = 1,
		XZPlane = 2,
		XYPlane = 3,
		ESettingsDOF_MAX = 4
	};

	enum class EAutoExposureMethodUI : uint8_t
	{
		AEM_Histogram = 0,
		AEM_Basic = 1,
		AEM_MAX = 2
	};

	enum class EEarlyZPass : uint8_t
	{
		None = 0,
		OpaqueOnly = 1,
		OpaqueAndMasked = 2,
		Auto = 3,
		EEarlyZPass_MAX = 4
	};

	enum class ECustomDepthStencil : uint8_t
	{
		Disabled = 0,
		Enabled = 1,
		EnabledOnDemand = 2,
		EnabledWithStencil = 3,
		ECustomDepthStencil_MAX = 4
	};

	enum class EMobileMSAASampleCount : uint8_t
	{
		One = 0,
		Two = 1,
		Four = 2,
		Eight = 3,
		EMobileMSAASampleCount_MAX = 4
	};

	enum class ECompositingSampleCount : uint8_t
	{
		One = 0,
		Two = 1,
		Four = 2,
		Eight = 3,
		ECompositingSampleCount_MAX = 4
	};

	enum class EClearSceneOptions : uint8_t
	{
		NoClear = 0,
		HardwareClear = 1,
		QuadAtMaxZ = 2,
		EClearSceneOptions_MAX = 3
	};

	enum class EUIScalingRule : uint8_t
	{
		ShortestSide = 0,
		LongestSide = 1,
		Horizontal = 2,
		Vertical = 3,
		Custom = 4,
		EUIScalingRule_MAX = 5
	};

	enum class ERenderFocusRule : uint8_t
	{
		Always = 0,
		NonPointer = 1,
		NavigationOnly = 2,
		Never = 3,
		ERenderFocusRule_MAX = 4
	};

	enum class EDistributionParamMode : uint8_t
	{
		DPM_Normal = 0,
		DPM_Abs = 1,
		DPM_Direct = 2,
		DPM_MAX = 3
	};

	enum class EDistributionVectorMirrorFlags : uint8_t
	{
		EDVMF_Same = 0,
		EDVMF_Different = 1,
		EDVMF_Mirror = 2,
		EDVMF_MAX = 3
	};

	enum class EDistributionVectorLockFlags : uint8_t
	{
		EDVLF_None = 0,
		EDVLF_XY = 1,
		EDVLF_XZ = 2,
		EDVLF_YZ = 3,
		EDVLF_XYZ = 4,
		EDVLF_MAX = 5
	};

	enum class ECanCreateConnectionResponse : uint8_t
	{
		CONNECT_RESPONSE_MAKE = 0,
		CONNECT_RESPONSE_DISALLOW = 1,
		CONNECT_RESPONSE_BREAK_OTHERS_A = 2,
		CONNECT_RESPONSE_BREAK_OTHERS_B = 3,
		CONNECT_RESPONSE_BREAK_OTHERS_AB = 4,
		CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE = 5,
		CONNECT_RESPONSE_MAX = 6
	};

	enum class EGraphType : uint8_t
	{
		GT_Function = 0,
		GT_Ubergraph = 1,
		GT_Macro = 2,
		GT_Animation = 3,
		GT_StateMachine = 4,
		GT_MAX = 5
	};

	enum class EConsoleType : uint8_t
	{
		CONSOLE_Any = 0,
		CONSOLE_Mobile = 1,
		CONSOLE_MAX = 2
	};

	enum class ETransitionType : uint8_t
	{
		TT_None = 0,
		TT_Paused = 1,
		TT_Loading = 2,
		TT_Saving = 3,
		TT_Connecting = 4,
		TT_Precaching = 5,
		TT_WaitingToConnect = 6,
		TT_MAX = 7
	};

	enum class EFullyLoadPackageType : uint8_t
	{
		FULLYLOAD_Map = 0,
		FULLYLOAD_Game_PreLoadClass = 1,
		FULLYLOAD_Game_PostLoadClass = 2,
		FULLYLOAD_Always = 3,
		FULLYLOAD_Mutator = 4,
		FULLYLOAD_MAX = 5
	};

	enum class EFontImportCharacterSet : uint8_t
	{
		FontICS_Default = 0,
		FontICS_Ansi = 1,
		FontICS_Symbol = 2,
		FontICS_MAX = 3
	};

	enum class EFontCacheType : uint8_t
	{
		Offline = 0,
		Runtime = 1,
		EFontCacheType_MAX = 2
	};

	enum class EWindowMode : uint8_t
	{
		Fullscreen = 0,
		WindowedFullscreen = 1,
		Windowed = 2,
		EWindowMode_MAX = 3
	};

	enum class ETrackActiveCondition : uint8_t
	{
		ETAC_Always = 0,
		ETAC_GoreEnabled = 1,
		ETAC_GoreDisabled = 2,
		ETAC_MAX = 3
	};

	enum class EInterpTrackMoveRotMode : uint8_t
	{
		IMR_Keyframed = 0,
		IMR_LookAtGroup = 1,
		IMR_Ignore = 2,
		IMR_MAX = 3
	};

	enum class EInterpMoveAxis : uint8_t
	{
		AXIS_TranslationX = 0,
		AXIS_TranslationY = 1,
		AXIS_TranslationZ = 2,
		AXIS_RotationX = 3,
		AXIS_RotationY = 4,
		AXIS_RotationZ = 5,
		AXIS_MAX = 6
	};

	enum class ETrackToggleAction : uint8_t
	{
		ETTA_Off = 0,
		ETTA_On = 1,
		ETTA_Toggle = 2,
		ETTA_Trigger = 3,
		ETTA_MAX = 4
	};

	enum class EVisibilityTrackCondition : uint8_t
	{
		EVTC_Always = 0,
		EVTC_GoreEnabled = 1,
		EVTC_GoreDisabled = 2,
		EVTC_MAX = 3
	};

	enum class EVisibilityTrackAction : uint8_t
	{
		EVTA_Hide = 0,
		EVTA_Show = 1,
		EVTA_Toggle = 2,
		EVTA_MAX = 3
	};

	enum class EMaterialAttributeBlend : uint8_t
	{
		Blend = 0,
		UseA = 1,
		UseB = 2,
		EMaterialAttributeBlend_MAX = 3
	};

	enum class EClampMode : uint8_t
	{
		CMODE_Clamp = 0,
		CMODE_ClampMin = 1,
		CMODE_ClampMax = 2,
		CMODE_MAX = 3
	};

	enum class ECustomMaterialOutputType : uint8_t
	{
		CMOT_Float1 = 0,
		CMOT_Float2 = 1,
		CMOT_Float3 = 2,
		CMOT_Float4 = 3,
		CMOT_MAX = 4
	};

	enum class EDepthOfFieldFunctionValue : uint8_t
	{
		TDOF_NearAndFarMask = 0,
		TDOF_NearMask = 1,
		TDOF_FarMask = 2,
		TDOF_CircleOfConfusionRadius = 3,
		TDOF_MAX = 4
	};

	enum class EFunctionInputType : uint8_t
	{
		FunctionInput_Scalar = 0,
		FunctionInput_Vector2 = 1,
		FunctionInput_Vector3 = 2,
		FunctionInput_Vector4 = 3,
		FunctionInput_Texture2D = 4,
		FunctionInput_TextureCube = 5,
		FunctionInput_StaticBool = 6,
		FunctionInput_MaterialAttributes = 7,
		FunctionInput_MAX = 8
	};

	enum class ENoiseFunction : uint8_t
	{
		NOISEFUNCTION_SimplexTex = 0,
		NOISEFUNCTION_GradientTex = 1,
		NOISEFUNCTION_GradientTex3D = 2,
		NOISEFUNCTION_GradientALU = 3,
		NOISEFUNCTION_ValueALU = 4,
		NOISEFUNCTION_VoronoiALU = 5,
		NOISEFUNCTION_MAX = 6
	};

	enum class EMaterialSceneAttributeInputMode : uint8_t
	{
		Coordinates = 0,
		OffsetFraction = 1,
		EMaterialSceneAttributeInputMode_MAX = 2
	};

	enum class ESceneTextureId : uint8_t
	{
		PPI_SceneColor = 0,
		PPI_SceneDepth = 1,
		PPI_DiffuseColor = 2,
		PPI_SpecularColor = 3,
		PPI_SubsurfaceColor = 4,
		PPI_BaseColor = 5,
		PPI_Specular = 6,
		PPI_Metallic = 7,
		PPI_WorldNormal = 8,
		PPI_SeparateTranslucency = 9,
		PPI_Opacity = 10,
		PPI_Roughness = 11,
		PPI_MaterialAO = 12,
		PPI_CustomDepth = 13,
		PPI_PostProcessInput0 = 14,
		PPI_PostProcessInput1 = 15,
		PPI_PostProcessInput2 = 16,
		PPI_PostProcessInput3 = 17,
		PPI_PostProcessInput4 = 18,
		PPI_PostProcessInput5 = 19,
		PPI_PostProcessInput6 = 20,
		PPI_DecalMask = 21,
		PPI_ShadingModel = 22,
		PPI_AmbientOcclusion = 23,
		PPI_CustomStencil = 24,
		PPI_StoredBaseColor = 25,
		PPI_StoredSpecular = 26,
		PPI_MAX = 27
	};

	enum class EMaterialExpressionScreenPositionMapping : uint8_t
	{
		MESP_SceneTextureUV = 0,
		MESP_ViewportUV = 1,
		MESP_Max = 2
	};

	enum class ESpeedTreeLODType : uint8_t
	{
		STLOD_Pop = 0,
		STLOD_Smooth = 1,
		STLOD_MAX = 2
	};

	enum class ESpeedTreeWindType : uint8_t
	{
		STW_None = 0,
		STW_Fastest = 1,
		STW_Fast = 2,
		STW_Better = 3,
		STW_Best = 4,
		STW_Palm = 5,
		STW_BestPlus = 6,
		STW_MAX = 7
	};

	enum class ESpeedTreeGeometryType : uint8_t
	{
		STG_Branch = 0,
		STG_Frond = 1,
		STG_Leaf = 2,
		STG_FacingLeaf = 3,
		STG_Billboard = 4,
		STG_MAX = 5
	};

	enum class ETextureMipValueMode : uint8_t
	{
		TMVM_None = 0,
		TMVM_MipLevel = 1,
		TMVM_MipBias = 2,
		TMVM_Derivative = 3,
		TMVM_MAX = 4
	};

	enum class ETextureColorChannel : uint8_t
	{
		TCC_Red = 0,
		TCC_Green = 1,
		TCC_Blue = 2,
		TCC_Alpha = 3,
		TCC_MAX = 4
	};

	enum class EMaterialExposedTextureProperty : uint8_t
	{
		TMTM_TextureSize = 0,
		TMTM_TexelSize = 1,
		TMTM_MAX = 2
	};

	enum class EMaterialVectorCoordTransform : uint8_t
	{
		TRANSFORM_Tangent = 0,
		TRANSFORM_Local = 1,
		TRANSFORM_World = 2,
		TRANSFORM_View = 3,
		TRANSFORM_Camera = 4,
		TRANSFORM_ParticleWorld = 5,
		TRANSFORM_MAX = 6
	};

	enum class EMaterialVectorCoordTransformSource : uint8_t
	{
		TRANSFORMSOURCE_Tangent = 0,
		TRANSFORMSOURCE_Local = 1,
		TRANSFORMSOURCE_World = 2,
		TRANSFORMSOURCE_View = 3,
		TRANSFORMSOURCE_Camera = 4,
		TRANSFORMSOURCE_ParticleWorld = 5,
		TRANSFORMSOURCE_MAX = 6
	};

	enum class EMaterialPositionTransformSource : uint8_t
	{
		TRANSFORMPOSSOURCE_Local = 0,
		TRANSFORMPOSSOURCE_World = 1,
		TRANSFORMPOSSOURCE_TranslatedWorld = 2,
		TRANSFORMPOSSOURCE_View = 3,
		TRANSFORMPOSSOURCE_Camera = 4,
		TRANSFORMPOSSOURCE_Particle = 5,
		TRANSFORMPOSSOURCE_MAX = 6
	};

	enum class EVectorNoiseFunction : uint8_t
	{
		VNF_CellnoiseALU = 0,
		VNF_VectorALU = 1,
		VNF_GradientALU = 2,
		VNF_CurlALU = 3,
		VNF_VoronoiALU = 4,
		VNF_MAX = 5
	};

	enum class EMaterialExposedViewProperty : uint8_t
	{
		MEVP_BufferSize = 0,
		MEVP_FieldOfView = 1,
		MEVP_TanHalfFieldOfView = 2,
		MEVP_ViewSize = 3,
		MEVP_WorldSpaceViewPosition = 4,
		MEVP_WorldSpaceCameraPosition = 5,
		MEVP_MAX = 6
	};

	enum class EWorldPositionIncludedOffsets : uint8_t
	{
		WPT_Default = 0,
		WPT_ExcludeAllShaderOffsets = 1,
		WPT_CameraRelative = 2,
		WPT_CameraRelativeNoOffsets = 3,
		WPT_MAX = 4
	};

	enum class EMaterialDecalResponse : uint8_t
	{
		MDR_None = 0,
		MDR_ColorNormalRoughness = 1,
		MDR_Color = 2,
		MDR_ColorNormal = 3,
		MDR_ColorRoughness = 4,
		MDR_Normal = 5,
		MDR_NormalRoughness = 6,
		MDR_Roughness = 7,
		MDR_MAX = 8
	};

	enum class EMaterialDomain : uint8_t
	{
		MD_Surface = 0,
		MD_DeferredDecal = 1,
		MD_LightFunction = 2,
		MD_Volume = 3,
		MD_PostProcess = 4,
		MD_UI = 5,
		MD_MAX = 6
	};

	enum class EDecalBlendMode : uint8_t
	{
		DBM_Translucent = 0,
		DBM_Stain = 1,
		DBM_Normal = 2,
		DBM_Emissive = 3,
		DBM_DBuffer_ColorNormalRoughness = 4,
		DBM_DBuffer_Color = 5,
		DBM_DBuffer_ColorNormal = 6,
		DBM_DBuffer_ColorRoughness = 7,
		DBM_DBuffer_Normal = 8,
		DBM_DBuffer_NormalRoughness = 9,
		DBM_DBuffer_Roughness = 10,
		DBM_Volumetric_DistanceFunction = 11,
		DBM_MAX = 12
	};

	enum class EEmitterRenderMode : uint8_t
	{
		ERM_Normal = 0,
		ERM_Point = 1,
		ERM_Cross = 2,
		ERM_LightsOnly = 3,
		ERM_None = 4,
		ERM_MAX = 5
	};

	enum class EParticleSubUVInterpMethod : uint8_t
	{
		PSUVIM_None = 0,
		PSUVIM_Linear = 1,
		PSUVIM_Linear_Blend = 2,
		PSUVIM_Random = 3,
		PSUVIM_Random_Blend = 4,
		PSUVIM_MAX = 5
	};

	enum class EParticleBurstMethod : uint8_t
	{
		EPBM_Instant = 0,
		EPBM_Interpolated = 1,
		EPBM_MAX = 2
	};

	enum class EParticleScreenAlignment : uint8_t
	{
		PSA_FacingCameraPosition = 0,
		PSA_Square = 1,
		PSA_Rectangle = 2,
		PSA_Velocity = 3,
		PSA_AwayFromCenter = 4,
		PSA_TypeSpecific = 5,
		PSA_FacingCameraDistanceBlend = 6,
		PSA_MAX = 7
	};

	enum class EParticleSystemInsignificanceReaction : uint8_t
	{
		Auto = 0,
		Complete = 1,
		DisableTick = 2,
		DisableTickAndKill = 3,
		Num = 4,
		EParticleSystemInsignificanceReaction_MAX = 5
	};

	enum class EParticleSignificanceLevel : uint8_t
	{
		Low = 0,
		Medium = 1,
		High = 2,
		Critical = 3,
		Num = 4,
		EParticleSignificanceLevel_MAX = 5
	};

	enum class EParticleSourceSelectionMethod : uint8_t
	{
		EPSSM_Random = 0,
		EPSSM_Sequential = 1,
		EPSSM_MAX = 2
	};

	enum class EModuleType : uint8_t
	{
		EPMT_General = 0,
		EPMT_TypeData = 1,
		EPMT_Beam = 2,
		EPMT_Trail = 3,
		EPMT_Spawn = 4,
		EPMT_Required = 5,
		EPMT_Event = 6,
		EPMT_Light = 7,
		EPMT_SubUV = 8,
		EPMT_MAX = 9
	};

	enum class EAttractorParticleSelectionMethod : uint8_t
	{
		EAPSM_Random = 0,
		EAPSM_Sequential = 1,
		EAPSM_MAX = 2
	};

	enum class EBeam2SourceTargetTangentMethod : uint8_t
	{
		PEB2STTM_Direct = 0,
		PEB2STTM_UserSet = 1,
		PEB2STTM_Distribution = 2,
		PEB2STTM_Emitter = 3,
		PEB2STTM_MAX = 4
	};

	enum class EBeam2SourceTargetMethod : uint8_t
	{
		PEB2STM_Default = 0,
		PEB2STM_UserSet = 1,
		PEB2STM_Emitter = 2,
		PEB2STM_Particle = 3,
		PEB2STM_Actor = 4,
		PEB2STM_MAX = 5
	};

	enum class EBeamModifierType : uint8_t
	{
		PEB2MT_Source = 0,
		PEB2MT_Target = 1,
		PEB2MT_MAX = 2
	};

	enum class EParticleCameraOffsetUpdateMethod : uint8_t
	{
		EPCOUM_DirectSet = 0,
		EPCOUM_Additive = 1,
		EPCOUM_Scalar = 2,
		EPCOUM_MAX = 3
	};

	enum class EParticleCollisionComplete : uint8_t
	{
		EPCC_Kill = 0,
		EPCC_Freeze = 1,
		EPCC_HaltCollisions = 2,
		EPCC_FreezeTranslation = 3,
		EPCC_FreezeRotation = 4,
		EPCC_FreezeMovement = 5,
		EPCC_MAX = 6
	};

	enum class EParticleCollisionResponse : uint8_t
	{
		Bounce = 0,
		Stop = 1,
		Kill = 2,
		EParticleCollisionResponse_MAX = 3
	};

	enum class ELocationBoneSocketSelectionMethod : uint8_t
	{
		BONESOCKETSEL_Sequential = 0,
		BONESOCKETSEL_Random = 1,
		BONESOCKETSEL_MAX = 2
	};

	enum class ELocationBoneSocketSource : uint8_t
	{
		BONESOCKETSOURCE_Bones = 0,
		BONESOCKETSOURCE_Sockets = 1,
		BONESOCKETSOURCE_MAX = 2
	};

	enum class ELocationEmitterSelectionMethod : uint8_t
	{
		ELESM_Random = 0,
		ELESM_Sequential = 1,
		ELESM_MAX = 2
	};

	enum class ECylinderHeightAxis : uint8_t
	{
		PMLPC_HEIGHTAXIS_X = 0,
		PMLPC_HEIGHTAXIS_Y = 1,
		PMLPC_HEIGHTAXIS_Z = 2,
		PMLPC_HEIGHTAXIS_MAX = 3
	};

	enum class ELocationSkelVertSurfaceSource : uint8_t
	{
		VERTSURFACESOURCE_Vert = 0,
		VERTSURFACESOURCE_Surface = 1,
		VERTSURFACESOURCE_MAX = 2
	};

	enum class EOrbitChainMode : uint8_t
	{
		EOChainMode_Add = 0,
		EOChainMode_Scale = 1,
		EOChainMode_Link = 2,
		EOChainMode_MAX = 3
	};

	enum class EParticleAxisLock : uint8_t
	{
		EPAL_NONE = 0,
		EPAL_X = 1,
		EPAL_Y = 2,
		EPAL_Z = 3,
		EPAL_NEGATIVE_X = 4,
		EPAL_NEGATIVE_Y = 5,
		EPAL_NEGATIVE_Z = 6,
		EPAL_ROTATE_X = 7,
		EPAL_ROTATE_Y = 8,
		EPAL_ROTATE_Z = 9,
		EPAL_MAX = 10
	};

	enum class EEmitterDynamicParameterValue : uint8_t
	{
		EDPV_UserSet = 0,
		EDPV_AutoSet = 1,
		EDPV_VelocityX = 2,
		EDPV_VelocityY = 3,
		EDPV_VelocityZ = 4,
		EDPV_VelocityMag = 5,
		EDPV_MAX = 6
	};

	enum class EOpacitySourceMode : uint8_t
	{
		OSM_Alpha = 0,
		OSM_ColorBrightness = 1,
		OSM_RedChannel = 2,
		OSM_GreenChannel = 3,
		OSM_BlueChannel = 4,
		OSM_MAX = 5
	};

	enum class ESubUVBoundingVertexCount : uint8_t
	{
		BVC_FourVertices = 0,
		BVC_EightVertices = 1,
		BVC_MAX = 2
	};

	enum class EEmitterNormalsMode : uint8_t
	{
		ENM_CameraFacing = 0,
		ENM_Spherical = 1,
		ENM_Cylindrical = 2,
		ENM_MAX = 3
	};

	enum class EParticleSortMode : uint8_t
	{
		PSORTMODE_None = 0,
		PSORTMODE_ViewProjDepth = 1,
		PSORTMODE_DistanceToView = 2,
		PSORTMODE_Age_OldestFirst = 3,
		PSORTMODE_Age_NewestFirst = 4,
		PSORTMODE_MAX = 5
	};

	enum class EParticleUVFlipMode : uint8_t
	{
		None = 0,
		FlipUV = 1,
		FlipUOnly = 2,
		FlipVOnly = 3,
		RandomFlipUV = 4,
		RandomFlipUOnly = 5,
		RandomFlipVOnly = 6,
		RandomFlipUVIndependent = 7,
		EParticleUVFlipMode_MAX = 8
	};

	enum class ETrail2SourceMethod : uint8_t
	{
		PET2SRCM_Default = 0,
		PET2SRCM_Particle = 1,
		PET2SRCM_Actor = 2,
		PET2SRCM_MAX = 3
	};

	enum class EBeamTaperMethod : uint8_t
	{
		PEBTM_None = 0,
		PEBTM_Full = 1,
		PEBTM_Partial = 2,
		PEBTM_MAX = 3
	};

	enum class EBeam2Method : uint8_t
	{
		PEB2M_Distance = 0,
		PEB2M_Target = 1,
		PEB2M_Branch = 2,
		PEB2M_MAX = 3
	};

	enum class EMeshCameraFacingOptions : uint8_t
	{
		XAxisFacing_NoUp = 0,
		XAxisFacing_ZUp = 1,
		XAxisFacing_NegativeZUp = 2,
		XAxisFacing_YUp = 3,
		XAxisFacing_NegativeYUp = 4,
		LockedAxis_ZAxisFacing = 5,
		LockedAxis_NegativeZAxisFacing = 6,
		LockedAxis_YAxisFacing = 7,
		LockedAxis_NegativeYAxisFacing = 8,
		VelocityAligned_ZAxisFacing = 9,
		VelocityAligned_NegativeZAxisFacing = 10,
		VelocityAligned_YAxisFacing = 11,
		VelocityAligned_NegativeYAxisFacing = 12,
		EMeshCameraFacingOptions_MAX = 13
	};

	enum class EMeshCameraFacingUpAxis : uint8_t
	{
		CameraFacing_NoneUP = 0,
		CameraFacing_ZUp = 1,
		CameraFacing_NegativeZUp = 2,
		CameraFacing_YUp = 3,
		CameraFacing_NegativeYUp = 4,
		CameraFacing_MAX = 5
	};

	enum class EMeshScreenAlignment : uint8_t
	{
		PSMA_MeshFaceCameraWithRoll = 0,
		PSMA_MeshFaceCameraWithSpin = 1,
		PSMA_MeshFaceCameraWithLockedAxis = 2,
		PSMA_MAX = 3
	};

	enum class ETrailsRenderAxisOption : uint8_t
	{
		Trails_CameraUp = 0,
		Trails_SourceUp = 1,
		Trails_WorldUp = 2,
		Trails_MAX = 3
	};

	enum class ECloudStorageDelegate : uint8_t
	{
		CSD_KeyValueReadComplete = 0,
		CSD_KeyValueWriteComplete = 1,
		CSD_ValueChanged = 2,
		CSD_DocumentQueryComplete = 3,
		CSD_DocumentReadComplete = 4,
		CSD_DocumentWriteComplete = 5,
		CSD_DocumentConflictDetected = 6,
		CSD_MAX = 7
	};

	enum class EAdManagerDelegate : uint8_t
	{
		AMD_ClickedBanner = 0,
		AMD_UserClosedAd = 1,
		AMD_MAX = 2
	};

	enum class EMicroTransactionResult : uint8_t
	{
		MTR_Succeeded = 0,
		MTR_Failed = 1,
		MTR_Canceled = 2,
		MTR_RestoredFromServer = 3,
		MTR_MAX = 4
	};

	enum class EMicroTransactionDelegate : uint8_t
	{
		MTD_PurchaseQueryComplete = 0,
		MTD_PurchaseComplete = 1,
		MTD_MAX = 2
	};

	enum class ETwitterIntegrationDelegate : uint8_t
	{
		TID_AuthorizeComplete = 0,
		TID_TweetUIComplete = 1,
		TID_RequestComplete = 2,
		TID_MAX = 3
	};

	enum class ETwitterRequestMethod : uint8_t
	{
		TRM_Get = 0,
		TRM_Post = 1,
		TRM_Delete = 2,
		TRM_MAX = 3
	};

	enum class EReporterLineStyle : uint8_t
	{
		Line = 0,
		Dash = 1,
		EReporterLineStyle_MAX = 2
	};

	enum class ELegendPosition : uint8_t
	{
		Outside = 0,
		Inside = 1,
		ELegendPosition_MAX = 2
	};

	enum class EGraphDataStyle : uint8_t
	{
		Lines = 0,
		Filled = 1,
		EGraphDataStyle_MAX = 2
	};

	enum class EGraphAxisStyle : uint8_t
	{
		Lines = 0,
		Notches = 1,
		Grid = 2,
		EGraphAxisStyle_MAX = 3
	};

	enum class EConstraintTransform : uint8_t
	{
		Absolute = 0,
		Relative = 1,
		EConstraintTransform_MAX = 2
	};

	enum class EControlConstraint : uint8_t
	{
		Orientation = 0,
		Translation = 1,
		Max = 2,
		EControlConstraint_MAX = 3
	};

	enum class EImpactDamageOverride : uint8_t
	{
		IDO_None = 0,
		IDO_On = 1,
		IDO_Off = 2,
		IDO_MAX = 3
	};

	enum class ETextureSamplerFilter : uint8_t
	{
		Point = 0,
		Bilinear = 1,
		Trilinear = 2,
		AnisotropicPoint = 3,
		AnisotropicLinear = 4,
		ETextureSamplerFilter_MAX = 5
	};

	enum class ETexturePowerOfTwoSetting : uint8_t
	{
		None = 0,
		PadToPowerOfTwo = 1,
		PadToSquarePowerOfTwo = 2,
		ETexturePowerOfTwoSetting_MAX = 3
	};

	enum class ETextureMipGenSettings : uint8_t
	{
		TMGS_FromTextureGroup = 0,
		TMGS_SimpleAverage = 1,
		TMGS_Sharpen0 = 2,
		TMGS_Sharpen1 = 3,
		TMGS_Sharpen2 = 4,
		TMGS_Sharpen3 = 5,
		TMGS_Sharpen4 = 6,
		TMGS_Sharpen5 = 7,
		TMGS_Sharpen6 = 8,
		TMGS_Sharpen7 = 9,
		TMGS_Sharpen8 = 10,
		TMGS_Sharpen9 = 11,
		TMGS_Sharpen10 = 12,
		TMGS_NoMipmaps = 13,
		TMGS_LeaveExistingMips = 14,
		TMGS_Blur1 = 15,
		TMGS_Blur2 = 16,
		TMGS_Blur3 = 17,
		TMGS_Blur4 = 18,
		TMGS_Blur5 = 19,
		TMGS_MAX = 20
	};

	enum class ETextureGroup : uint8_t
	{
		TEXTUREGROUP_World = 0,
		TEXTUREGROUP_WorldNormalMap = 1,
		TEXTUREGROUP_WorldSpecular = 2,
		TEXTUREGROUP_Character = 3,
		TEXTUREGROUP_CharacterNormalMap = 4,
		TEXTUREGROUP_CharacterSpecular = 5,
		TEXTUREGROUP_Weapon = 6,
		TEXTUREGROUP_WeaponNormalMap = 7,
		TEXTUREGROUP_WeaponSpecular = 8,
		TEXTUREGROUP_Vehicle = 9,
		TEXTUREGROUP_VehicleNormalMap = 10,
		TEXTUREGROUP_VehicleSpecular = 11,
		TEXTUREGROUP_Cinematic = 12,
		TEXTUREGROUP_Effects = 13,
		TEXTUREGROUP_EffectsNotFiltered = 14,
		TEXTUREGROUP_Skybox = 15,
		TEXTUREGROUP_UI = 16,
		TEXTUREGROUP_Lightmap = 17,
		TEXTUREGROUP_RenderTarget = 18,
		TEXTUREGROUP_MobileFlattened = 19,
		TEXTUREGROUP_ProcBuilding_Face = 20,
		TEXTUREGROUP_ProcBuilding_LightMap = 21,
		TEXTUREGROUP_Shadowmap = 22,
		TEXTUREGROUP_ColorLookupTable = 23,
		TEXTUREGROUP_Terrain_Heightmap = 24,
		TEXTUREGROUP_Terrain_Weightmap = 25,
		TEXTUREGROUP_Bokeh = 26,
		TEXTUREGROUP_IESLightProfile = 27,
		TEXTUREGROUP_Pixels2D = 28,
		TEXTUREGROUP_HierarchicalLOD = 29,
		TEXTUREGROUP_MAX = 30
	};

	enum class ETextureSourceFormat : uint8_t
	{
		TSF_Invalid = 0,
		TSF_G8 = 1,
		TSF_BGRA8 = 2,
		TSF_BGRE8 = 3,
		TSF_RGBA16 = 4,
		TSF_RGBA16F = 5,
		TSF_RGBA8 = 6,
		TSF_RGBE8 = 7,
		TSF_MAX = 8
	};

	enum class ETextureSourceArtType : uint8_t
	{
		TSAT_Uncompressed = 0,
		TSAT_PNGCompressed = 1,
		TSAT_DDSFile = 2,
		TSAT_MAX = 3
	};

	enum class ETextureMipCount : uint8_t
	{
		TMC_ResidentMips = 0,
		TMC_AllMips = 1,
		TMC_AllMipsBiased = 2,
		TMC_MAX = 3
	};

	enum class ECompositeTextureMode : uint8_t
	{
		CTM_Disabled = 0,
		CTM_NormalRoughnessToRed = 1,
		CTM_NormalRoughnessToGreen = 2,
		CTM_NormalRoughnessToBlue = 3,
		CTM_NormalRoughnessToAlpha = 4,
		CTM_MAX = 5
	};

	enum class ETextureAddress : uint8_t
	{
		TA_Wrap = 0,
		TA_Clamp = 1,
		TA_Mirror = 2,
		TA_MAX = 3
	};

	enum class ETextureFilter : uint8_t
	{
		TF_Nearest = 0,
		TF_Bilinear = 1,
		TF_Trilinear = 2,
		TF_Default = 3,
		TF_MAX = 4
	};

	enum class ETextureCompressionSettings : uint8_t
	{
		TC_Default = 0,
		TC_Normalmap = 1,
		TC_Masks = 2,
		TC_Grayscale = 3,
		TC_Displacementmap = 4,
		TC_VectorDisplacementmap = 5,
		TC_HDR = 6,
		TC_EditorIcon = 7,
		TC_Alpha = 8,
		TC_DistanceFieldFont = 9,
		TC_HDR_Compressed = 10,
		TC_BC7 = 11,
		TC_MAX = 12
	};

	enum class EMaxConcurrentResolutionRule : uint8_t
	{
		PreventNew = 0,
		StopOldest = 1,
		StopFarthestThenPreventNew = 2,
		StopFarthestThenOldest = 3,
		StopLowestPriority = 4,
		StopQuietest = 5,
		StopLowestPriorityThenPreventNew = 6,
		EMaxConcurrentResolutionRule_MAX = 7
	};

	enum class ESoundGroup : uint8_t
	{
		SOUNDGROUP_Default = 0,
		SOUNDGROUP_Effects = 1,
		SOUNDGROUP_UI = 2,
		SOUNDGROUP_Music = 3,
		SOUNDGROUP_Voice = 4,
		SOUNDGROUP_GameSoundGroup1 = 5,
		SOUNDGROUP_GameSoundGroup2 = 6,
		SOUNDGROUP_GameSoundGroup3 = 7,
		SOUNDGROUP_GameSoundGroup4 = 8,
		SOUNDGROUP_GameSoundGroup5 = 9,
		SOUNDGROUP_GameSoundGroup6 = 10,
		SOUNDGROUP_GameSoundGroup7 = 11,
		SOUNDGROUP_GameSoundGroup8 = 12,
		SOUNDGROUP_GameSoundGroup9 = 13,
		SOUNDGROUP_GameSoundGroup10 = 14,
		SOUNDGROUP_GameSoundGroup11 = 15,
		SOUNDGROUP_GameSoundGroup12 = 16,
		SOUNDGROUP_GameSoundGroup13 = 17,
		SOUNDGROUP_GameSoundGroup14 = 18,
		SOUNDGROUP_GameSoundGroup15 = 19,
		SOUNDGROUP_GameSoundGroup16 = 20,
		SOUNDGROUP_GameSoundGroup17 = 21,
		SOUNDGROUP_GameSoundGroup18 = 22,
		SOUNDGROUP_GameSoundGroup19 = 23,
		SOUNDGROUP_GameSoundGroup20 = 24,
		SOUNDGROUP_MAX = 25
	};

	enum class EDecompressionType : uint8_t
	{
		DTYPE_Setup = 0,
		DTYPE_Invalid = 1,
		DTYPE_Preview = 2,
		DTYPE_Native = 3,
		DTYPE_RealTime = 4,
		DTYPE_Procedural = 5,
		DTYPE_Xenon = 6,
		DTYPE_Streaming = 7,
		DTYPE_MAX = 8
	};

	enum class EAudioOutputTarget : uint8_t
	{
		Speaker = 0,
		Controller = 1,
		ControllerFallbackToSpeaker = 2,
		EAudioOutputTarget_MAX = 3
	};

	enum class EModulationParamMode : uint8_t
	{
		MPM_Normal = 0,
		MPM_Abs = 1,
		MPM_Direct = 2,
		MPM_MAX = 3
	};

	enum class EOptimizationType : uint8_t
	{
		OT_NumOfTriangles = 0,
		OT_MaxDeviation = 1,
		OT_MAX = 2
	};

	enum class EImportanceLevel : uint8_t
	{
		IL_Off = 0,
		IL_Lowest = 1,
		IL_Low = 2,
		IL_Normal = 3,
		IL_High = 4,
		IL_Highest = 5,
		TEMP_BROKEN2 = 6,
		EImportanceLevel_MAX = 7
	};

	enum class ENormalMode : uint8_t
	{
		NM_PreserveSmoothingGroups = 0,
		NM_RecalculateNormals = 1,
		NM_RecalculateNormalsSmooth = 2,
		NM_RecalculateNormalsHard = 3,
		TEMP_BROKEN = 4,
		ENormalMode_MAX = 5
	};

	enum class EVertexAttributeStreamType : uint8_t
	{
		VAST_unknown = 0,
		VAST_float = 1,
		VAST_float2 = 2,
		VAST_float3 = 3,
		VAST_float4 = 4,
		VAST_MAX = 5
	};

	enum class EUserDefinedStructureStatus : uint8_t
	{
		UDSS_UpToDate = 0,
		UDSS_Dirty = 1,
		UDSS_Error = 2,
		UDSS_Duplicate = 3,
		UDSS_MAX = 4
	};

	enum class EVectorFieldConstructionOp : uint8_t
	{
		VFCO_Extrude = 0,
		VFCO_Revolve = 1,
		VFCO_MAX = 2
	};

	enum class EPostCopyOperation : uint8_t
	{
		None = 0,
		LogicalNegateBool = 1,
		EPostCopyOperation_MAX = 2
	};

	enum class EPinHidingMode : uint8_t
	{
		NeverAsPin = 0,
		PinHiddenByDefault = 1,
		PinShownByDefault = 2,
		AlwaysAsPin = 3,
		EPinHidingMode_MAX = 4
	};

	enum class EEvaluatorMode : uint8_t
	{
		EM_Standard = 0,
		EM_Freeze = 1,
		EM_DelayedFreeze = 2,
		EM_MAX = 3
	};


	// Enum Engine.EEvaluatorDataSource
	enum class EEvaluatorDataSource : uint8_t
	{
		EDS_SourcePose = 0,
		EDS_DestinationPose = 1,
		EDS_MAX = 2
	};

	enum class ECameraAlphaBlendMode : uint8_t
	{
		CABM_Linear = 0,
		CABM_Cubic = 1,
		CABM_MAX = 2
	};

	enum class EVertexPaintAxis : uint8_t
	{
		X = 0,
		Y = 1,
		Z = 2,
		EVertexPaintAxis_MAX = 3
	};

	enum class EDrawDebugItemType : uint8_t
	{
		DirectionalArrow = 0,
		Sphere = 1,
		Line = 2,
		OnScreenMessage = 3,
		EDrawDebugItemType_MAX = 4
	};

	enum class EAnimPhysCollisionType : uint8_t
	{
		CoM = 0,
		CustomSphere = 1,
		InnerSphere = 2,
		OuterSphere = 3,
		AnimPhysCollisionType_MAX = 4
	};

	enum class EAnimPhysTwistAxis : uint8_t
	{
		AxisX = 0,
		AxisY = 1,
		AxisZ = 2,
		AnimPhysTwistAxis_MAX = 3
	};

	enum class EWindowTitleBarMode : uint8_t
	{
		Overlay = 0,
		VerticalBox = 1,
		EWindowTitleBarMode_MAX = 2
	};
};