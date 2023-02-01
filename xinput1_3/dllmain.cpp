#include <Windows.h>

#pragma region Proxy
struct xinput1_3_dll
{
    HMODULE dll;
    FARPROC oDllMain;
    FARPROC oXInputEnable;
    FARPROC oXInputGetBatteryInformation;
    FARPROC oXInputGetCapabilities;
    FARPROC oXInputGetDSoundAudioDeviceGuids;
    FARPROC oXInputGetKeystroke;
    FARPROC oXInputGetState;
    FARPROC oXInputSetState;
} xinput1_3;

extern "C"
{
    FARPROC PA = 0;
    int runASM();

    void fDllMain()
    {
        PA = xinput1_3.oDllMain;
        runASM();
    }
    void fXInputEnable()
    {
        PA = xinput1_3.oXInputEnable;
        runASM();
    }
    void fXInputGetBatteryInformation()
    {
        PA = xinput1_3.oXInputGetBatteryInformation;
        runASM();
    }
    void fXInputGetCapabilities()
    {
        PA = xinput1_3.oXInputGetCapabilities;
        runASM();
    }
    void fXInputGetDSoundAudioDeviceGuids()
    {
        PA = xinput1_3.oXInputGetDSoundAudioDeviceGuids;
        runASM();
    }
    void fXInputGetKeystroke()
    {
        PA = xinput1_3.oXInputGetKeystroke;
        runASM();
    }
    void fXInputGetState()
    {
        PA = xinput1_3.oXInputGetState;
        runASM();
    }
    void fXInputSetState()
    {
        PA = xinput1_3.oXInputSetState;
        runASM();
    }
}

void setupFunctions()
{
    xinput1_3.oDllMain = GetProcAddress(xinput1_3.dll, "DllMain");
    xinput1_3.oXInputEnable = GetProcAddress(xinput1_3.dll, "XInputEnable");
    xinput1_3.oXInputGetBatteryInformation = GetProcAddress(xinput1_3.dll, "XInputGetBatteryInformation");
    xinput1_3.oXInputGetCapabilities = GetProcAddress(xinput1_3.dll, "XInputGetCapabilities");
    xinput1_3.oXInputGetDSoundAudioDeviceGuids = GetProcAddress(xinput1_3.dll, "XInputGetDSoundAudioDeviceGuids");
    xinput1_3.oXInputGetKeystroke = GetProcAddress(xinput1_3.dll, "XInputGetKeystroke");
    xinput1_3.oXInputGetState = GetProcAddress(xinput1_3.dll, "XInputGetState");
    xinput1_3.oXInputSetState = GetProcAddress(xinput1_3.dll, "XInputSetState");
}
#pragma endregion

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        xinput1_3.dll = LoadLibrary(L"\\System32\\xinput1_3.dll");
        setupFunctions();

        LoadLibrary(L"UnrealEngineModLoader.dll");

        break;
    case DLL_PROCESS_DETACH:
        FreeLibrary(xinput1_3.dll);
        break;
    }
    return 1;
}
