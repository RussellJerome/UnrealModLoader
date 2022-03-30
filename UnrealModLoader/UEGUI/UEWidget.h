#pragma once
#include "UMG/Blueprint/UserWidget.h"

namespace UEGUI
{
	class UEWidget
	{
	public:
		UEWidget();

		class UE4::UUserWidget* GetUserWidget();
	private:
		class UE4::UUserWidget* _rawWidget;
	};
};