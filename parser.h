#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include <iostream>

#include "tokenizer.h"
#include "treeNode.h"

using namespace std;

class TreeNode;
class Tokenizer;

// Parser for the Boolean Formula
class FormulaParser {
		Tokenizer *tknzr;
		// map<string, bool> assignments;
		TreeNode *parseFormula();  // parse non-terminal Formula in the grammar
		TreeNode *parseConjTerm(); // parse non-terminal ConjTerm in the grammar
		TreeNode *parseTerm(); // parse non-terminal Term in the grammar
		TreeNode *c1();
		TreeNode *t1();

	public:
		FormulaParser(std::string ln);
		// TreeNode *getTreeRoot(map<string, bool>); 
		TreeNode* getTreeRoot(); // parse the Boolean formula and return the root node of the formula syntax tree
		~FormulaParser();
};

#endif
