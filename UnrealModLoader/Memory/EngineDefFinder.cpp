#include "EngineDefFinder.h"
#include "Utility.h"
#include "Memory.h"
#include "UObject/Object.h"
#include "UObject/Class.h"
#include "UObject/NameType.h"
#include "UObject/CoreTypes.h"
#include "UObject/UnrealType.h"
#include <iostream>

namespace UML
{
	namespace EngineDefFinder
	{
		bool FindUObjectIndexDefs(UE4::UObject* CoreUObject, UE4::UObject* UEObject)
		{
			LOG_INFO("Scanning For UObject Index Def.");
			bool HasIndexNotBeenFound = true;

			while (HasIndexNotBeenFound)
			{
				GetGameInfo()->defs->UObject.Index = GetGameInfo()->defs->UObject.Index + 0x4;
				if (Memory::Read<int32_t>(CoreUObject + GetGameInfo()->defs->UObject.Index) == 1)
				{
					if (Memory::Read<int32_t>(UEObject + GetGameInfo()->defs->UObject.Index) == 2)
					{
						HasIndexNotBeenFound = false;
					}
				}
			}
			LOG_INFO("UObject Index Def located at: 0x%p", GetGameInfo()->defs->UObject.Index);
			return true;
		};

		bool FindUObjectNameDefs(UE4::UObject* CoreUObject)
		{
			bool HasNameNotBeenFound = true;
			bool HasHardNameCheck = false;
			LOG_INFO("Scanning For UObject Name Def.");
			while (HasNameNotBeenFound)
			{
				UE4::FName Name;
				if (HasHardNameCheck == false)
				{
					GetGameInfo()->defs->UObject.Name = 0x18;
					HasHardNameCheck = true;
				}
				Name = Memory::Read<UE4::FName>(CoreUObject + GetGameInfo()->defs->UObject.Name);
				if (GetGameInfo()->UsesFNamePool)
				{
					if (UE4::FName::GetFNamePool().IsValidIndex(Name.ComparisonIndex))
					{
						if (Name.GetName() == "Object")
						{
							HasNameNotBeenFound = false;
						}
					}
				}
				else
				{
					if (UE4::FName::GetTNameArray().IsValidIndex(Name.ComparisonIndex))
					{
						if (Name.GetName() == "Object")
						{
							HasNameNotBeenFound = false;
						}
					}
				}
				if (HasNameNotBeenFound == true)
				{
					GetGameInfo()->defs->UObject.Name = GetGameInfo()->defs->UObject.Name + 0x8;
				}
			}
			LOG_INFO("UObject Name Def located at: 0x%p", GetGameInfo()->defs->UObject.Name);
			return true;
		}

		bool FindUObjectClassDefs(UE4::UObject* CoreUObject)
		{
			bool HasClassNotBeenFound = true;
			bool HasFinishedHardCheck = false;
			LOG_INFO("Scanning For UObject Class Def.");
			while (HasClassNotBeenFound)
			{
				UE4::UClass* Class;
				if (HasFinishedHardCheck == false)
				{
					GetGameInfo()->defs->UObject.Class = 0x10;
					Class = Memory::Read<UE4::UClass*>(CoreUObject + GetGameInfo()->defs->UObject.Class);
					HasFinishedHardCheck = true;
				}
				else
				{
					Class = Memory::Read<UE4::UClass*>(CoreUObject + GetGameInfo()->defs->UObject.Class);
				}

				auto ClassIndex = Class->GetIndex();
				UE4::UObject* ClassCheck;
				if (GetGameInfo()->IsUsingFChunkedFixedUObjectArray)
				{
					ClassCheck = UE4::UObject::GObjects->GetAsChunckArray().GetByIndex(ClassIndex).Object;
				}
				else
				{
					ClassCheck = UE4::UObject::GObjects->GetAsTUArray().GetByIndex(ClassIndex).Object;
				}

				if (ClassCheck != nullptr)
				{
					if (ClassCheck->GetName() == "Class")
					{
						HasClassNotBeenFound = false;
					}
				}
				if (HasClassNotBeenFound)
				{
					GetGameInfo()->defs->UObject.Class = GetGameInfo()->defs->UObject.Class + 0x8;
				}
			}
			LOG_INFO("UObject Class Def located at: 0x%p", GetGameInfo()->defs->UObject.Class);
			return true;
		}

