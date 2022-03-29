#pragma once
#include <cstdint>

namespace UE4
{
	enum class ESlateBrushImageType : uint8_t
	{
		NoImage = 0,
		FullColor = 1,
		Linear = 2,
		ESlateBrushImageType_MAX = 3
	};

	enum class ESlateBrushMirrorType : uint8_t
	{
		NoMirror = 0,
		Horizontal = 1,
		Vertical = 2,
		Both = 3,
		ESlateBrushMirrorType_MAX = 4
	};

	enum class ESlateBrushTileType : uint8_t
	{
		NoTile = 0,
		Horizontal = 1,
		Vertical = 2,
		Both = 3,
		ESlateBrushTileType_MAX = 4
	};

	enum class ESlateColorStylingMode : uint8_t
	{
		UseColor_Specified = 0,
		UseColor_Specified_Link = 1,
		UseColor_Foreground = 2,
		UseColor_Foreground_Subdued = 3,
		UseColor_MAX = 4
	};

	enum class ESlateBrushDrawType : uint8_t
	{
		NoDrawType = 0,
		Box = 1,
		Border = 2,
		Image = 3,
		ESlateBrushDrawType_MAX = 4
	};

	enum class EFontLoadingPolicy : uint8_t
	{
		LazyLoad = 0,
		Stream = 1,
		Inline = 2,
		EFontLoadingPolicy_MAX = 3
	};

	enum class EFontHinting : uint8_t
	{
		Default = 0,
		Auto = 1,
		AutoLight = 2,
		Monochrome = 3,
		None = 4,
		EFontHinting_MAX = 5
	};

	enum class EFontFallback : uint8_t
	{
		FF_NoFallback = 0,
		FF_LocalizedFallback = 1,
		FF_LastResortFallback = 2,
		FF_Max = 3
	};

	enum class ESelectInfo : uint8_t
	{
		OnKeyPress = 0,
		OnNavigation = 1,
		OnMouseClick = 2,
		Direct = 3,
		ESelectInfo_MAX = 4
	};

	enum class ETextCommit : uint8_t
	{
		Default = 0,
		OnEnter = 1,
		OnUserMovedFocus = 2,
		OnCleared = 3,
		ETextCommit_MAX = 4
	};

	enum class EScrollDirection : uint8_t
	{
		Scroll_Down = 0,
		Scroll_Up = 1,
		Scroll_MAX = 2
	};

	enum class EOrientation : uint8_t
	{
		Orient_Horizontal = 0,
		Orient_Vertical = 1,
		Orient_MAX = 2
	};

	enum class EMenuPlacement : uint8_t
	{
		MenuPlacement_BelowAnchor = 0,
		MenuPlacement_CenteredBelowAnchor = 1,
		MenuPlacement_BelowRightAnchor = 2,
		MenuPlacement_ComboBox = 3,
		MenuPlacement_ComboBoxRight = 4,
		MenuPlacement_MenuRight = 5,
		MenuPlacement_AboveAnchor = 6,
		MenuPlacement_CenteredAboveAnchor = 7,
		MenuPlacement_AboveRightAnchor = 8,
		MenuPlacement_MenuLeft = 9,
		MenuPlacement_Center = 10,
		MenuPlacement_RightLeftCenter = 11,
		MenuPlacement_MAX = 12
	};

	enum class EVerticalAlignment : uint8_t
	{
		VAlign_Fill = 0,
		VAlign_Top = 1,
		VAlign_Center = 2,
		VAlign_Bottom = 3,
		VAlign_MAX = 4
	};

	enum class EHorizontalAlignment : uint8_t
	{
		HAlign_Fill = 0,
		HAlign_Left = 1,
		HAlign_Center = 2,
		HAlign_Right = 3,
		HAlign_MAX = 4
	};

	enum class ENavigationGenesis : uint8_t
	{
		Keyboard = 0,
		Controller = 1,
		User = 2,
		ENavigationGenesis_MAX = 3
	};

	enum class ENavigationSource : uint8_t
	{
		FocusedWidget = 0,
		WidgetUnderCursor = 1,
		ENavigationSource_MAX = 2
	};

	enum class EUINavigation : uint8_t
	{
		Left = 0,
		Right = 1,
		Up = 2,
		Down = 3,
		Next = 4,
		Previous = 5,
		Num = 6,
		Invalid = 7,
		EUINavigation_MAX = 8
	};

	enum class EButtonPressMethod : uint8_t
	{
		DownAndUp = 0,
		ButtonPress = 1,
		ButtonRelease = 2,
		EButtonPressMethod_MAX = 3
	};

	enum class EButtonTouchMethod : uint8_t
	{
		DownAndUp = 0,
		PreciseTap = 1,
		EButtonTouchMethod_MAX = 2
	};

	enum class EButtonClickMethod : uint8_t
	{
		DownAndUp = 0,
		MouseDown = 1,
		MouseUp = 2,
		PreciseClick = 3,
		EButtonClickMethod_MAX = 4
	};

	enum class ECheckBoxState : uint8_t
	{
		Unchecked = 0,
		Checked = 1,
		Undetermined = 2,
		ECheckBoxState_MAX = 3
	};

	enum class ESlateCheckBoxType : uint8_t
	{
		CheckBox = 0,
		ToggleButton = 1,
		ESlateCheckBoxType_MAX = 2
	};

	enum class EConsumeMouseWheel : uint8_t
	{
		WhenScrollingPossible = 0,
		Always = 1,
		Never = 2,
		EConsumeMouseWheel_MAX = 3
	};

	enum class ETextShapingMethod : uint8_t
	{
		Auto = 0,
		KerningOnly = 1,
		FullShaping = 2,
		ETextShapingMethod_MAX = 3
	};

	enum class EFocusCause : uint8_t
	{
		Mouse = 0,
		Navigation = 1,
		SetDirectly = 2,
		Cleared = 3,
		OtherWidgetLostFocus = 4,
		WindowActivate = 5,
		EFocusCause_MAX = 6
	};

	enum class EUINavigationRule : uint8_t
	{
		Escape = 0,
		Explicit = 1,
		Wrap = 2,
		Stop = 3,
		Custom = 4,
		Invalid = 5,
		EUINavigationRule_MAX = 6
	};
};