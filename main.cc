#include <iostream>
#include <string>
#include "parser.h"
#include "tseitinTransformer.h"
#include "satSolver.h"

using namespace std;

void lclean(string &line)
{
	string cleanLine;

	int i;

	// remove space from prefix
	i = 0;
	while (i < line.length())
	{
		if (line[i] != '\n' && line[i] != '\r' && line[i] != '\t' && line[i] != ' ')
		{
			break;
		}
		i++;
	}

	cleanLine = line.substr(i, line.length() - i);
	line = cleanLine;
}

void rclean(string &line)
{
	string cleanLine;

	int i;

	// remove space from suffix
	i = line.length() - 1;
	// cout << "\nlast index" << i;
	while (i >= 0)
	{
		// cout << line[i] << endl;
		if (line[i] != '\n' && line[i] != '\r' && line[i] != '\t' && line[i] != ' ')
		{
			break;
		}
		i--;
	}
	// cout << "\nlast index w/o space" << i;
	cleanLine = line.substr(0, i + 1);
	// cout << cleanLine;
	line = cleanLine;
}

void clean(string &line)
{
	// line.erase(line.find_last_not_of(" \n\r\t")+1);

	lclean(line);
	rclean(line);

	return;
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
	std::string line;
	int cnt = 1;
	while (getline(cin, line)) // continuously asking for new inputs from standard input
	{
		// std::string line; // store each input line
		// your code starts here
		clean(line);

		try
		{
			// cout << "logs main: formula : " << cnt++ << endl;
			FormulaParser *formulaparser = new FormulaParser(line);
			// TreeNode *root = formulaparser->getTreeRoot(assignments);
			TreeNode *root = formulaparser->getTreeRoot();

			TseitinTransformer ts(root);
			vector<vector<int>> cnf = ts.transform();

			// debug code
			/* root->inOrder(root);
			cout << endl;

			for (int i = 0; i < cnf.size();i++)
			{
				for (int j = 0; j < cnf[i].size();j++)
				{
					cout << cnf[i][j] << " ";
				}
				cout << endl;
			} */

			// cout << "logs main: total number of variables : " << ts.getVarNum() << endl;

			bool res = satCallingMiniSat(ts.getVarNum(), cnf);
			if(!res)
			{
				cout << "un";
			}
			cout << "sat" << endl;
		}
		catch (int e)
		{
			cout << "Error: ";
			switch (e)
			{
			case 0:
				// any input that is not in the CFL
				cout << "invalid input";
				break;
			case 1:
				// at least one variable is not assigned truth value
				cout << "incomplete assignment";
				break;
			case 2:
				// one variable is assigned contradicting truth values
				cout << "contradicting assignment";
				break;
			}
			cout << endl;
		}
	}
}
