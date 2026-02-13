#pragma once

#include "jeffLexer.h"
#include <map>

class jeffParser
{
public:
	enum NonTerminalType
	{
		PROGRAM, FUNCTION, STATEMENT, EXPRESSION, DECLARATION, ASSIGNMENT, 
		TYPE, INTEGER, SIGNED_INTEGER, UNSIGNED_INTEGER, FLOAT, LITERAL, 
		OPERATOR, BIN_OPERATOR, ASSIGNER
	};

	struct jeffSymbol
	{
		bool isTerminal;
		jeffSymbol(bool term) : isTerminal(term) {}
	};

	struct jeffTerminal : jeffSymbol
	{
		jeffLexer::jeffToken token;
		jeffTerminal(jeffLexer::jeffToken jToken) : jeffSymbol(true), token(jToken) {}
	};

	struct jeffNonTerminal : jeffSymbol
	{
		NonTerminalType groupingType;
		std::vector<jeffSymbol> children;
		jeffNonTerminal(NonTerminalType type) : jeffSymbol(false), groupingType(type) {}
	};

	// allows rules with alternatives, e.g. "A -> B | C D" (Backus-Naur form)
	struct jeffRule
	{
		NonTerminalType leftSide;

		// each rule has a list of valid replacements
		std::vector<jeffSymbol> rightSide;
	};

	// list of rules (JSON?)
	//std::vector<jeffRule> grammar =
	//{
	//	// statements
	//	{ STATEMENT, {{DECLARATION}} }, { STATEMENT, {{ASSIGNMENT}} },
	//	{ DECLARATION, {{TYPE}, {jeffLexer::ID}, {jeffLexer::EOL}} }, { DECLARATION, {{TYPE}, {jeffLexer::ID}, {ASSIGNER}, {EXPRESSION}, {jeffLexer::EOL}} },
	//	{ ASSIGNMENT, {{jeffLexer::ID}, {ASSIGNER}, {EXPRESSION}, {jeffLexer::EOL}} },
	//	// assignment variations
	//	{ ASSIGNER, {{jeffLexer::ASSIGN}}}, { ASSIGNER, {{jeffLexer::ASSIGNADD}}},{ ASSIGNER, {{jeffLexer::ASSIGNSUB}}},{ ASSIGNER, {{jeffLexer::ASSIGNMUL}}}, { ASSIGNER, {{jeffLexer::ASSIGNDIV}}},
	//	// built-in types
	//	{ TYPE, {{jeffLexer::BOOL}} }, { TYPE, {{jeffLexer::CHAR}} }, { TYPE, {{jeffLexer::STRING}} }, { TYPE, {{INTEGER}} }, { TYPE, {{FLOAT}} },
	//	{ INTEGER, {{SIGNED_INTEGER}} }, { INTEGER, {{UNSIGNED_INTEGER}} },
	//	{ SIGNED_INTEGER, {{jeffLexer::SINT8}} }, { SIGNED_INTEGER, {{jeffLexer::SINT16}} }, { SIGNED_INTEGER, {{jeffLexer::SINT32}} }, { SIGNED_INTEGER, {{jeffLexer::SINT64}} },
	//	{ UNSIGNED_INTEGER, {{jeffLexer::UINT8}} }, { UNSIGNED_INTEGER, {{jeffLexer::UINT16}} }, { UNSIGNED_INTEGER, {{jeffLexer::UINT32}} }, { UNSIGNED_INTEGER, {{jeffLexer::UINT64}} },
	//	{ FLOAT, {{jeffLexer::FLOAT32}}}, { FLOAT, {{jeffLexer::FLOAT64}}},
	//	// expressions
	//	{ EXPRESSION, {{OPERATOR}, {EXPRESSION}} }, { EXPRESSION, {{EXPRESSION}, {BIN_OPERATOR}, {EXPRESSION}} }, { EXPRESSION, {{LITERAL}} }, { EXPRESSION, {{jeffLexer::ID}} },
	//	// literals

	//	// unary operators
	//	{ OPERATOR, {{jeffLexer::NOT}} }, { OPERATOR, {{jeffLexer::DECREMENT}} }, { OPERATOR, {{jeffLexer::INCREMENT}} },
	//	// binary operators
	//	{ BIN_OPERATOR, {{jeffLexer::AND}} }, { BIN_OPERATOR, {{jeffLexer::OR}} }, { BIN_OPERATOR, {{jeffLexer::EXPONENT}} }, { BIN_OPERATOR, {{jeffLexer::PLUS}} }, { BIN_OPERATOR, {{jeffLexer::MINUS}} },
	//	{ BIN_OPERATOR, {{jeffLexer::TIMES}} }, { BIN_OPERATOR, {{jeffLexer::DIVIDE}} }, { BIN_OPERATOR, {{jeffLexer::MODULO}} }, { BIN_OPERATOR, {{jeffLexer::EQUAL}} }, { BIN_OPERATOR, {{jeffLexer::NEQUAL}} }, 
	//	{ BIN_OPERATOR, {{jeffLexer::GREATER}} }, { BIN_OPERATOR, {{jeffLexer::GREATEREQ}} }, { BIN_OPERATOR, {{jeffLexer::LESS}} }, { BIN_OPERATOR, {{jeffLexer::LESSEQ}} },
	//};

	jeffParser();
	~jeffParser();

};

