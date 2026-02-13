#include "jeffIO.h"

jeffIO::jeffIO()
{

}

jeffIO::~jeffIO()
{

}

std::string jeffIO::readFile(std::string filename)
{
	std::string fileText;

	std::ifstream inputFile;
	inputFile.open(filename.c_str(), std::ios::in);
	assert(inputFile.is_open());

	jeffPreprocessor jeffpre;

	std::string line;
	while (std::getline(inputFile, line))
	{
		line = jeffpre.preprocessLine(line);
		fileText.append(line);
	}

	inputFile.close();

	return jeffpre.preprocess(fileText);
}