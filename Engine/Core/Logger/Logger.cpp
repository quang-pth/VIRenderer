#include"Logger.h"

#include<spdlog/common.h>
#include<spdlog/fmt/ostr.h>
#include<spdlog/sinks/stdout_color_sinks.h>

namespace VIEngine {
	std::shared_ptr<spdlog::logger> Logger::sCoreLogger = nullptr;
	std::shared_ptr<spdlog::logger> Logger::sClientLogger = nullptr;

	void Logger::Init() {
		// Example: [22:40:00] [VIEngine::Logger:Init:11] [VIEngine] [Thread:1000] Logger works
		spdlog::set_pattern("%^[%H:%M:%S] [%!:%#] [%n] [Thread:%t] %v%$");

		sCoreLogger = spdlog::stdout_color_mt("VIEngine");
		sCoreLogger->set_level(spdlog::level::trace);
        VI_ASSERT(sCoreLogger != nullptr && "Failed to init Core Logger");
        
		sClientLogger = spdlog::stdout_color_mt("Client");
		sClientLogger->set_level(spdlog::level::trace);
        VI_ASSERT(sClientLogger != nullptr && "Failed to init Client Logger");
	}
}