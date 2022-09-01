#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace LostSouls{

	class LOSTSOULS_API Log
	{
	public: 
		static void Init();
	
		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	
	};
}

// Core logging macros
#define LS_CORE_TRACE(...) ::LostSouls::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LS_CORE_INFO(...)  ::LostSouls::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LS_CORE_WARN(...)  ::LostSouls::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LS_CORE_ERROR(...) ::LostSouls::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LS_CORE_FATAL(...) ::LostSouls::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client logging macros
#define LS_TRACE(...) ::LostSouls::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LS_INFO(...)  ::LostSouls::Log::GetClientLogger()->info(__VA_ARGS__)
#define LS_WARN(...)  ::LostSouls::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LS_ERROR(...) ::LostSouls::Log::GetClientLogger()->error(__VA_ARGS__)
#define LS_FATAL(...) ::LostSouls::Log::GetClientLogger()->fatal(__VA_ARGS__)