		bool FindUObjectOuterDefs(UE4::UObject* CoreUObject)
		{
			bool HasOuterNotBeenFound = true;
			LOG_INFO("Scanning For UObject Outer Def.");
			while (HasOuterNotBeenFound)
			{
				auto Outer = Memory::Read<UE4::UObject*>(CoreUObject + GetGameInfo()->defs->UObject.Outer);
				UE4::UObject* ObjectCheck;
				if (GetGameInfo()->IsUsingFChunkedFixedUObjectArray)
				{
					ObjectCheck = UE4::UObject::GObjects->GetAsChunckArray().GetByIndex(0).Object;
				}
				else
				{
					ObjectCheck = UE4::UObject::GObjects->GetAsTUArray().GetByIndex(0).Object;
				}

				if (Outer == ObjectCheck)
				{
					HasOuterNotBeenFound = false;
				}
				if (HasOuterNotBeenFound)
				{
					GetGameInfo()->defs->UObject.Outer = GetGameInfo()->defs->UObject.Outer + 0x8;
				}
			}
			LOG_INFO("UObject Outer Def located at: 0x%p", GetGameInfo()->defs->UObject.Outer);
			return true;
		}

		bool FindUObjectDefs()
		{
			UE4::UObject* CoreUObject;
			UE4::UObject* UEObject;
			if (GetGameInfo()->IsUsingFChunkedFixedUObjectArray)
			{
				CoreUObject = UE4::UObject::GObjects->GetAsChunckArray().GetByIndex(1).Object;
				UEObject = UE4::UObject::GObjects->GetAsChunckArray().GetByIndex(2).Object;
			}
			else
			{
				CoreUObject = UE4::UObject::GObjects->GetAsTUArray().GetByIndex(1).Object;
				UEObject = UE4::UObject::GObjects->GetAsTUArray().GetByIndex(2).Object;
			}
			if (FindUObjectIndexDefs(CoreUObject, UEObject) && FindUObjectNameDefs(CoreUObject) && FindUObjectClassDefs(CoreUObject) && FindUObjectOuterDefs(CoreUObject))
			{
				LOG_INFO("UObject Defined");
				return true;
			}
			else
			{
				LOG_ERROR("UObject could not be defined. Try Manually Defining in the game profile file.");
			}
			return false;
		}

		bool FindUFieldNextDef()
		{
			LOG_INFO("Scanning For UField Next Def.");
			bool HasNextNotBeenFound = true;
			auto UserConstructionScript = UE4::UObject::FindObject<UE4::UFunction>("Function Engine.Actor.UserConstructionScript");
			GetGameInfo()->defs->UField.Next = GetGameInfo()->defs->UObject.Outer; // Prevents scanning same area over and over.
			while (HasNextNotBeenFound)
			{
				auto NextObject = Memory::Read<UE4::UField*>(UserConstructionScript + GetGameInfo()->defs->UField.Next);
				if (NextObject && NextObject->GetOuter() == UserConstructionScript->GetOuter())
				{
					HasNextNotBeenFound = false;
				}
				if (HasNextNotBeenFound)
				{
					GetGameInfo()->defs->UField.Next = GetGameInfo()->defs->UField.Next + 0x8;
				}
			}
			LOG_INFO("UField Next Def located at: 0x%p", GetGameInfo()->defs->UField.Next);
			return true;
		}

		bool FindUFieldDefs()
		{
			if (FindUFieldNextDef())
			{
				LOG_INFO("UField Defined");
				return true;
			}
			else
			{
				LOG_ERROR("UField could not be defined. Try Manually Defining in the game profile file.");
			}
			return false;
		}

