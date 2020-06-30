#include <iostream>
#include <fstream>
#include <vector>
#include "TokenBreaking.h"
#include "Parser.h"
#include "AbstractSyntaxTree.h"
#include "Preprocessing.h"
#include "RecursiveTraversal.h"
#include "Asm/Asm.h"

#include "Errors/LocalizationSettings.h"
#include "Errors/ErrorSettings.h"
#include <Windows.h>

using std::ifstream;
using std::getline;
using std::vector;

void OnCompilation(string pathFile);
string GetAllTextInFile(string pathFile);


int main(int argc, char* argv[])
{
	SetConsoleOutputCP(CP_UTF8);

	LocalizationSettings::SetLanguage(Language::Russian);

	ErrorSettings::AddTableLocalization("L", new TableLocalization("ErrorsLexer.csv"));
	ErrorSettings::AddTableLocalization("P", new TableLocalization("ErrorsParser.csv"));
	ErrorSettings::AddTableLocalization("AST", new TableLocalization("ErrorsAST.csv"));

	if (argc > 1)
	{
		for(int i = 1; i < argc; i++)
			OnCompilation(argv[i]);
	}
	else
	{
		OnCompilation("progGo.go");
	}


	
	system("pause");
	return 0;
}

void OnCompilation(string pathFile)
{
	string textInFile = GetAllTextInFile(pathFile);
	Preprocessing preprocessing(&textInFile);

	TokenBreaking tokenBreaking(preprocessing.GetText());
	tokenBreaking.ShowTokens();

	Parser parser(tokenBreaking.GetTokens());
	AbstractSyntaxTree tree(parser.GetNodeHead());
	tree.ShowTree();

	RecursiveTraversal recursiveTraversal(parser.GetNodeHead());
	recursiveTraversal.Show();

	tree.ShowTree();

	Asm asmNew(parser.GetNodeHead());
}

string GetAllTextInFile(string pathFile)
{
	string textInFile;
	string tempLineText;
	ifstream in(pathFile);
	while (getline(in, tempLineText))
	{
		textInFile += tempLineText + '\n';
	}
	in.close();
	textInFile.erase(textInFile.end() - 1);
	return textInFile;
}