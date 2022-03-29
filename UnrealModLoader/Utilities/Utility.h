#pragma once
#include <Windows.h>
#include <string>
#include "Logger.h"
#define LOG_INFO(msg, ...) Logger::Info(msg, __VA_ARGS__)
#define LOG_ERROR(msg, ...) Logger::Error(msg, __VA_ARGS__)
#define LOG_WARNING(msg, ...) Logger::Warn(msg, __VA_ARGS__)

namespace UML
{
	namespace Utility
	{
		PBYTE FindPattern(const char* pattern, PBYTE rangeStart = NULL, PBYTE rangeEnd = NULL);

		DWORD ConvertStringToDWord(std::string str);

		std::string GetModuleFilePath(HMODULE hModule);
	};
};