		bool FindUStructSuperFieldDef()
		{
			LOG_INFO("Scanning For UStruct SuperField Def.");
			auto StructObject = UE4::UObject::FindObject<UE4::UStruct>("Class CoreUObject.Struct");
			auto FieldObject = UE4::UObject::FindObject<UE4::UField>("Class CoreUObject.Field");
			bool HasSuperFieldNotBeenFound = true;
			GetGameInfo()->defs->UStruct.SuperStruct = GetGameInfo()->defs->UField.Next; // Prevents scanning same area over and over.
			while (HasSuperFieldNotBeenFound)
			{
				auto SuperFieldObject = Memory::Read<UE4::UObject*>(StructObject + GetGameInfo()->defs->UStruct.SuperStruct);
				if (SuperFieldObject == FieldObject)
				{
					HasSuperFieldNotBeenFound = false;
				}
				if (HasSuperFieldNotBeenFound)
				{
					GetGameInfo()->defs->UStruct.SuperStruct = GetGameInfo()->defs->UStruct.SuperStruct + 0x8;
				}
			}
			LOG_INFO("UStruct SuperField Def located at: 0x%p", GetGameInfo()->defs->UStruct.SuperStruct);
			return true;
		}

		bool FindUStructChildrenDef()
		{
			LOG_INFO("Scanning For UStruct Children Def.");
			auto VectorObject = UE4::UObject::FindObject<UE4::UObject>("ScriptStruct CoreUObject.Vector");
			auto VectorFirstChildObject = UE4::UObject::FindObject<UE4::UObject>("FloatProperty CoreUObject.Vector.X");
			bool HasChildrenNotBeenFound = true;
			GetGameInfo()->defs->UStruct.Children = GetGameInfo()->defs->UStruct.SuperStruct;
			while (HasChildrenNotBeenFound)
			{
				auto ChildObject = Memory::Read<UE4::UObject*>((byte*)VectorObject + GetGameInfo()->defs->UStruct.Children);
				if (VectorFirstChildObject)
				{
					if (VectorFirstChildObject == ChildObject)
					{
						HasChildrenNotBeenFound = false;
					}
					if (HasChildrenNotBeenFound)
					{
						GetGameInfo()->defs->UStruct.Children = GetGameInfo()->defs->UStruct.Children + 0x8;
					}
				}
				else
				{
					if (auto Class = ChildObject->GetClass())
					{
						std::cout << "Class" << std::endl;
						if (Class->GetName() == "FloatProperty" || "Vector")
						{
							HasChildrenNotBeenFound = false;
						}
						else
						{
							GetGameInfo()->defs->UStruct.Children = GetGameInfo()->defs->UStruct.Children + 0x8;
						}
					}
					else
					{
						GetGameInfo()->defs->UStruct.Children = GetGameInfo()->defs->UStruct.Children + 0x8;
					}
				}
			}
			LOG_INFO("UStruct Children Def located at: 0x%p", GetGameInfo()->defs->UStruct.Children);
			return true;
		}

		bool FindUStructPropertySizeDef()
		{
			LOG_INFO("Scanning For UStruct PropertySize Def.");
			auto VectorObject = UE4::UObject::FindObject<UE4::UObject>("ScriptStruct CoreUObject.Vector");
			while (Memory::Read<int32_t>(VectorObject + GetGameInfo()->defs->UStruct.PropertiesSize) != 12)
			{
				GetGameInfo()->defs->UStruct.PropertiesSize = GetGameInfo()->defs->UStruct.PropertiesSize + 0x4;
			}
			LOG_INFO("UStruct PropertySize Def located at: 0x%p", GetGameInfo()->defs->UStruct.PropertiesSize);
			return true;
		}

		int GetOverallUStructSize()
		{
			auto UStruct = UE4::UObject::FindObject<UE4::UStruct>("Class CoreUObject.Struct");
			if (UStruct)
			{
				return UStruct->GetPropertySize();
			}
			return 0;
		}

		bool FindUStructDefs()
		{
			if (FindUStructSuperFieldDef() && FindUStructChildrenDef() && FindUStructPropertySizeDef())
			{
				GetGameInfo()->defs->UStruct.OverallUStructSize = GetOverallUStructSize();
				LOG_INFO("UStruct Size: %i", GetGameInfo()->defs->UStruct.OverallUStructSize);
				LOG_INFO("UStruct Defined");
				return true;
			}
			else
			{
				LOG_ERROR("UStruct could not be defined. Try Manually Defining in the game profile file.");
			}
			return false;
		}

