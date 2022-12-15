#include "treeNode.h"

TreeNode::TreeNode(std::string cntt): content {cntt} {}

std::string TreeNode::getContent() const {
	// your code starts here
	return this->content;
}

void TreeNode::setVarNum(unsigned int i)
{
	this->varNum = i;
}

unsigned int TreeNode::getVarNum() const
{
	// your code starts here
	return this->varNum;
}

TreeNode *TreeNode::getLeftChild()  {
	// your code starts here
	return this->leftChild;
}
TreeNode *TreeNode::getRightChild()  {
	// your code starts here
	return this->rightChild;
}

void TreeNode::updateLeftChild(TreeNode *lChild) {
	// your code starts here
	this->leftChild = lChild;
}

void TreeNode::updateRightChild(TreeNode *rChild)
{
	// your code starts here
	this->rightChild = rChild;
}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild) {
	// your code starts here
	this->leftChild = lChild;
	this->rightChild = rChild;
}

void TreeNode::postOrder(TreeNode *root)
{
	if(root==NULL)
	{
		return;
	}
	postOrder(root->getLeftChild());
	postOrder(root->getRightChild());
	std::cout << root->content;
	std::cout << root->varNum;
}

void TreeNode::inOrder(TreeNode *root)
{
	if (root == NULL)
	{
		return;
	}
	inOrder(root->getLeftChild());
	std::cout << root->content;
	std::cout << root->varNum << " ";
	inOrder(root->getRightChild());
}

OperatorNode::OperatorNode(std::string cntt): TreeNode{cntt} {}

ConstantNode::ConstantNode(std::string cntt): TreeNode{cntt} {}

VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}

string OperatorNode::getType() {
	return "op";
}

string ConstantNode::getType() {
	return "const";
}

string VariableNode::getType() {
	return "var";
}

TreeNode::~TreeNode() {
	// your code starts here
	delete this;
}
