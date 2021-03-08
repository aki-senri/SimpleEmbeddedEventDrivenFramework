
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

bool KeyValueConfig::ReadConfigFile(std::string file_path)
{

	return false;
}

bool KeyValueConfig::ReadConfigString(std::string config_string)
{
	std::istringstream config_stream(config_string);

	while (config_stream.good())
	{
		std::string line;

		std::getline(config_stream, line);
		StringTrimLeft(line);
		if (line[0] == '#')
		{
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

			config_elements_.insert(std::pair<std::string,std::string>{ key, value });
		}
	}

	return true;
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
