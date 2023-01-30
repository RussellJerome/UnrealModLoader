#include "GameSettings.h"

GameSettings::GameSettings GameSettings::GameSettings::GetBakedSettings()
{
    GameSettings Settings = {};

    Settings.IsUsingFChunkedFixedUObjectArray = true;
    Settings.UsesFNamePool = true;

    FunctionInfoPatterns FunctionPatterns = {};
    FunctionPatterns.CallFunctionByNameWithArguments = "41 57 41 56 41 55 41 54 56 57 55 53 48 81 EC ? ? ? ? 44 0F "
                                                       "29 BC 24 ? ? ? ? 44 0F 29 B4 24 ? ? ? "
                                                       "? 44 0F 29 "
                                                       "AC 24 ? ? ? ? 44 0F 29 A4 24 ? ? ? ? 44 0F 29 9C 24 ? ? ? ? "
                                                       "44 0F 29 94 24 ? ? ? ? 44 0F 29 8C 24 "
                                                       "? ? ? ? 44 "
                                                       "0F 29 84 24 ? ? ? ? 0F 29 BC 24 ? ? ? ? 0F 29 B4 24 ? ? ? ? "
                                                       "48 8B 8C 24 ? ? ? ? 48 8B 94 24 ? ? ? "
                                                       "? 48 8B 84 "
                                                       "24 ? ? ? ? 4C 8B 40 18 0F 28 3D";

    FunctionInfo Info = {};
    Info.Info = FunctionPatterns;

    Settings.FunctionInfoSettings = Info;

    return Settings;
}