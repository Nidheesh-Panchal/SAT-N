#include "tseitinTransformer.h"

TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot{root} {}

//assign id if not already assigned and return the id of the root
unsigned int TseitinTransformer::checkVarNum(TreeNode *root)
{
	if (root->getType() == "var")
	{
		if (varIdTable.find(root->getContent()) == varIdTable.end())
		{
			// cout << "logs checkVarNum: setting varId: " << varIdCounter << " to variable: " << root->getContent() << endl;
			varIdTable[root->getContent()] = varIdCounter++;
		}
		return varIdTable[root->getContent()];
	}
	if(root->getVarNum() == 0)
	{
		root->setVarNum(varIdCounter++);
	}
	return root->getVarNum();
}

int TseitinTransformer::transSubformula(TreeNode* root) {
	// your code starts here
	if(root == NULL)
	{
		return 0;
	}
	string rootType = root->getType();
	if (rootType == "var")
	{
		checkVarNum(root);
	}
	else if(rootType == "op" && root->getContent() == "-")
	{
		int curId = checkVarNum(root);

		TreeNode *leftChild = root->getLeftChild();
		int leftId = checkVarNum(leftChild);

		addNegEq(curId, leftId);
		
		transSubformula(leftChild);
	}
	else if (rootType == "op")
	{
		int curId = checkVarNum(root);

		TreeNode *leftChild = root->getLeftChild();
		int leftId = checkVarNum(leftChild);

		TreeNode *rightChild = root->getRightChild();
		int rightId = checkVarNum(rightChild);

		if (root->getContent() == "*")
		{
			addAndEq(curId, leftId, rightId);
		}

		else if (root->getContent() == "+")
		{
			addOrEq(curId, leftId, rightId);
		}

		transSubformula(leftChild);
		transSubformula(rightChild);
	}
	return 0;
}

void TseitinTransformer::addNegEq(int curID, int childID) {
	// your code starts here
	vector<int> t1;
	t1.push_back(-curID);
	t1.push_back(-childID);

	vector<int> t2;
	t2.push_back(curID);
	t2.push_back(childID);

	cnf.push_back(t1);
	cnf.push_back(t2);
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
	// your code starts here
	vector<int> t1;
	t1.push_back(curID);
	t1.push_back(-leftID);

	vector<int> t2;
	t2.push_back(curID);
	t2.push_back(-rightID);

	vector<int> t3;
	t3.push_back(-curID);
	t3.push_back(leftID);
	t3.push_back(rightID);

	cnf.push_back(t1);
	cnf.push_back(t2);
	cnf.push_back(t3);
}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
	// your code starts here
	vector<int> t1;
	t1.push_back(-curID);
	t1.push_back(leftID);

	vector<int> t2;
	t2.push_back(-curID);
	t2.push_back(rightID);

	vector<int> t3;
	t3.push_back(curID);
	t3.push_back(-leftID);
	t3.push_back(-rightID);

	cnf.push_back(t1);
	cnf.push_back(t2);
	cnf.push_back(t3);
}

std::vector<std::vector<int>> TseitinTransformer::transform() {
	// your code starts here
	vector<int> temp;
	temp.push_back(1);
	cnf.push_back(temp);
	transSubformula(formulaRoot);
	return cnf;
}

std::string TseitinTransformer::cnfString(TreeNode *root) const {
	std::string result = "Failed";
	// your code starts here
	result = "Success";
	return result;
}

unsigned int TseitinTransformer::getVarNum() const {
	// your code starts here
	return varIdCounter - 1;
}
