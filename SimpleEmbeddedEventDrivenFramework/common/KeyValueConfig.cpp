
#include "KeyValueConfig.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <locale>
#include <utility>

KeyValueConfig::KeyValueConfig()
{
}

KeyValueConfig::~KeyValueConfig()
{
}

bool KeyValueConfig::ReadConfigStream(std::istream& stream)
{
	std::string section_name = "";

	while (stream.good())
	{
		std::string line;

		std::getline(stream, line);
		StringTrimLeft(line);
		if (line[0] == '#')
		{
			continue;
		}

		if (line[0] == '[')
		{
			std::string::size_type tail = line.find_last_not_of(']');
			if (tail != std::string::npos)
			{
				section_name = line.substr(1, tail);
			}
			continue;
		}

		std::vector<std::string> keyvalue = StringSplit(line, '=');

		if (keyvalue.size() == 2)
		{
			std::string key = keyvalue[0];
			std::string value = keyvalue[1];

			StringTrimLeft(key);
			StringTrimRight(key);
			StringTrimLeft(value);
			StringTrimRight(value);

			config_elements_[section_name].insert(std::pair<std::string, std::string>{ key, value });
		}
	}

	return true;
}

bool KeyValueConfig::ReadConfigFile(std::string file_path)
{
	std::ifstream config_stream(file_path);

	return ReadConfigStream(config_stream);
}

bool KeyValueConfig::ReadConfigString(std::string config_string)
{
	std::istringstream config_stream(config_string);

	return ReadConfigStream(config_stream);
}

bool KeyValueConfig::WriteConfigStream(std::ostream& stream)
{
	for(auto element : config_elements_)
	{
		if (element.first.size() > 0)
		{
			stream << "[" << element.first << "]" << std::endl;
		}

		for (auto key_value : element.second)
		{
			stream << key_value.first << "=" << key_value.second << std::endl;
		}
		stream << std::endl;
	}

	return true;
}

bool KeyValueConfig::WriteConfigFile(std::string file_path)
{
	std::ofstream config_stream(file_path);

	return WriteConfigStream(config_stream);
}

bool KeyValueConfig::WriteConfigString(std::string config_string)
{
	std::ostringstream config_stream(config_string);

	return WriteConfigStream(config_stream);
}

std::vector<std::string> KeyValueConfig::StringSplit(const std::string& s, char delim) {
	std::vector<std::string> elems;
	std::string item;
	for (char ch : s)
	{
		if (ch == delim)
		{
			if (!item.empty())
			{
				elems.push_back(item);
			}
			item.clear();
		}
		else
		{
			item += ch;
		}
	}

	if (!item.empty())
	{
		elems.push_back(item);
	}

	return elems;
}

bool KeyValueConfig::StringTrimLeft(std::string& str)
{
	bool result = false;

	size_t head = str.find_first_not_of(' ', 0);

	if (head != std::string::npos)
	{
		str.erase(0, head);
		result = true;
	}

	return result;
}

bool KeyValueConfig::StringTrimRight(std::string& str)
{
	bool result = false;

	size_t tail = str.find_last_not_of(' ', str.length());

	if (tail != std::string::npos)
	{
		str.erase(tail + 1, str.length());
		result = true;
	}

	return result;
}
