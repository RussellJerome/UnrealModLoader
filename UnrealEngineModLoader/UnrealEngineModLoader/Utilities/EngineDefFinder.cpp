#include "../UE4/Ue4.hpp"
#include "Utilities/Logger.h"
namespace ClassDefFinder
{
	bool FindUObjectIndexDefs(UE4::UObject* CoreUObject)
	{
		Log::Info("Scanning For UObject Index Def.");
		while (Read<int32_t>((byte*)CoreUObject + GameProfile::SelectedGameProfile.defs.UObject.Index) != 1)
		{
			GameProfile::SelectedGameProfile.defs.UObject.Index = GameProfile::SelectedGameProfile.defs.UObject.Index + 0x4;
		}
		Log::Info("UObject Index Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UObject.Index);
		return true;
	};

	bool FindUObjectNameDefs(UE4::UObject* CoreUObject)
	{
		bool HasNameNotBeenFound = true;
		Log::Info("Scanning For UObject Name Def.");
		while (HasNameNotBeenFound)
		{
			auto Name = *reinterpret_cast<UE4::FName*>((byte*)CoreUObject + GameProfile::SelectedGameProfile.defs.UObject.Name);
			if (GameProfile::SelectedGameProfile.UsesFNamePool)
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
				GameProfile::SelectedGameProfile.defs.UObject.Name = GameProfile::SelectedGameProfile.defs.UObject.Name + 0x8;
			}
		}
		Log::Info("UObject Name Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UObject.Name);
		return true;
	}

	bool FindUObjectClassDefs(UE4::UObject* CoreUObject)
	{
		bool HasClassNotBeenFound = true;
		Log::Info("Scanning For UObject Class Def.");
		while (HasClassNotBeenFound)
		{
			auto Class = Read<UE4::UClass*>((byte*)CoreUObject + GameProfile::SelectedGameProfile.defs.UObject.Class);
			auto ClassIndex = Class->GetIndex();
			UE4::UObject* ClassCheck;
			if (GameProfile::SelectedGameProfile.IsUsingFChunkedFixedUObjectArray)
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
				GameProfile::SelectedGameProfile.defs.UObject.Class = GameProfile::SelectedGameProfile.defs.UObject.Class + 0x8;
			}
		}
		Log::Info("UObject Class Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UObject.Class);
		return true;
	}

	bool FindUObjectOuterDefs(UE4::UObject* CoreUObject)
	{
		bool HasOuterNotBeenFound = true;
		Log::Info("Scanning For UObject Outer Def.");
		while (HasOuterNotBeenFound)
		{
			auto Outer = Read<UE4::UObject*>((byte*)CoreUObject + GameProfile::SelectedGameProfile.defs.UObject.Outer);
			UE4::UObject* ObjectCheck;
			if (GameProfile::SelectedGameProfile.IsUsingFChunkedFixedUObjectArray)
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
				GameProfile::SelectedGameProfile.defs.UObject.Outer = GameProfile::SelectedGameProfile.defs.UObject.Outer + 0x8;
			}
		}
		Log::Info("UObject Outer Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UObject.Outer);
		return true;
	}

	bool FindUObjectDefs(UE4::UObject* CoreUObject)
	{
		if (FindUObjectIndexDefs(CoreUObject) && FindUObjectNameDefs(CoreUObject) && FindUObjectClassDefs(CoreUObject) && FindUObjectOuterDefs(CoreUObject))
		{
			Log::Info("UObject Defined");
			return true;
		}
		else
		{
			Log::Error("UObject could not be defined. Try Manually Defining in the game profile file.");
		}
		return false;
	}

	bool FindUFieldNextDef()
	{
		Log::Info("Scanning For UField Next Def.");
		bool HasNextNotBeenFound = true;
		auto WasRecentlyRendered = UE4::UObject::FindObject<UE4::UFunction>("Function Engine.Actor.WasRecentlyRendered");
		GameProfile::SelectedGameProfile.defs.UField.Next = GameProfile::SelectedGameProfile.defs.UObject.Outer; // Prevents scanning same area over and over.
		while (HasNextNotBeenFound)
		{
			auto NextObject = Read<UE4::UField*>((byte*)WasRecentlyRendered + GameProfile::SelectedGameProfile.defs.UField.Next);
			if (NextObject && NextObject->GetIndex() == WasRecentlyRendered->GetIndex() - 1)
			{
				HasNextNotBeenFound = false;
			}
			if (HasNextNotBeenFound)
			{
				GameProfile::SelectedGameProfile.defs.UField.Next = GameProfile::SelectedGameProfile.defs.UField.Next + 0x8;
			}
		}
		Log::Info("UField Next Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UField.Next);
		return true;
	}

	bool FindUFieldDefs()
	{
		if (FindUFieldNextDef())
		{
			Log::Info("UField Defined");
			return true;
		}
		else
		{
			Log::Error("UField could not be defined. Try Manually Defining in the game profile file.");
		}
		return false;
	}

	bool FindUStructSuperFieldDef()
	{
		Log::Info("Scanning For UStruct SuperField Def.");
		auto StructObject = UE4::UObject::FindObject<UE4::UStruct>("Class CoreUObject.Struct");
		auto FieldObject = UE4::UObject::FindObject<UE4::UField>("Class CoreUObject.Field");
		bool HasSuperFieldNotBeenFound = true;
		GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct = GameProfile::SelectedGameProfile.defs.UField.Next; // Prevents scanning same area over and over.
		while (HasSuperFieldNotBeenFound)
		{
			auto SuperFieldObject = Read<UE4::UObject*>((byte*)StructObject + GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct);
			if (SuperFieldObject == FieldObject)
			{
				HasSuperFieldNotBeenFound = false;
			}
			if (HasSuperFieldNotBeenFound)
			{
				GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct = GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct + 0x8;
			}
		}
		Log::Info("UStruct SuperField Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct);
		return true;
	}

	bool FindUStructChildrenDef()
	{
		Log::Info("Scanning For UStruct Children Def.");
		auto VectorObject = UE4::UObject::FindObject<UE4::UObject>("ScriptStruct CoreUObject.Vector");
		auto VectorFirstChildObject = UE4::UObject::FindObject<UE4::UObject>("FloatProperty CoreUObject.Vector.X");
		bool HasChildrenNotBeenFound = true;
		GameProfile::SelectedGameProfile.defs.UStruct.Children = GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct;
		while (HasChildrenNotBeenFound)
		{
			auto ChildObject = Read<UE4::UObject*>((byte*)VectorObject + GameProfile::SelectedGameProfile.defs.UStruct.Children);
			if (VectorFirstChildObject)
			{
				if (VectorFirstChildObject == ChildObject)
				{
					HasChildrenNotBeenFound = false;
				}
				if (HasChildrenNotBeenFound)
				{
					GameProfile::SelectedGameProfile.defs.UStruct.Children = GameProfile::SelectedGameProfile.defs.UStruct.Children + 0x8;
				}
			}
			else
			{
				if (auto Class = ChildObject->GetClass())
				{
					if (Class->GetName() == "FloatProperty" || "Vector")
					{
						HasChildrenNotBeenFound = false;
					}
					else
					{
						GameProfile::SelectedGameProfile.defs.UStruct.Children = GameProfile::SelectedGameProfile.defs.UStruct.Children + 0x8;
					}
				}
				else
				{
					GameProfile::SelectedGameProfile.defs.UStruct.Children = GameProfile::SelectedGameProfile.defs.UStruct.Children + 0x8;
				}
			}
		}
		Log::Info("UStruct Children Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UStruct.Children);
		return true;
	}

	bool FindUStructPropertySizeDef()
	{
		Log::Info("Scanning For UStruct PropertySize Def.");
		auto VectorObject = UE4::UObject::FindObject<UE4::UObject>("ScriptStruct CoreUObject.Vector");
		while (Read<int32_t>((byte*)VectorObject + GameProfile::SelectedGameProfile.defs.UStruct.PropertiesSize) != 12)
		{
			GameProfile::SelectedGameProfile.defs.UStruct.PropertiesSize = GameProfile::SelectedGameProfile.defs.UStruct.PropertiesSize + 0x4;
		}
		Log::Info("UStruct PropertySize Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UStruct.PropertiesSize);
		return true;
	}

	int GetOverallUStructSize()
	{
		auto UStruct = UE4::UObject::FindObject<UE4::UStruct>("Class CoreUObject.Struct");
		if (UStruct)
		{
			return UStruct->GetPropertySize();
		}
	}

	bool FindUStructDefs()
	{
		if (FindUStructSuperFieldDef() && FindUStructChildrenDef() && FindUStructPropertySizeDef())
		{
			GameProfile::SelectedGameProfile.defs.UStruct.OverallUStructSize = GetOverallUStructSize();
			Log::Info("UStruct Size: %i", GameProfile::SelectedGameProfile.defs.UStruct.OverallUStructSize);
			Log::Info("UStruct Defined");
			return true;
		}
		else
		{
			Log::Error("UStruct could not be defined. Try Manually Defining in the game profile file.");
		}
		return false;
	}

	bool FindUFunctionFunctionFlagsDef()
	{
		Log::Info("Scanning For UFunction FunctionFlags Def.");
		bool HasFunctionFlagsNotBeenFound = true;
		auto WasRecentlyRendered = UE4::UObject::FindObject<UE4::UFunction>("Function Engine.Actor.WasRecentlyRendered");
		GameProfile::SelectedGameProfile.defs.UFunction.FunctionFlags = GameProfile::SelectedGameProfile.defs.UStruct.OverallUStructSize; // Prevents scanning same area over and over.
		while (HasFunctionFlagsNotBeenFound)
		{
			auto FunctionFlags = Read<int>((byte*)WasRecentlyRendered + GameProfile::SelectedGameProfile.defs.UFunction.FunctionFlags);
			if (FunctionFlags == 1409418241)
			{
				HasFunctionFlagsNotBeenFound = false;
			}
			if (HasFunctionFlagsNotBeenFound)
			{
				GameProfile::SelectedGameProfile.defs.UFunction.FunctionFlags = GameProfile::SelectedGameProfile.defs.UFunction.FunctionFlags + 0x4;
			}
		}
		Log::Info("UFunction FunctionFlags Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UFunction.FunctionFlags);
		return true;
	}

	bool FindUFunctionFunc()
	{
		auto UFunction = UE4::UObject::FindObject<UE4::UFunction>("Class CoreUObject.Function");
		if (UFunction)
		{
			GameProfile::SelectedGameProfile.defs.UFunction.Func = UFunction->GetPropertySize() - 0x8;
			Log::Info("UFunction Func: 0x%p", GameProfile::SelectedGameProfile.defs.UFunction.Func);
			return true;
		}
		return false;
	}

	bool FindUFunctionDefs()
	{
		if (FindUFunctionFunctionFlagsDef() && FindUFunctionFunc())
		{
			Log::Info("UFunction Defined");
			return true;
		}
		else
		{
			Log::Error("UFunction could not be defined. Try Manually Defining in the game profile file.");
		}
		return false;
	}

	bool FindPersistentLevelDef()
	{
		bool HasPersistentLevelNotBeenFound = true;
		GameProfile::SelectedGameProfile.defs.UWorld.PersistentLevel = GameProfile::SelectedGameProfile.defs.UObject.Outer + 0x8;
		while (HasPersistentLevelNotBeenFound)
		{
			auto PersistentLevel = Read<UE4::ULevel*>((byte*)UE4::UWorld::GetWorld() + GameProfile::SelectedGameProfile.defs.UWorld.PersistentLevel);
			if (PersistentLevel != nullptr && PersistentLevel->IsA(UE4::ULevel::StaticClass()))
			{
				if (PersistentLevel->GetName() == "PersistentLevel" && PersistentLevel->GetClass()->GetName() == "Level")
				{
					Log::Info("PersistentLevel: 0x%p", GameProfile::SelectedGameProfile.defs.UWorld.PersistentLevel);
					HasPersistentLevelNotBeenFound = false;
				}
			}
			if (HasPersistentLevelNotBeenFound)
			{
				GameProfile::SelectedGameProfile.defs.UWorld.PersistentLevel = GameProfile::SelectedGameProfile.defs.UWorld.PersistentLevel + 0x8;
			}
		}
		Log::Info("Persistent Level Found.");
		return true;
	}

	bool FindGameModeDef()
	{
		bool HasGameModeNotBeenFound = true;
		GameProfile::SelectedGameProfile.defs.UWorld.AuthorityGameMode = GameProfile::SelectedGameProfile.defs.UWorld.PersistentLevel + 0x8;
		while (HasGameModeNotBeenFound)
		{
			auto AuthorityGameMode = Read<UE4::AGameModeBase*>((byte*)UE4::UWorld::GetWorld() + GameProfile::SelectedGameProfile.defs.UWorld.AuthorityGameMode);
			if (AuthorityGameMode != nullptr && AuthorityGameMode->IsA(UE4::AGameModeBase::StaticClass()))
			{
				Log::Info("AuthorityGameMode: 0x%p", GameProfile::SelectedGameProfile.defs.UWorld.AuthorityGameMode);
				HasGameModeNotBeenFound = false;
			}
			if (HasGameModeNotBeenFound)
			{
				GameProfile::SelectedGameProfile.defs.UWorld.AuthorityGameMode = GameProfile::SelectedGameProfile.defs.UWorld.AuthorityGameMode + 0x8;
			}
		}
		Log::Info("Authority GameMode Found.");
		return true;
	}

	bool FindWorldArrayDef()
	{
		GameProfile::SelectedGameProfile.defs.ULevel.WorldArray = GameProfile::SelectedGameProfile.defs.UObject.Outer + 0x8 + 0x78;
		Log::Info("World Actor Array: 0x%p", GameProfile::SelectedGameProfile.defs.ULevel.WorldArray);
		Log::Info("World Actors Found.");
		return true;
	}

	bool FindEngineClasses()
	{
		Log::Warn("Engine Classes Not Defined. Starting Automatic Class Finder.");
		UE4::UObject* CoreUobjectObject;
		if (GameProfile::SelectedGameProfile.IsUsingFChunkedFixedUObjectArray)
		{
			CoreUobjectObject = UE4::UObject::GObjects->GetAsChunckArray().GetByIndex(1).Object;
		}
		else
		{
			CoreUobjectObject = UE4::UObject::GObjects->GetAsTUArray().GetByIndex(1).Object;
		}
		if (FindUObjectDefs(CoreUobjectObject) && FindUFieldDefs() && FindUStructDefs() && FindUFunctionDefs())
		{
			if (GameProfile::SelectedGameProfile.IsUWorldMissing)
			{
				FindPersistentLevelDef();
				FindGameModeDef();
				FindWorldArrayDef();
			}
			return true;
		}
		return false;
	};
};