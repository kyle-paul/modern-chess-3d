#pragma once
#include "Core/Core.h"
#include "spdlog/spdlog.h"

class Logging
{
public:
	static void Init();
	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};

#define TRACE(...)	Logging::GetLogger()->trace(__VA_ARGS__)
#define INFO(...)	Logging::GetLogger()->info(__VA_ARGS__)
#define WARN(...)	Logging::GetLogger()->warn(__VA_ARGS__)
#define ERROR(...)	Logging::GetLogger()->error(__VA_ARGS__)
#define FATAL(...)	Logging::GetLogger()->critical(__VA_ARGS__)