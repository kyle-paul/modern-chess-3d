#include "Core/Debug/Logging.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Logging::s_Logger;

void Logging::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_Logger = spdlog::stdout_color_mt("CHESS");
    s_Logger->set_level(spdlog::level::trace);
}