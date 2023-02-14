#pragma once

#ifdef UNREALCPPLOADER_EXPORTS
#define LOADER_API __declspec(dllexport)
#else
#define LOADER_API __declspec(dllimport)
#endif

#define BPFUNCTION(Function)                                                                                           \
    void Function(UE4::UObject *ContextObject, UE4::FFrame *stack, void *const ret,                                    \
                  void *(*OriginalFunction)(UE4::UObject *, UE4::FFrame *, void *))

#define REGISTER_FUNCTION(Function) Global::GetGlobals()->AddBPFunctionWrapper(#Function, Function);