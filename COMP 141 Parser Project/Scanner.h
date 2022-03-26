#pragma once
#include <vector>
using namespace std;

const int ARRAY_MAX = 20;
ifstream inputFile;
ofstream outputFile;
regex IDENTIFIER("([a-z]|[A-Z])([a-z]|[A-Z]|[0-9])*");
regex NUMBER("[0-9]+");
regex SYMBOL("[\\+ | \\- | \\* | \\/ | \\( | \\) | \\:= | \\;]");
regex KEYWORD("if|then|else|endif|while|do|endwhile|skip");

string returnType(string s)
{
	if (regex_match(s, KEYWORD))
	{

		return "KEYWORD";
	}
	else if (regex_match(s, IDENTIFIER))
	{
		return "IDENTIFIER";
	}
	else if (regex_match(s, NUMBER))
	{
		return "NUMBER";
	}
	else if (!s.compare(":="))
	{
		return "SYMBOL";
	}
	else if (regex_match(s, SYMBOL))
	{
		return "SYMBOL";
	}
	else
	{
		char temp = s[0];
		if (s.size() == 1 && temp == '-')
		{
			return "SYMBOL";
		}
		return "ERROR";
	}
}

void printToken(Token token)
{
	outputFile << left << setfill(' ') << setw(8) << token.getValue() << ": ";
	outputFile << left << setfill(' ') << setw(8) << token.getType() << endl;
}

string* splitByLine(int* linesIndex)
{
	string* lines = new string[ARRAY_MAX];
	while (!(inputFile.peek() == EOF))
	{
		getline(inputFile, lines[*linesIndex]);
		*linesIndex += 1;
	}
	return lines;
}

vector<Token> Tokenizer(string line, int* linesIndex)
{
	int checkMatchResult;
	int rightIndex = 1;
	int stringLengthChecked = 0;
	int stringLengthToCheck;
	bool ifBreak = 0;
	vector<Token> tokens;
	Token tempToken;
	string toCheck;
	string tempStr;
	istringstream is(line);
	while (!is.eof())
	{
		is >> toCheck;
		//cout << toCheck << endl;
		stringLengthChecked = 0;
		stringLengthToCheck = toCheck.length();
		while (stringLengthToCheck != stringLengthChecked)
		{
			tempStr = toCheck.substr(stringLengthChecked, rightIndex);
			if (returnType(tempStr) == "ERROR")
			{
				if (tempStr.length() == 1)
				{
					outputFile << left << setfill(' ') << setw(8) << "ERROR READING: \"" << tempStr << "\"" << endl;
					stringLengthChecked = 0;
					rightIndex = 1;
					ifBreak = 1;
					break;
				}
				else
				{
					rightIndex -= 1;
					tempStr = toCheck.substr(stringLengthChecked, rightIndex);
					stringLengthChecked += tempStr.length();
					tempToken.setType(returnType(tempStr));
					tempToken.setValue(tempStr);
					tokens.push_back(tempToken);
					printToken(tempToken);
					rightIndex = 1;
				}
			}
			else
			{
				if (stringLengthChecked + rightIndex == toCheck.length())
				{
					tempToken.setType(returnType(tempStr));
					tempToken.setValue(tempStr);
					tokens.push_back(tempToken);
					printToken(tempToken);
					stringLengthChecked += rightIndex;
					rightIndex = 1;
				}
				else
				{
					rightIndex++;
				}
			}
		}
		if (ifBreak == 1)
		{
			break;
		}
	}
	return tokens;
}