#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class jeffLexer
{
public:
	enum TOKENTYPE
	{
		// special
		ILLEGAL, EndF,
		// user-defined
		ID,
		// demarcations
		LPAR, RPAR, LBRACKET, RBRACKET, LBRACE, RBRACE,
		// punctuation
		COMMA, DOT, SEMICOLON, COLON, QUOTE, DQUOTE, QMARK,
		EOL, ESCAPE,
		// operators
		PLUS, MINUS, TIMES, DIVIDE,
		ASSIGN, ASSIGNADD, ASSIGNSUB, ASSIGNMUL, ASSIGNDIV,
		EQUAL, NEQUAL,
		LESS, GREATER, LESSEQ, GREATEREQ,
		INCREMENT, DECREMENT, 
		NOT, AND, OR, EXPONENT, MODULO, DOLLAR, HASH, DEREF, BACKTICK,
		// keywords
		RETURN, BREAK, CONTINUE,
		IF, ELSE, FOR, WHILE,
		SINT8, SINT16, SINT32, SINT64,
		UINT8, UINT16, UINT32, UINT64,
		FLOAT32, FLOAT64,
		BOOL,
		CHAR,
		STRING,
		ENUM,
		// literals
		BOOLLITERAL, CHARLITERAL, INTLITERAL, FLOATLITERAL, DOUBLELITERAL, STRINGLITERAL
	};

	// pre-defined tokens
#define TRUTH "true"
#define UNTRUTH "false"
	std::unordered_map<std::string, TOKENTYPE> keywordDictionary =
	{
		{"return", RETURN}, {"break", BREAK}, {"continue", CONTINUE},
		{"if", IF}, {"else", ELSE}, {"for", FOR}, {"while", WHILE},
		{"sint8", SINT8}, {"sint16", SINT16}, {"sint32", SINT32}, {"sint64", SINT64},
		{"uint8", UINT8}, {"uint16", UINT16}, {"uint32", UINT32}, {"uint64", UINT64},
		{"float32", FLOAT32}, {"float64", FLOAT64},
		{"bool", BOOL},
		{"char", CHAR},
		{"string", STRING},
		{"enum", ENUM}
	};

	std::unordered_map<std::string, TOKENTYPE> multicharDictionary =
	{
		// demarcations
		{"(", LPAR}, {")", RPAR}, {"[", LBRACKET}, {"]", RBRACKET}, {"{", LBRACE}, {"}", RBRACE},
		// punctuation
		{",", COMMA}, {".", DOT}, {";", SEMICOLON}, {"\"", QUOTE}, {"\"", DQUOTE}, {"!", EOL}, {"?", QMARK}, {"\\", ESCAPE},
		// operators
		{"&", AND}, {"|", OR}, {"^", EXPONENT}, {"~", NOT}, {"%", MODULO}, {"$", DOLLAR}, {"#", HASH}, {"@", DEREF}, {"`", BACKTICK}, {"=", EQUAL},
		{":", COLON}, {"+", PLUS}, {"-", MINUS}, {"*", TIMES}, {"/", DIVIDE}, {">", GREATEREQ}, {"<", LESSEQ},
		{":=", ASSIGN}, {"+=", ASSIGNADD}, {"-=", ASSIGNSUB}, {"*=", ASSIGNMUL}, {"/=", ASSIGNDIV},
		{">=", GREATEREQ}, {"<=", LESSEQ}, {"~=", NEQUAL}, 
		{"++", INCREMENT}, {"--", DECREMENT}
	};

	struct jeffToken
	{
		TOKENTYPE type = ILLEGAL;
		std::string lexeme;
	};

	jeffLexer();
	~jeffLexer();

	std::vector<jeffToken> lexify(std::string inputText);

	bool getMultiSymToken(std::string inputText, int& readIndex, jeffLexer::jeffToken& curToken);
	bool getStringToken(std::string inputText, int& readIndex, jeffToken& curToken);

	bool handleCharStringLiteral(std::string inputText, int& readIndex, jeffToken& curToken);
	bool handleNumberLiteral(std::string inputText, int& readIndex, jeffToken& curToken);
	bool handleIdentifier(std::string inputText, int& readIndex, jeffToken& curToken);
};

