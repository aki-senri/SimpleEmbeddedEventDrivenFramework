#pragma once

#include <ostream>
#include <memory>

class Logger
{
public:
	Logger();
	Logger(std::unique_ptr<std::ostream> output_stream);
	~Logger();

	bool SetLogOutputTarget(std::unique_ptr<std::ostream> stream);

	enum class LogLevel
	{
		All = 0,
		Debug = 1,
		Info = 2,
		Warning = 3,
		Error = 4,
		Fatal = 5,
		Off = 6,
	};

	bool SetLogLevel(LogLevel level);

	bool Output(LogLevel level, std::string message);

private:
	std::unique_ptr<std::ostream> output_stream_;
	LogLevel log_level_;
};