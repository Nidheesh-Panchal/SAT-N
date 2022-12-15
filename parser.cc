#include "parser.h"

FormulaParser::FormulaParser(std::string ln): tknzr {new Tokenizer{ln}} {}

TreeNode *FormulaParser::parseFormula()
{
	// your code starts here
	// cout << "logs parseFormula: calling parseConjTerm for left child" << endl;
	TreeNode *lChild = parseConjTerm();
	// cout << "logs parseFormula: calling c1 for root" << endl;
	TreeNode *root = c1();
	if(root==NULL)
	{
		// cout << "logs parseFormula: chose lambda for c1, returning just parseConjTerm" << endl;
		return lChild;
	}
	root->updateLeftChild(lChild);
	return root;
}

TreeNode *FormulaParser::parseConjTerm() {
	// your code starts here
	// cout << "logs parseConjTerm: calling parseTerm for left child" << endl;
	TreeNode *lChild = parseTerm();
	// cout << "logs parseConjTerm: calling t1 for root" << endl;
	TreeNode *root = t1();
	if (root == NULL)
	{
		// cout << "logs parseConjTerm: chose lambda for t1, returning just parseTerm" << endl;
		return lChild;
	}
	root->updateLeftChild(lChild);
	return root;
}

TreeNode *FormulaParser::c1()
{
	if (!tknzr->hasToken())
	{
		// cout << "logs c1: no more token in line, choosing lambda" << endl;
		return NULL;
	}
	Token token;
	if (tknzr->unused)
	{
		token = tknzr->getUnUsedToken();
		// cout << "logs c1: get unused token : " << token.content << endl;
	}
	else
	{
		token = tknzr->getToken();
		// cout << "logs c1: got new token : " << token.content << endl;
	}
	if(token.type=="or_op")
	{
		// cout << "logs c1: matched or_op, marking it used" << endl;
		tknzr->unused = false;
		OperatorNode *root = new OperatorNode(token.content);
		// cout << "logs c1: calling parseConjTerm" << endl;
		TreeNode *rChild = parseFormula();
		root->updateRightChild(rChild);
		return root;
	}
	else
	{
		// cout << "logs c1: the token does not match or_op : " << token.content << ", choosing lambda" << endl;
		return NULL;
	}
}

TreeNode *FormulaParser::t1()
{
	if (!tknzr->hasToken())
	{
		// cout << "logs t1: no more token in line, choosing lambda" << endl;
		return NULL;
	}
	Token token;
	if (tknzr->unused)
	{
		token = tknzr->getUnUsedToken();
		// cout << "logs t1: get unused token : " << token.content << endl;
	}
	else
	{
		token = tknzr->getToken();
		// cout << "logs t1: got new token : " << token.content << endl;
	}
	if(token.type=="and_op")
	{
		// cout << "logs t1: matched and_op, marking it used" << endl;
		tknzr->unused = false;
		OperatorNode *root = new OperatorNode(token.content);
		// cout << "logs t1: calling parseConjTerm" << endl;
		TreeNode *rChild = parseConjTerm();
		root->updateRightChild(rChild);
		return root;
	}
	else
	{
		// cout << "logs t1: the token does not match and_op : " << token.content << ", choosing lambda" << endl;
		return NULL;
	}
}

TreeNode *FormulaParser::parseTerm() {
	// your code starts here
	if(!tknzr->hasToken())
	{
		// cout << "logs parseTerm: expected a token, but line is empty now" << endl;
		throw 0;
	}
	Token token;
	if (tknzr->unused)
	{
		token = tknzr->getUnUsedToken();
		// cout << "logs parseTerm: get unused token : " << token.content << endl;
	}
	else
	{
		token = tknzr->getToken();
		// cout << "logs parseTerm: got new token : " << token.content << endl;
	}
	if (token.type != "const" && token.type != "var" && token.type != "para_open" && token.type != "negate_op")
	{
		// cout << "logs parseTerm: unexpected token content : " << token.content << endl;
		throw 0;
	}
	if(token.type=="const")
	{
		// cout << "logs parseTerm: marking token used: " << token.content << endl;
		tknzr->unused = false;
		ConstantNode *root = new ConstantNode(token.content);
		root->updateChildren(NULL, NULL);
		return root;
	}
	if(token.type=="var")
	{
		// cout << "logs parseTerm: marking token used: " << token.content << endl;
		tknzr->unused = false;
		VariableNode *root = new VariableNode(token.content);
		root->updateChildren(NULL, NULL);
		return root;
	}
	if(token.type=="para_open")
	{
		// cout << "logs parseTerm: marking token used: " << token.content << endl;
		tknzr->unused = false;
		// cout << "logs parseTerm: calling parseFormula" << endl;
		TreeNode *root = parseFormula();

		Token paraClose;
		if (tknzr->unused)
		{
			paraClose = tknzr->getUnUsedToken();
			// cout << "logs parseTerm: get unused token : " << paraClose.content << endl;
		}
		else
		{
			paraClose = tknzr->getToken();
			// cout << "logs parseTerm: got new token : " << paraClose.content << endl;
		}
		// cout << "logs parseTerm: getting new token, expecting para_close only : " << paraClose.content << paraClose.type << endl;
		tknzr->unused = false;
		if (paraClose.type != "para_close")
		{
			// cout << "logs parseTerm: expected token para_close, but got: " << paraClose.content;
			throw 0;
		}
		return root;
	}
	else
	{
		// cout << "logs parseTerm: marking token used: " << token.content << endl;
		tknzr->unused = false;
		OperatorNode *root = new OperatorNode(token.content);
		// cout << "logs parseTerm: calling parseTerm" << endl;
		TreeNode *lChild = parseTerm();
		root->updateChildren(lChild, NULL);
		return root;
	}
}

TreeNode* FormulaParser::getTreeRoot() {
	// your code starts here
	TreeNode *root = parseFormula();
	if (tknzr->hasToken() || tknzr->unused)
	{
		// cout << "logs getTreeRoot: There are still more tokens to read" << endl;
		// cout << "logs getTreeRoot: " << tknzr->getToken().content;
		throw 0;
	}
	return root;
}

FormulaParser::~FormulaParser() {
	// your code starts here
	delete this;
}