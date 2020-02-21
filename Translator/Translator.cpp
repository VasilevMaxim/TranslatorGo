#include <iostream>
#include "TokenBreaking.h"
#include "Parser.h"

#include <fstream>
#include <string>

int main()
{
	std::string rezult;
	std::string line;
	std::ifstream in("E:\\github\\Translator\\Translator\\Translator\\programGo.go"); 

	while (std::getline(in, line))
	{
		rezult += line + '\n';
	}

	TokenBreaking tb(rezult);
	in.close();

	tb.ShowTokens();

	Parser parser(*tb.GetTokens());
	parser.ShowTree(parser.head,0);
	
}