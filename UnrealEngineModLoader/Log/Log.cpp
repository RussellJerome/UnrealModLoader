#include "Log.h"
#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/wincolor_sink.h>

void Log::Init()
{
    auto ConsoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    ConsoleSink->set_level(spdlog::level::trace);
    ConsoleSink->set_pattern("[%^%l%$] %v");

    auto FileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("UML-Log.txt", true);
    ConsoleSink->set_level(spdlog::level::trace);
    ConsoleSink->set_pattern("[%^%l%$] %v");

    spdlog::logger Logger("logger", {ConsoleSink, FileSink});

    auto SharedLogger = std::make_shared<spdlog::logger>(Logger);
    SharedLogger->set_level(spdlog::level::trace);
    SharedLogger->info("[Logger] Logger initialized");

    spdlog::set_default_logger(SharedLogger);
    spdlog::flush_every(std::chrono::seconds(1));
}