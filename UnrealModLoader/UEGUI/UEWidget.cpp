#include "UEWidget.h"
#include "UMG/Blueprint/WidgetTree.h"
#include "UObject/Class.h"
#include "UMG/Components/Border.h"
#include "Ue4.hpp"
#include <iostream>
namespace UEGUI
{
	UEWidget::UEWidget()
	{
		_rawWidget = (UE4::UUserWidget*)UE4::UObject::StaticConstructObject_Internal(UE4::UUserWidget::StaticClass(), UE4::UWorld::GetWorld(), "", 0x00000008, UE4::EInternalObjectFlags::None, nullptr, false, nullptr, false);
		std::cout << _rawWidget << std::endl;
		if (_rawWidget)
		{
			UE4::UWidgetTree* Tree = (UE4::UWidgetTree*)UE4::UObject::StaticConstructObject_Internal(UE4::UWidgetTree::StaticClass(), UE4::UWorld::GetWorld(), "", 0x00000008, UE4::EInternalObjectFlags::None, nullptr, false, nullptr, false);
			UE4::SetVariable<UE4::UWidgetTree*>(_rawWidget, "WidgetTree", Tree);

			auto Bord = (UE4::UBorder*)UE4::UObject::StaticConstructObject_Internal(UE4::UBorder::StaticClass(), UE4::UWorld::GetWorld(), "", 0x00000008, UE4::EInternalObjectFlags::None, nullptr, false, nullptr, false);
			UE4::SetVariable<UE4::UWidget*>(Tree, "RootWidget", Bord);
			_rawWidget->AddToViewport(0);
		}
	}
	UE4::UUserWidget* UEWidget::GetUserWidget()
	{
		return _rawWidget;
	}
};