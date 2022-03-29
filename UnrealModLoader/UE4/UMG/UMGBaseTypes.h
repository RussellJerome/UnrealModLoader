#pragma once
#include <cstdint>

namespace UE4
{
	enum class ESlateVisibility : uint8_t
	{
		Visible = 0,
		Collapsed = 1,
		Hidden = 2,
		HitTestInvisible = 3,
		SelfHitTestInvisible = 4,
		ESlateVisibility_MAX = 5
	};

	enum class EVirtualKeyboardType : uint8_t
	{
		Default = 0,
		Number = 1,
		Web = 2,
		Email = 3,
		Password = 4,
		AlphaNumeric = 5,
		EVirtualKeyboardType_MAX = 6
	};

	enum class EDragPivot : uint8_t
	{
		MouseDown = 0,
		TopLeft = 1,
		TopCenter = 2,
		TopRight = 3,
		CenterLeft = 4,
		CenterCenter = 5,
		CenterRight = 6,
		BottomLeft = 7,
		BottomCenter = 8,
		BottomRight = 9,
		EDragPivot_MAX = 10
	};

	enum class ESlateSizeRule : uint8_t
	{
		Automatic = 0,
		Fill = 1,
		ESlateSizeRule_MAX = 2
	};

	enum class EWidgetDesignFlags : uint8_t
	{
		None = 0,
		Designing = 1,
		ShowOutline = 2,
		ExecutePreConstruct = 3,
		EWidgetDesignFlags_MAX = 4
	};

	enum class EBindingKind : uint8_t
	{
		Function = 0,
		Property = 1,
		EBindingKind_MAX = 2
	};

	enum class EDesignPreviewSizeMode : uint8_t
	{
		FillScreen = 0,
		Custom = 1,
		CustomOnScreen = 2,
		Desired = 3,
		DesiredOnScreen = 4,
		EDesignPreviewSizeMode_MAX = 5
	};

	enum class EUMGSequencePlayMode : uint8_t
	{
		Forward = 0,
		Reverse = 1,
		PingPong = 2,
		EUMGSequencePlayMode_MAX = 3
	};

	enum class EWidgetGeometryMode : uint8_t
	{
		Plane = 0,
		Cylinder = 1,
		EWidgetGeometryMode_MAX = 2
	};

	enum class EWidgetBlendMode : uint8_t
	{
		Opaque = 0,
		Masked = 1,
		Transparent = 2,
		EWidgetBlendMode_MAX = 3
	};

	enum class EWidgetSpace : uint8_t
	{
		World = 0,
		Screen = 1,
		EWidgetSpace_MAX = 2
	};

	enum class EWidgetInteractionSource : uint8_t
	{
		World = 0,
		Mouse = 1,
		CenterScreen = 2,
		Custom = 3,
		EWidgetInteractionSource_MAX = 4
	};
};