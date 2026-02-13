
#include <iostream>
#include "jeffIO.h"
#include "jeffParser.h"

int main(int argc, char* argv[])
{
    jeffIO jefio;
    std::string test = jefio.readFile("test.txt");

    jeffLexer lex;
    std::vector<jeffLexer::jeffToken> tokens = lex.lexify(test);

    std::cout << test;
}