		bool FindUFunctionFunctionFlagsDef()
		{
			LOG_INFO("Scanning For UFunction FunctionFlags Def.");
			bool HasFunctionFlagsNotBeenFound = true;
			auto WasRecentlyRendered = UE4::UObject::FindObject<UE4::UFunction>("Function Engine.Actor.WasRecentlyRendered");
			GetGameInfo()->defs->UFunction.FunctionFlags = GetGameInfo()->defs->UStruct.OverallUStructSize; // Prevents scanning same area over and over.
			while (HasFunctionFlagsNotBeenFound)
			{
				auto FunctionFlags = Memory::Read<int>(WasRecentlyRendered + GetGameInfo()->defs->UFunction.FunctionFlags);
				if (FunctionFlags == 1409418241)
				{
					HasFunctionFlagsNotBeenFound = false;
				}
				if (HasFunctionFlagsNotBeenFound)
				{
					GetGameInfo()->defs->UFunction.FunctionFlags = GetGameInfo()->defs->UFunction.FunctionFlags + 0x4;
				}
			}
			LOG_INFO("UFunction FunctionFlags Def located at: 0x%p", GetGameInfo()->defs->UFunction.FunctionFlags);
			return true;
		}

		bool FindUFunctionFunc()
		{
			auto UFunction = UE4::UObject::FindObject<UE4::UFunction>("Class CoreUObject.Function");
			if (UFunction)
			{
				GetGameInfo()->defs->UFunction.Func = UFunction->GetPropertySize() - 0x8;
				LOG_INFO("UFunction Func: 0x%p", GetGameInfo()->defs->UFunction.Func);
				return true;
			}
			return false;
		}

		bool FindUFunctionDefs()
		{
			if (FindUFunctionFunctionFlagsDef() && FindUFunctionFunc())
			{
				LOG_INFO("UFunction Defined");
				return true;
			}
			else
			{
				LOG_ERROR("UFunction could not be defined. Try Manually Defining in the game profile file.");
			}
			return false;
		}

		bool FindFField()
		{
			auto VectorObject = (UE4::UStruct*)UE4::UObject::FindObject<UE4::UObject>("ScriptStruct CoreUObject.Vector");
			auto FieldChild = (UE4::FField*)VectorObject->GetChildren();
			bool NameFound = false;
			bool NextFound = false;
			while (!NameFound)
			{
				auto Name = Memory::Read<UE4::FName>(FieldChild + GetGameInfo()->defs->FField.Name);
				if (UE4::FName::GetFNamePool().IsValidIndex(Name.ComparisonIndex))
				{
					if (Name.GetName() == "X")
					{
						NameFound = true;
					}
				}
				if (NameFound == false)
				{
					GetGameInfo()->defs->FField.Name = GetGameInfo()->defs->FField.Name + 0x8;
				}
			}
			LOG_INFO("FField Name Def located at: 0x%p", GetGameInfo()->defs->FField.Name);
			while (!NextFound)
			{
				// 9 times out of 10, its right behind the Name, so we do that check to save possible issues
				auto NextField = Memory::Read<UE4::FField*>(FieldChild + GetGameInfo()->defs->FField.Name - 0x8);
				if (NextField && NextField->GetName() == "Y")
				{
					NextFound = true;
					GetGameInfo()->defs->FField.Next = GetGameInfo()->defs->FField.Name - 0x8;
					break;
				}

				NextField = Memory::Read<UE4::FField*>(FieldChild + GetGameInfo()->defs->FField.Next);
				if (NextField && NextField->GetName() == "Y")
				{
					NextFound = true;
				}
				if (NextFound == false)
				{
					GetGameInfo()->defs->FField.Next = GetGameInfo()->defs->FField.Next + 0x8;
				}
			}
			LOG_INFO("FField Next Def located at: 0x%p", GetGameInfo()->defs->FField.Next);
			return true;
		}

