#include "Dumper.h"
#include <windows.h>
#include "../UE4/Ue4.hpp"
#include "Globals.h"
bool bDumpObjects;
bool bDumpEngineInfo;
bool bDumpWorldActors;
namespace Dumper
{
	bool DumpObjects()
	{
		FILE* Log = NULL;
		fopen_s(&Log, "ObjectDump.txt", "w+");
		if (UE4::UObject::GObjects != nullptr)
		{
			if (GameProfile::SelectedGameProfile.IsUsingFChunkedFixedUObjectArray)
			{
				for (int i = 0; i < UE4::UObject::GObjects->GetAsChunckArray().Num(); i++)
				{
					auto obj = UE4::UObject::GObjects->GetAsChunckArray().GetByIndex(i).Object;
					if (obj != nullptr)
						fprintf(Log, "[%06i] %-100s 0x%p\n", obj->GetIndex(), obj->GetFullName().c_str(), obj);
				}
				Log::SetupMessage("Done!", "Object Dump Complete!");
			}
			else
			{
				for (int i = 0; i < UE4::UObject::GObjects->GetAsTUArray().Num(); i++)
				{
					auto obj = UE4::UObject::GObjects->GetAsTUArray().GetByIndex(i).Object;
					if (obj != nullptr)
						fprintf(Log, "[%06i] %-100s 0x%p\n", obj->GetIndex(), obj->GetFullName().c_str(), obj);
				}
				Log::SetupMessage("Done!", "Object Dump Complete!");
			}
			Log::Info("Object Dump Complete!");
			fclose(Log);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool DumpEngineInfo()
	{
		FILE* Log = NULL;
		fopen_s(&Log, "EngineInfo.txt", "w+");
		fprintf(Log, "#Engine Info Dump\n");
		fprintf(Log, "[GInfo]\nIsGInfoPatterns=0\nGName=0x%p\nGObject=0x%p\nGWorld=0x%p\n", GameProfile::SelectedGameProfile.GName - (DWORD64)GetModuleHandleW(0), GameProfile::SelectedGameProfile.GObject - (DWORD64)GetModuleHandleW(0), GameProfile::SelectedGameProfile.GWorld - (DWORD64)GetModuleHandleW(0));
		fprintf(Log, "\n[UObjectDef]\nIndex=0x%p\nClass=0x%p\nName=0x%p\nOuter=0x%p\n", GameProfile::SelectedGameProfile.defs.UObject.Index, GameProfile::SelectedGameProfile.defs.UObject.Class, GameProfile::SelectedGameProfile.defs.UObject.Name, GameProfile::SelectedGameProfile.defs.UObject.Outer);
		fprintf(Log, "\n[UFieldDef]\nNext=0x%p\n", GameProfile::SelectedGameProfile.defs.UField.Next);
		fprintf(Log, "\n[UStructDef]\nSuperStruct=0x%p\nChildren=0x%p\nPropertiesSize=0x%p\n", GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct, GameProfile::SelectedGameProfile.defs.UStruct.Children, GameProfile::SelectedGameProfile.defs.UStruct.PropertiesSize);
		fprintf(Log, "\n[UFunctionDef]\nFunctionFlags=0x%p\nFunc=0x%p\n", GameProfile::SelectedGameProfile.defs.UFunction.FunctionFlags, GameProfile::SelectedGameProfile.defs.UFunction.Func);
		fclose(Log);
		Log::SetupMessage("Done!", "Engine Info Dump Complete!");
		Log::Info("Engine Info Dump Complete!");
		return true;
	}

	bool DumpWorldActors()
	{
		FILE* Log = NULL;
		fopen_s(&Log, "WorldActorDump.txt", "w+");
		if (UE4::UWorld::GetWorld()->GetPersistentLevel())
		{
			auto GameplayStatics = (UE4::UGameplayStatics*)UE4::UGameplayStatics::StaticClass()->CreateDefaultObject();
			fprintf(Log, "#Level: %s\n\n", GameplayStatics->GetCurrentLevelName(false).ToString().c_str());
			for (int i = 0; i < UE4::UWorld::GetWorld()->GetPersistentLevel()->GetWorldActors().Num(); i++)
			{
				auto CurrentActor = UE4::UWorld::GetWorld()->GetPersistentLevel()->GetWorldActors()[i];
				if (CurrentActor != nullptr)
				{
					auto Transform = CurrentActor->GetTransform();
					fprintf(Log, "ActorName: %s\n", CurrentActor->GetName().c_str());
					fprintf(Log, "ClassName: %s\n", CurrentActor->GetClass()->GetName().c_str());
					fprintf(Log, "Location: %f, %f, %f\n", Transform.Translation.X, Transform.Translation.Y, Transform.Translation.Z);
					auto Rota = CurrentActor->GetActorRotation();
					fprintf(Log, "Rotation: %f, %f, %f\n", Rota.Pitch, Rota.Roll, Rota.Yaw);
					fprintf(Log, "Scale: %f, %f, %f\n", Transform.Scale3D.X, Transform.Scale3D.Y, Transform.Scale3D.Z);
					fprintf(Log, "\n");

				}
			}
		}
		Log::SetupMessage("Done!", "World Actors Dump Complete!");
		fclose(Log);
		return true;
	}
	bool f1_pressed;
	void KeyDetectionLoop()
	{
		while (true)
		{
			if (GetAsyncKeyState(VK_F1) != 0)
				f1_pressed = true;
			else if (f1_pressed)
			{
				f1_pressed = false;
				if (Global::bIsMenuOpen)
				{
					Global::bIsMenuOpen = false;
				}
				else
				{
					Global::bIsMenuOpen = true;
				}
			}

			if (bDumpObjects)
			{
				bDumpObjects = false;
				DumpObjects();
			}


			if (bDumpEngineInfo)
			{
				bDumpEngineInfo = false;
				DumpEngineInfo();
			}
			if (bDumpWorldActors)
			{
				bDumpWorldActors = false;
				DumpWorldActors();
			}
			Sleep(1000 / 60);
		}
	}

	DWORD __stdcall LoopThread(LPVOID)
	{
		Dumper::KeyDetectionLoop();
		return NULL;
	}


	void BeginObjectDump()
	{
		bDumpObjects = true;
	}

	void BeginEngineDump()
	{
		bDumpEngineInfo = true;
	}

	void BeginWorldDump()
	{
		bDumpWorldActors = true;
	}

	void BeginKeyThread()
	{
		CreateThread(0, 0, LoopThread, 0, 0, 0);
	}
}