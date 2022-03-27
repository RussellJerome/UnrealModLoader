#pragma once
#include <windows.h>
#include <string>
#include <mutex>

#define LOGGER_SOURCE "UnrealModLoader"

#define LOG_STREAM stdout

class Logger
{
private:
	enum class MsgType
	{
		INFO_MSG = 0,
		WARNING_MSG = 1,
		ERROR_MSG = 2,
		INFO_PRINTCONSOLE = 3
	};

	static std::mutex log_mutex;

	template <typename ...Args>
	static void LogMsg(MsgType type, const std::string& format, Args&& ...args)
	{
		std::scoped_lock lock(log_mutex);
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		fprintf(LOG_STREAM, "[");
		SetConsoleTextAttribute(hConsole, 11);
		fprintf(LOG_STREAM, LOGGER_SOURCE);
		SetConsoleTextAttribute(hConsole, 7);
		fprintf(LOG_STREAM, "][");

		switch (type)
		{
		case MsgType::INFO_MSG:
			SetConsoleTextAttribute(hConsole, 10);
			fprintf(LOG_STREAM, "INFO");
			break;
		case MsgType::WARNING_MSG:
			SetConsoleTextAttribute(hConsole, 14);
			fprintf(LOG_STREAM, "WARNING");
			break;
		case MsgType::ERROR_MSG:
			SetConsoleTextAttribute(hConsole, 12);
			fprintf(LOG_STREAM, "ERROR");
			break;
		case MsgType::INFO_PRINTCONSOLE:
			SetConsoleTextAttribute(hConsole, 13);
			fprintf(LOG_STREAM, "PRINT");
			break;
		}

		auto size = std::snprintf(nullptr, 0, format.c_str(), std::forward<Args>(args)...);
		std::string output(size + 1, '\0');
		std::sprintf(&output[0], format.c_str(), std::forward<Args>(args)...);

		SetConsoleTextAttribute(hConsole, 7);
		fprintf(LOG_STREAM, "] %s\n", output.c_str());
		//LogArray.push_back(output);
	}

public:
	template <typename ...Args>
	static void Info(const std::string& format, Args&& ...args)
	{
		LogMsg(MsgType::INFO_MSG, format, std::forward<Args>(args)...);
	}

	template <typename ...Args>
	static void Warn(const std::string& format, Args&& ...args)
	{
		LogMsg(MsgType::WARNING_MSG, format, std::forward<Args>(args)...);
	}

	template <typename ...Args>
	static void Error(const std::string& format, Args&& ...args)
	{
		LogMsg(MsgType::ERROR_MSG, format, std::forward<Args>(args)...);
	}

	template <typename ...Args>
	static void Print(const std::string& format, Args&& ...args)
	{
		LogMsg(MsgType::INFO_PRINTCONSOLE, format, std::forward<Args>(args)...);
	}
};