#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace LostSouls {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		// Setting the pattern of the text (set text color,[timeStamp] loggerName: logMessage)
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// Set up the core logger
		s_CoreLogger = spdlog::stdout_color_mt("LOSTSOULS");
		s_CoreLogger->set_level(spdlog::level::trace);

		// Set up the client logger 
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);

	}
}