#include "satSolver.h"
#include "SolverTypes.h"
#include "Solver.h"
using namespace std;

bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int>> &cnf) {
	// your code starts here
	int i, j, n, cnt = 1;
	n = cnf.size();

	// cout << "logs satCallingMiniSat: creating solver pointer" << endl;

	Solver solver;

	// cout << "logs satCallingMiniSat: creating literals vector" << endl;

	for (i = 0; i < n; i++)
	{
		vector<Lit> v;
		for (j = 0; j < cnf[i].size(); j++)
		{
			Lit l(cnf[i][j]);
			/* cout << "cnf[i][j]: " << cnf[i][j] << "\t";
			cout << "literal" << l << endl; */
			v.push_back(l);
		}
		solver.addClause(v);
	}

	// cout << "logs satCallingMiniSat: creating solver clauses" << endl;
	// solver.print();

	bool res = solver.solve();
	return res;
}
