#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include <iostream>

class KeyValueConfig
{
public:
	KeyValueConfig();
	~KeyValueConfig();

	bool ReadConfigStream(std::istream& stream);
	bool ReadConfigFile(std::string file_path);
	bool ReadConfigString(std::string config_string);

	bool WriteConfigStream(std::ostream& stream);
	bool WriteConfigFile(std::string file_path);
	bool WriteConfigString(std::string config_string);

private:
	std::string file_path_;
	std::map<std::string, std::map<std::string, std::string>> config_elements_;
	std::vector<std::string> KeyValueConfig::StringSplit(const std::string& s, char delim);
	bool KeyValueConfig::StringTrimLeft(std::string& str);
	bool KeyValueConfig::StringTrimRight(std::string& str);
};