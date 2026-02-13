#include "jeffLexer.h"

jeffLexer::jeffLexer()
{

}

jeffLexer::~jeffLexer()
{

}

std::vector<jeffLexer::jeffToken> jeffLexer::lexify(std::string inputText)
{
	std::vector<jeffToken> tokens;
	for (int readIndex = 0; readIndex < inputText.length(); readIndex++)
	{
		if (std::isspace(inputText[readIndex]))
			continue;

		// determine token at readIndex
		jeffToken curToken;
		if (!getMultiSymToken(inputText, readIndex, curToken))
		{
			if (!getStringToken(inputText, readIndex, curToken))
			{
				curToken.type = ILLEGAL;
			}
		}

		tokens.emplace_back(curToken);
	}

	jeffToken end;
	end.type = EndF;
	tokens.emplace_back(end);
	return tokens;
}

// assigns type to current token and returns true if string of symbolic characters, otherwise returns false
bool jeffLexer::getMultiSymToken(std::string inputText, int& readIndex, jeffLexer::jeffToken& curToken)
{
	int originalIndex = readIndex;

	std::string stringToken;
	for (; !std::isalnum(inputText[readIndex]) && !std::isspace(inputText[readIndex]) && readIndex < inputText.size(); readIndex++)
	{
		stringToken.push_back(inputText[readIndex]);
	}
	readIndex--;

	while (!stringToken.empty())
	{
		if (multicharDictionary.find(stringToken) != multicharDictionary.end())
		{
			curToken.type = multicharDictionary[stringToken];
			return true;
		}
		stringToken.pop_back();
		readIndex--;
	} 

	readIndex = originalIndex;
	return false;
}

bool jeffLexer::handleCharStringLiteral(std::string inputText, int& readIndex, jeffLexer::jeffToken& curToken)
{
	// TODO: handle error if unclosed quote
	if (inputText[readIndex] == '\'')
	{
		readIndex++;
		curToken.type = CHARLITERAL;
		for (; inputText[readIndex] != '\''; readIndex++)
		{
			curToken.lexeme.push_back(inputText[readIndex]);
		}
		return true;
	}
	else if (inputText[readIndex] == '"')
	{
		readIndex++;
		curToken.type = STRINGLITERAL;
		for (; inputText[readIndex] != '"'; readIndex++)
		{
			curToken.lexeme.push_back(inputText[readIndex]);
		}
		return true;
	}
	else
	{
		int originalIndex = readIndex;

		std::string stringToken;
		for (; std::isalpha(inputText[readIndex]); readIndex++)
		{
			stringToken.push_back(inputText[readIndex]);
		}
		readIndex--;

		if (stringToken == TRUTH || stringToken == UNTRUTH)
		{
			curToken.type = BOOLLITERAL;
			curToken.lexeme = stringToken;
			return true;
		}

		readIndex = originalIndex;
	}
	return false;
}

bool jeffLexer::handleIdentifier(std::string inputText, int& readIndex, jeffLexer::jeffToken& curToken)
{
	std::string stringToken;
	if (std::isalpha(inputText[readIndex]))
	{
		for (; std::isalnum(inputText[readIndex]) || inputText[readIndex] == '_'; readIndex++)
		{
			stringToken.push_back(inputText[readIndex]);
		}
		readIndex--;

		// keywords
		if (keywordDictionary.find(stringToken) != keywordDictionary.end())
		{
			curToken.type = keywordDictionary[stringToken];
		}
		// other identifiers
		else
		{
			curToken.type = ID;
			curToken.lexeme = stringToken;
		}
		return true;
	}
	return false;
}

bool jeffLexer::handleNumberLiteral(std::string inputText, int& readIndex, jeffLexer::jeffToken& curToken)
{
	std::string stringToken;
	if (std::isdigit(inputText[readIndex]))
	{
		// supports hexadecimal, octal, and binary
		for (; std::isdigit(inputText[readIndex]) || inputText[readIndex] == '.' || inputText[readIndex] == 'f' || inputText[readIndex] == 'd' || inputText[readIndex] == 'x' || inputText[readIndex] == 'b'; readIndex++)
		{
			stringToken.push_back(inputText[readIndex]);
		}
		readIndex--;

		if (stringToken.find('f') != std::string::npos)
			curToken.type = FLOATLITERAL;
		else if (stringToken.find('d') != std::string::npos)
			curToken.type = DOUBLELITERAL;
		else if (stringToken.find('.') == std::string::npos)
			curToken.type = INTLITERAL;
		curToken.lexeme = stringToken;
		return true;
	}
	return false;
}

// assigns type to current token and returns true if it is an alphanumeric token, otherwise returns false
bool jeffLexer::getStringToken(std::string inputText, int& readIndex, jeffLexer::jeffToken& curToken)
{
	if (handleCharStringLiteral(inputText, readIndex, curToken))
		return true;
	else if (handleIdentifier(inputText, readIndex, curToken))
		return true;
	else if (handleNumberLiteral(inputText, readIndex, curToken))
		return true;

	return false;
}
