#pragma once
#include "ContentWidget.h"

namespace UE4
{
	class UBorder : public UContentWidget
	{
	public:
		/*void SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment);
		void SetPadding(const struct FMargin& InPadding);
		void SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment);
		void SetDesiredSizeScale(const struct FVector2D& InScale);
		void SetContentColorAndOpacity(const struct FLinearColor& InContentColorAndOpacity);
		void SetBrushFromTexture(class UTexture2D* Texture);
		void SetBrushFromMaterial(class UMaterialInterface* Material);
		void SetBrushFromAsset(class USlateBrushAsset* Asset);
		void SetBrushColor(const struct FLinearColor& InBrushColor);
		void SetBrush(const struct FSlateBrush& InBrush);
		class UMaterialInstanceDynamic* GetDynamicMaterial();*/

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class UMG.Border");
			return ptr;
		}
	};
};