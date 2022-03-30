#pragma once
/*
TODO
====
Add Ability To Write FText
*/
namespace UE4
{
	class FTextData {
	public:
		char UnknownData[0x28];
		wchar_t* Name;
		__int32 Length;
	};

	struct FText {
		FTextData* Data;
		char UnknownData[0x10];

		FText(const wchar_t* Name) {

			Data = new FTextData();
			Data->Name = const_cast<wchar_t*>(Name);
			Data->Length = std::wcslen(Name);
		}

		wchar_t* Get() const {
			if (Data)
				return Data->Name;

			return nullptr;
		}
	};
};