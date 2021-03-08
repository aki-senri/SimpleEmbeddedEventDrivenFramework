#include "Logger.h"
#ifdef WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#elif __unix__
#else
#endif

Logger::Logger()
{
}

Logger::Logger(std::unique_ptr<std::ostream> output_stream)
{
	output_stream_ = std::move(output_stream);
}

Logger::~Logger()
{
}

bool Logger::SetLogOutputTarget(std::unique_ptr<std::ostream> stream)
{

	return false;
}

bool Logger::SetLogLevel(LogLevel level)
{
	log_level_ = level;
	return true;
}

bool Logger::Output(LogLevel level, std::string message)
{
	if (!output_stream_->good())
	{
		return false;
	}

	if ((log_level_ != LogLevel::Off) &&
		(level >= log_level_))
	{
#ifdef WIN32
		SYSTEMTIME system_time;
		GetLocalTime(&system_time);
#else
#endif

		*output_stream_ << system_time.wYear << "/" << system_time.wMonth << "/" << system_time.wDay << " "
						<< system_time.wHour << ":" << system_time.wMinute << ":" << system_time.wSecond << "." << system_time.wMilliseconds
						<< " : " << message << std::endl;
	}

	return false;
}
