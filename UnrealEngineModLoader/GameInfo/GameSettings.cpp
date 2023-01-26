#include "GameSettings.h"

GameSettings::GameSettings GameSettings::GameSettings::GetBakedSettings()
{
    GameSettings Settings = {};

    Settings.IsUsingFChunkedFixedUObjectArray = true;
    Settings.UsesFNamePool = true;

    return Settings;
}