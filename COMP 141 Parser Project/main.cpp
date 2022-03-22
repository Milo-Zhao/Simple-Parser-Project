/*
Programmer: Fangyuan Zhao
			Group 26
Course:     COMP 141
Phase:      2.1
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <regex>
#include <string>
#include "Token.h"
#include "Scanner.h"
#include "Node.h"
#include "AST.h"
using namespace std;

int main(int argc, char** argv)
{
	inputFile.open(argv[1]);
	outputFile.open(argv[2]);
	//fstream setup
	if (!inputFile.is_open() || !outputFile.is_open())
	{
		cerr << "Unable to open file." << endl;
		return 0;
	}
	//begin analyzing and output
	int linesIndex = 0;
	int* linesIndexPtr = &linesIndex;
	string* lines = splitByLine(linesIndexPtr);
	vector<Token> tokens;
	Node* root;
	for (int i = 0; i < linesIndex; i++)
	{
		outputFile << "Parsing..." << endl;
		outputFile << "Line: " << lines[i] << endl;
		tokens = Tokenizer(lines[i], linesIndexPtr);
		outputFile << "AST: " << endl << endl;
		root = parse(tokens);
		printAST(root, 0);
	}
	//finishing
	cout << "Program terminated." << endl;
	inputFile.close();
	outputFile.close();
	return 0;
}