		bool FindUEPropertyDefs()
		{
			auto VectorObject = (UE4::UStruct*)UE4::UObject::FindObject<UE4::UObject>("ScriptStruct CoreUObject.Vector");
			bool ArrayDimFound = false;
			bool OffsetFound = false;
			if (GetGameInfo()->bIsFProperty)
			{
				auto FieldChild = (UE4::FField*)VectorObject->GetChildren();
				while (!ArrayDimFound)
				{
					if (UML::Memory::Read<int64_t>((byte*)FieldChild + GetGameInfo()->defs->Property.ArrayDim) == 17179869185) // Array Dim and Element Size are Side By Side
					{
						ArrayDimFound = true;
					}

					if (ArrayDimFound == false)
					{
						GetGameInfo()->defs->Property.ArrayDim = GetGameInfo()->defs->Property.ArrayDim + 0x8;
					}
				}
				LOG_INFO("FProperty Array Dim Def located at: 0x%p", GetGameInfo()->defs->Property.ArrayDim);

				auto FieldChildY = FieldChild->GetNext();
				auto FieldChildZ = FieldChildY->GetNext();
				GetGameInfo()->defs->Property.Offset = GetGameInfo()->defs->Property.ArrayDim + 0x8;
				while (!OffsetFound)
				{
					if (UML::Memory::Read<int32_t>((byte*)FieldChildY + GetGameInfo()->defs->Property.Offset) == 4 && UML::Memory::Read<int32_t>((byte*)FieldChildZ + GetGameInfo()->defs->Property.Offset) == 8)
					{
						OffsetFound = true;
					}
					if (OffsetFound == false)
					{
						GetGameInfo()->defs->Property.Offset = GetGameInfo()->defs->Property.Offset + 0x4;
					}
				}
				LOG_INFO("FProperty Offset Def located at: 0x%p", GetGameInfo()->defs->Property.Offset);

			}
			else
			{
				auto FieldChild = (UE4::UField*)VectorObject->GetChildren();
				while (!ArrayDimFound)
				{
					if (UML::Memory::Read<int64_t>((byte*)FieldChild + GetGameInfo()->defs->Property.ArrayDim) == 17179869185) // Array Dim and Element Size are Side By Side
					{
						ArrayDimFound = true;
					}

					if (ArrayDimFound == false)
					{
						GetGameInfo()->defs->Property.ArrayDim = GetGameInfo()->defs->Property.ArrayDim + 0x8;
					}
				}
				LOG_INFO("UProperty Array Dim Def located at: 0x%p", GetGameInfo()->defs->Property.ArrayDim);
				auto FieldChildY = FieldChild->GetNext();
				auto FieldChildZ = FieldChildY->GetNext();
				GetGameInfo()->defs->Property.Offset = GetGameInfo()->defs->Property.ArrayDim + 0x8;
				while (!OffsetFound)
				{
					if (UML::Memory::Read<int32_t>((byte*)FieldChildY + GetGameInfo()->defs->Property.Offset) == 4 && UML::Memory::Read<int32_t>((byte*)FieldChildZ + GetGameInfo()->defs->Property.Offset) == 8)
					{
						OffsetFound = true;
					}
					if (OffsetFound == false)
					{
						GetGameInfo()->defs->Property.Offset = GetGameInfo()->defs->Property.Offset + 0x4;
					}
				}
				LOG_INFO("UProperty Offset Def located at: 0x%p", GetGameInfo()->defs->Property.Offset);
			}
			return true;
		}

		bool FindUEProperty()
		{
			LOG_INFO("Scanning For UEProperty");
			auto VectorObject = (UE4::UStruct*)UE4::UObject::FindObject<UE4::UObject>("ScriptStruct CoreUObject.Vector");

			if (!VectorObject->GetChildren()->IsA(UE4::UObject::StaticClass()))
			{
				GetGameInfo()->bIsFProperty = true;
				LOG_INFO("UEProperty is a FProperty");
				if (FindFField())
				{
					GetGameInfo()->defs->Property.ArrayDim = GetGameInfo()->defs->FField.Name;
					FindUEPropertyDefs();
				}
			}
			else
			{
				GetGameInfo()->bIsFProperty = false;
				LOG_INFO("UEProperty is a UProperty");
				GetGameInfo()->defs->Property.ArrayDim = GetGameInfo()->defs->UField.Next;
				FindUEPropertyDefs();
			}
			return true;
		}
	};
};