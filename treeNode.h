#ifndef TNODE_H
#define TNODE_H

#include <string>
#include <map>
#include <iostream>
using namespace std;

// abstract superclass of the syntax tree node
class TreeNode {
		std::string content;
		//give default value of varnum as 0
		unsigned int varNum = 0;
		TreeNode *leftChild = nullptr;
		TreeNode *rightChild = nullptr;
	public:
		TreeNode(std::string cntt);
		TreeNode *getLeftChild();
		TreeNode *getRightChild();
		std::string getContent() const;
		unsigned int getVarNum() const;
		void updateLeftChild(TreeNode *lChild); // for the operator "-", the operand is stored in leftChild
		void updateRightChild(TreeNode *lChild);
		void updateChildren(TreeNode *lChild, TreeNode *rChild);
		void setVarNum(unsigned int i);
		virtual string getType() = 0;
		void postOrder(TreeNode *root);
		void inOrder(TreeNode *root);
		virtual ~TreeNode();
};

// concrete tree node of opertaor type
class OperatorNode : public TreeNode {
	public:
		OperatorNode(std::string cntt);
		string getType();
};

// concrete tree node of constant type
class ConstantNode : public TreeNode {
	public:
		ConstantNode(std::string cntt);
		string getType();
};

// concrete tree node of varibale type
class VariableNode : public TreeNode {
	public:
		VariableNode(std::string cntt);
		string getType();
};

#endif
