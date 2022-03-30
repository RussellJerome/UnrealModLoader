#pragma once
#include <cstdint>

namespace UE4
{
	enum class EInterpCurveMode : uint8_t
	{
		CIM_Linear = 0,
		CIM_CurveAuto = 1,
		CIM_Constant = 2,
		CIM_CurveUser = 3,
		CIM_CurveBreak = 4,
		CIM_CurveAutoClamped = 5,
		CIM_MAX = 6
	};

	enum class ERangeBoundTypes : uint8_t
	{
		Exclusive = 0,
		Inclusive = 1,
		Open = 2,
		ERangeBoundTypes_MAX = 3
	};

	enum class ELocalizedTextSourceCategory : uint8_t
	{
		Game = 0,
		Engine = 1,
		Editor = 2,
		ELocalizedTextSourceCategory_MAX = 3
	};

	enum class EAutomationEventType : uint8_t
	{
		Info = 0,
		Warning = 1,
		Error = 2,
		EAutomationEventType_MAX = 3
	};

	enum class ELifetimeCondition : uint8_t
	{
		COND_None = 0,
		COND_InitialOnly = 1,
		COND_OwnerOnly = 2,
		COND_SkipOwner = 3,
		COND_SimulatedOnly = 4,
		COND_AutonomousOnly = 5,
		COND_SimulatedOrPhysics = 6,
		COND_InitialOrOwner = 7,
		COND_Custom = 8,
		COND_ReplayOrOwner = 9,
		COND_ReplayOnly = 10,
		COND_SimulatedOnlyNoReplay = 11,
		COND_SimulatedOrPhysicsNoReplay = 12,
		COND_SkipReplay = 13,
		COND_Max = 14
	};

	enum class EUnit : uint8_t
	{
		Micrometers = 0,
		Millimeters = 1,
		Centimeters = 2,
		Meters = 3,
		Kilometers = 4,
		Inches = 5,
		Feet = 6,
		Yards = 7,
		Miles = 8,
		Lightyears = 9,
		Degrees = 10,
		Radians = 11,
		MetersPerSecond = 12,
		KilometersPerHour = 13,
		MilesPerHour = 14,
		Celsius = 15,
		Farenheit = 16,
		Kelvin = 17,
		Micrograms = 18,
		Milligrams = 19,
		Grams = 20,
		Kilograms = 21,
		MetricTons = 22,
		Ounces = 23,
		Pounds = 24,
		Stones = 25,
		Newtons = 26,
		PoundsForce = 27,
		KilogramsForce = 28,
		Hertz = 29,
		Kilohertz = 30,
		Megahertz = 31,
		Gigahertz = 32,
		RevolutionsPerMinute = 33,
		Bytes = 34,
		Kilobytes = 35,
		Megabytes = 36,
		Gigabytes = 37,
		Terabytes = 38,
		Lumens = 39,
		Milliseconds = 40,
		Seconds = 41,
		Minutes = 42,
		Hours = 43,
		Days = 44,
		Months = 45,
		Years = 46,
		Multiplier = 47,
		Percentage = 48,
		Unspecified = 49,
		EUnit_MAX = 50
	};

	enum class EMouseCursor : uint8_t
	{
		None = 0,
		Default = 1,
		TextEditBeam = 2,
		ResizeLeftRight = 3,
		ResizeUpDown = 4,
		ResizeSouthEast = 5,
		ResizeSouthWest = 6,
		CardinalCross = 7,
		Crosshairs = 8,
		Hand = 9,
		GrabHand = 10,
		GrabHandClosed = 11,
		SlashedCircle = 12,
		EyeDropper = 13,
		EMouseCursor_MAX = 14
	};

	enum class EPixelFormat : uint8_t
	{
		PF_Unknown = 0,
		PF_A32B32G32R32F = 1,
		PF_B8G8R8A8 = 2,
		PF_G8 = 3,
		PF_G16 = 4,
		PF_DXT1 = 5,
		PF_DXT3 = 6,
		PF_DXT5 = 7,
		PF_UYVY = 8,
		PF_FloatRGB = 9,
		PF_FloatRGBA = 10,
		PF_DepthStencil = 11,
		PF_ShadowDepth = 12,
		PF_R32_FLOAT = 13,
		PF_G16R16 = 14,
		PF_G16R16F = 15,
		PF_G16R16F_FILTER = 16,
		PF_G32R32F = 17,
		PF_A2B10G10R10 = 18,
		PF_A16B16G16R16 = 19,
		PF_D24 = 20,
		PF_R16F = 21,
		PF_R16F_FILTER = 22,
		PF_BC5 = 23,
		PF_V8U8 = 24,
		PF_A1 = 25,
		PF_FloatR11G11B10 = 26,
		PF_A8 = 27,
		PF_R32_UINT = 28,
		PF_R32_SINT = 29,
		PF_PVRTC2 = 30,
		PF_PVRTC4 = 31,
		PF_R16_UINT = 32,
		PF_R16_SINT = 33,
		PF_R16G16B16A16_UINT = 34,
		PF_R16G16B16A16_SINT = 35,
		PF_R5G6B5_UNORM = 36,
		PF_R8G8B8A8 = 37,
		PF_A8R8G8B8 = 38,
		PF_BC4 = 39,
		PF_R8G8 = 40,
		PF_ATC_RGB = 41,
		PF_ATC_RGBA_E = 42,
		PF_ATC_RGBA_I = 43,
		PF_X24_G8 = 44,
		PF_ETC1 = 45,
		PF_ETC2_RGB = 46,
		PF_ETC2_RGBA = 47,
		PF_R32G32B32A32_UINT = 48,
		PF_R16G16_UINT = 49,
		PF_ASTC_4x4 = 50,
		PF_ASTC_6x6 = 51,
		PF_ASTC_8x8 = 52,
		PF_ASTC_10x10 = 53,
		PF_ASTC_12x12 = 54,
		PF_BC6H = 55,
		PF_BC7 = 56,
		PF_R8_UINT = 57,
		PF_L8 = 58,
		PF_XGXR8 = 59,
		PF_R8G8B8A8_UINT = 60,
		PF_R8G8B8A8_SNORM = 61,
		PF_R16G16B16A16_UNORM = 62,
		PF_R16G16B16A16_SNORM = 63,
		//	PF_MAX                         = 64
	};

	enum class EAxis : uint8_t
	{
		None = 0,
		X = 1,
		Y = 2,
		Z = 3,
		EAxis_MAX = 4
	};

	enum class ELogTimes : uint8_t
	{
		None = 0,
		UTC = 1,
		SinceGStartTime = 2,
		Local = 3,
		ELogTimes_MAX = 4
	};

	enum class ESearchDir : uint8_t
	{
		FromStart = 0,
		FromEnd = 1,
		ESearchDir_MAX = 2
	};

	enum class ESearchCase : uint8_t
	{
		CaseSensitive = 0,
		IgnoreCase = 1,
		ESearchCase_MAX = 2
	};
};