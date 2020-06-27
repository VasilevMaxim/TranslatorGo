#include <iostream>
#include <fstream>
#include <vector>
#include "TokenBreaking.h"
#include "Parser.h"
#include "AbstractSyntaxTree.h"
#include "Preprocessing.h"
#include "RecursiveTraversal.h"
#include "Errors/LocalizationSettings.h"
#include "Errors/ErrorSettings.h"
#include <Windows.h>

using std::ifstream;
using std::getline;
using std::vector;

void OnCompilation(string pathFile);
string GetAllTextInFile(string pathFile);

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	LocalizationSettings::SetLanguage(Language::Russian);
	ErrorSettings::AddTableLocalization("L", new TableLocalization("ErrorsLexer.csv"));
	ErrorSettings::AddTableLocalization("P", new TableLocalization("ErrorsParser.csv"));
	ErrorSettings::AddTableLocalization("AST", new TableLocalization("ErrorsAST.csv"));

	OnCompilation("progGo.go");

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