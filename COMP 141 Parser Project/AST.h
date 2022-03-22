#pragma once
#include "Token.h"
using namespace std;

Node* parseExperssion(vector<Token> tokens);
int index;

void consume_token()
{
	index++;
}

Node* parseLeaf(vector<Token> tokens)
{
	if ((tokens[index].getType() == "NUMBER") || (tokens[index].getType() == "IDENTIFIER"))
	{
		int curIndex = index;
		consume_token();
		Node* leaf = createNewNode(tokens[curIndex], NULL, NULL);
		return leaf;
	}
	return NULL;
}

Node* parseElement(vector<Token> tokens)
{
	Node* tree = NULL;
	if (!(index >= tokens.size()))
	{
		if (tokens[index].getValue() == "(")
		{
			consume_token();
			tree = parseExperssion(tokens);
			if (!(index >= tokens.size()) && tokens[index].getValue() == ")")
			{
				consume_token();
				return tree;
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			return parseLeaf(tokens);
		}
	}
	return tree;
}

Node* parsePiece(vector<Token> tokens)
{
	Node* tree = parseElement(tokens);
	if (tree == NULL)
	{
		return NULL;
	}
	if (!(index >= tokens.size()) && (tokens[index].getValue() == "*"))
	{
		int curIndex = index;
		consume_token();
		tree = createNewNode(tokens[curIndex], tree, parseElement(tokens));
	}
	return tree;
}

Node* parseFactor(vector<Token> tokens)
{
	Node* tree = parsePiece(tokens);
	if (tree == NULL)
	{
		return NULL;
	}
	if (!(index >= tokens.size()) && (tokens[index].getValue() == "/"))
	{
		int curIndex = index;
		consume_token();
		tree = createNewNode(tokens[curIndex], tree, parsePiece(tokens));
	}
	return tree;
}

Node* parseTerm(vector<Token> tokens)
{
	Node* tree = parseFactor(tokens);
	if (tree == NULL)
	{
		return NULL;
	}
	if (!(index >= tokens.size()) && (tokens[index].getValue() == "-"))
	{
		int curIndex = index;
		consume_token();
		tree = createNewNode(tokens[curIndex], tree, parseFactor(tokens));
	}
	return tree;
}

Node* parseExperssion(vector<Token> tokens)
{
	Node* tree = parseTerm(tokens);
	if (tree == NULL)
	{
		return NULL;
	}
	if (!(index >= tokens.size()) && (tokens[index].getValue() == "+"))
	{
		int curIndex = index;
		consume_token();
		tree = createNewNode(tokens[curIndex], tree, parseTerm(tokens));
	}
	return tree;
}

Node* parse(vector<Token> tokens)
{
	index = 0;
	Node* root = parseExperssion(tokens);
	return root;
}

void printAST(Node* root, int height)
{
	if (root != NULL)
	{
		for (int i = 0; i < height; i++)
		{
			outputFile << "    ";
		}
		outputFile << printNode(root) << endl;
		printAST(root->left, height + 1);
		printAST(root->right, height + 1);
	}
}