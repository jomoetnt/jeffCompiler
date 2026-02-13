#pragma once

#include <string>

class jeffPreprocessor
{
public:
	jeffPreprocessor();
	~jeffPreprocessor();

	std::string preprocessLine(std::string inputText);
	std::string preprocess(std::string inputText);
};

