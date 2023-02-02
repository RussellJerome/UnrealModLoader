#pragma once
#include "../UE4/CoreUObject_classes.hpp"
#include "GameInfo/GameInfo.h"
namespace ClassDefFinder
{
bool FindUObjectDefs(UE4::UObject *CoreUObject, UE4::UObject *UEObject);
bool FindUFieldDefs();
bool FindUStructDefs();
bool FindUFunctionDefs();
bool FindUEProperty();
}; // namespace ClassDefFinder
