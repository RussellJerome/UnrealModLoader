#ifdef _MSC_VER
#pragma pack(push, 0x8)
#endif

#include "CoreUObject_parameters.hpp"
namespace UE4
{
	//---------------------------------------------------------------------------
	//Functions
	//---------------------------------------------------------------------------

	std::string UObject::GetName() const
	{
		auto Name = *reinterpret_cast<FName*>((byte*)this + GameProfile::SelectedGameProfile.defs.UObject.Name);
		std::string name(Name.GetName());
		if (Name.Number > 0)
		{
			name += '_' + std::to_string(Name.Number);
		}

		auto pos = name.rfind('/');
		if (pos == std::string::npos)
		{
			return name;
		}

		return name.substr(pos + 1);
	}

	std::string UObject::GetFullName() const
	{
		std::string name;
		auto Class = GetClass();
		if (Class != nullptr)
		{
			std::string temp;
			for (auto p = GetOuter(); p; p = p->GetOuter())
			{
				temp = p->GetName() + "." + temp;
			}

			name = Class->GetName();
			name += " ";
			name += temp;
			name += GetName();
		}

		return name;
	}

	bool UObject::IsA(UClass* cmp) const
	{
		for (auto super = GetClass(); super; super = static_cast<UClass*>(super->GetSuperField()))
		{
			if (super == cmp)
			{
				return true;
			}
		}

		return false;
	}

	void UObject::ExecuteUbergraph(int EntryPoint)
	{
		static auto fn = UObject::FindObject<UFunction>("Function CoreUObject.Object.ExecuteUbergraph");

		UObject_ExecuteUbergraph_Params params;
		params.EntryPoint = EntryPoint;

		//auto flags = fn->FunctionFlags;

		UObject::ProcessEvent(fn, &params);

		//fn->FunctionFlags = flags;
	}


}

#ifdef _MSC_VER
#pragma pack(pop)
#endif
