#include "UnrealType.h"
#include "NameType.h"
#include "../UnrealModLoader.h"

namespace UE4
{
	FField* FField::GetNext() const
	{
		return (class FField*)this + UML::GetGameInfo()->defs->FField.Next;
	};

	std::string FField::GetName() const
	{
		auto Name = *reinterpret_cast<FName*>((byte*)this + UML::GetGameInfo()->defs->FField.Name);
		if (UE4::FName::GetFNamePool().IsValidIndex(Name.ComparisonIndex))
		{
			return Name.GetName();
		}
		return "nullptr";
	};

	FField* UEProperty::GetParentFProperty()
	{
		return (FField*)this;
	}
	class UField* UEProperty::GetParentUProperty()
	{
		return (class UField*)this;
	}
	int32_t UEProperty::GetArrayDim() const
	{
		return (int32_t)this + UML::GetGameInfo()->defs->Property.ArrayDim;
	};

	int32_t UEProperty::GetOffset() const
	{
		return (int32_t)this + UML::GetGameInfo()->defs->Property.Offset;
	};
};