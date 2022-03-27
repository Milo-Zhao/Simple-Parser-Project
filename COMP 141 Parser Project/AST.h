#pragma once
#include "Token.h"
using namespace std;

Node* parseExperssion(vector<Token> tokens);
Node* parseStatement(vector<Token> tokens);
int tokenIndex;

void consume_token()
{
	tokenIndex++;
}

Node* parseLeaf(vector<Token> tokens)
{
	if ((tokens[tokenIndex].getType() == "NUMBER") || (tokens[tokenIndex].getType() == "IDENTIFIER"))
	{
		int curIndex = tokenIndex;
		consume_token();
		Node* leaf = createNewNode(tokens[curIndex], NULL, NULL, NULL);
		return leaf;
	}
	return NULL;
}

Node* parseElement(vector<Token> tokens)
{
	Node* tree = NULL;
	if (!(tokenIndex >= tokens.size()))
	{
		if (tokens[tokenIndex].getValue() == "(")
		{
			consume_token();
			tree = parseExperssion(tokens);
			if (!(tokenIndex >= tokens.size()) && tokens[tokenIndex].getValue() == ")")
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
	if (!(tokenIndex >= tokens.size()) && (tokens[tokenIndex].getValue() == "*"))
	{
		int curIndex = tokenIndex;
		consume_token();
		tree = createNewNode(tokens[curIndex], tree, NULL, parseElement(tokens));
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
	if (!(tokenIndex >= tokens.size()) && (tokens[tokenIndex].getValue() == "/"))
	{
		int curIndex = tokenIndex;
		consume_token();
		tree = createNewNode(tokens[curIndex], tree, NULL, parsePiece(tokens));
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
	if (!(tokenIndex >= tokens.size()) && (tokens[tokenIndex].getValue() == "-"))
	{
		int curIndex = tokenIndex;
		consume_token();
		tree = createNewNode(tokens[curIndex], tree, NULL, parseFactor(tokens));
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
	if (!(tokenIndex >= tokens.size()) && (tokens[tokenIndex].getValue() == "+"))
	{
		int curIndex = tokenIndex;
		consume_token();
		tree = createNewNode(tokens[curIndex], tree, NULL, parseTerm(tokens));
	}
	return tree;
}

Node* parseWhile(vector<Token> tokens)
{
	Node* tree = NULL;
	int curIndex = tokenIndex;
	consume_token();
	Node* left_node = parseExperssion(tokens);
	if (left_node == NULL)
	{
		return NULL;
	}
	if (!(tokenIndex >= tokens.size()) && (tokens[tokenIndex].getValue() == "do"))
	{
		consume_token();
		Node* right_node = parseStatement(tokens);
		if (!(tokenIndex >= tokens.size()) && (tokens[tokenIndex].getValue() == "endwhile"))
		{
			consume_token();
			tree = createNewNode(tokens[curIndex], left_node, NULL, right_node);
			return tree;
		}
	}
	return tree;
}

Node* parseIf(vector<Token> tokens)
{
	Node* tree = NULL;
	int curIndex = tokenIndex;
	consume_token();
	Node* left_node = parseExperssion(tokens);
	if (left_node == NULL)
	{
		return NULL;
	}
	if (!(tokenIndex >= tokens.size()) && (tokens[tokenIndex].getValue() == "then"))
	{
		consume_token();
		Node* middle_node = parseStatement(tokens);
		if (!(tokenIndex >= tokens.size()) && (tokens[tokenIndex].getValue() == "else"))
		{
			consume_token();
			Node* right_node = parseStatement(tokens);
			if (!(tokenIndex >= tokens.size()) && (tokens[tokenIndex].getValue() == "endif"))
			{
				consume_token();
				tree = createNewNode(tokens[curIndex], left_node, middle_node, right_node);
				return tree;
			}
		}
	}
	return tree;
}

Node* parseAssignment(vector<Token> tokens)
{
	Node* tree = parseLeaf(tokens);
	if (tree == NULL)
	{
		return NULL;
	}
	if (!(tokenIndex >= tokens.size()) && (tokens[tokenIndex].getValue() == ":="))
	{
		int curIndex = tokenIndex;
		consume_token();
		tree = createNewNode(tokens[curIndex], tree, NULL, parseExperssion(tokens));
		return tree;
	}
	return tree;
}

Node* parseBase(vector<Token> tokens)
{
	Node* tree = NULL;
	if (!(tokenIndex >= tokens.size()))
	{
		if (tokens[tokenIndex].getType() == "IDENTIFIER")
		{
			return parseAssignment(tokens);
		}
		else if (tokens[tokenIndex].getValue() == "if")
		{
			return parseIf(tokens);
		}
		else if (tokens[tokenIndex].getValue() == "while")
		{
			return parseWhile(tokens);
		}
		else if (tokens[tokenIndex].getValue() == "skip")
		{
			int curIndex = tokenIndex;
			consume_token();
			tree = createNewNode(tokens[curIndex], NULL, NULL, NULL);
			return tree;
		}
	}
	return tree;
}

Node* parseStatement(vector<Token> tokens)
{
	Node* tree = parseBase(tokens);
	if (tree == NULL)
	{
		return NULL;
	}
	while (!(tokenIndex >= tokens.size()) && (tokens[tokenIndex].getValue() == ";"))
	{
		int curIndex = tokenIndex;
		consume_token();
		tree = createNewNode(tokens[curIndex], tree, NULL, parseBase(tokens));
	}
	return tree;
}

Node* parse(vector<Token> tokens)
{
	tokenIndex = 0;
	Node* root = parseStatement(tokens);
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
		printAST(root->middle, height + 1);
		printAST(root->right, height + 1);
	}
}