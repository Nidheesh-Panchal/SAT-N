#ifndef SOLVER_H
#define SOLVER_H

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <queue>

#include "SolverTypes.h"

using namespace std;


bool dpll(vector<vector<Lit>> clauses, map<long long int, bool> assignment);

// Parser for the Boolean Formula
class Solver
{
	vector<vector<Lit>> clauses;
	map<long long int, bool> assignment;

	long long int chooseVar(vector<vector<Lit>> clauses)
	{
		int i, j;
		i = 0;
		while (i < clauses.size())
		{
			if (clauses[i].size() == 1)
			{
				return clauses[i][0].litno;
			}
			i++;
		}
		return -1;
	}

public:

	Lit mkLit(long long int n, bool sign = false)
	{
		Lit t(n, sign);
		return t;
	}

	void addClause(vector<Lit> v)
	{
		clauses.push_back(v);
	}

	void print()
	{
		long long int i, j;
		i = 0;
		// cout << "logs class print: clauses size: " << clauses.size() << endl;
		while (i < clauses.size())
		{
			j = 0;
			while (j < clauses[i].size())
			{
				if(!clauses[i][j].sign)
				{
					cout << "-";
				}
				cout << clauses[i][j].litno << " ";
				j++;
			}
			cout << endl;
			i++;
		}
	}

	bool solve()
	{
		// cout << "logs solve: solver called" << endl;
		long long int s = chooseVar(this->clauses);
		if(s < 0)
		{
			return false;
		}
		// cout << "logs choose: called choose var, chose lit: " << s << endl;
		assignment[s] = true;
		// cout << "logs choose: assigning true to the first unit literal" << endl;
		return dpll(this->clauses, this->assignment);
	}
};

void print(vector<vector<Lit>> clauses)
{
	long long int i, j;
	i = 0;
	// cout << "logs print: clauses size: " << clauses.size() << endl;
	while (i < clauses.size())
	{
		j = 0;
		cout << i << " : ";
		while (j < clauses[i].size())
		{
			if (!clauses[i][j].sign)
			{
				cout << "-";
			}
			cout << clauses[i][j].litno << " ";
			j++;
		}
		cout << endl;
		i++;
	}
}

long long int chooseVar(vector<vector<Lit>> clauses, map<long long int, bool> assignment)
{
	int i, j;
	map<long long int, long long int> v;
	long long int max = 0;
	long long int cnt = 0;
	i = 0;
	while (i < clauses.size())
	{
		j = 0;
		while (j < clauses[i].size())
		{
			if (assignment.find(clauses[i][j].litno) == assignment.end())
			{
				v[clauses[i][j].litno]++;
				if (v[clauses[i][j].litno] > cnt)
				{
					cnt = v[clauses[i][j].litno];
					max = clauses[i][j].litno;
				}
			}
			j++;
		}
		i++;
	}
	return max;
}

vector<vector<Lit>> bcp(vector<vector<Lit>> clauses, map<long long int, bool> assignment)
{
	long long int i, j;
	bool unitPresent = true;

	bool emptyClauses = false;
	long long int eraseClause = -1;
	long long int eraseLit = -1;
	bool popq = false;
	bool unsat = false;

	bool unchanged = true;
	queue<pair<long long int, bool>> q;

	for (map<long long int, bool>::iterator it = assignment.begin(); it != assignment.end(); it++)
	{
		q.push(make_pair(it->first, it->second));
	}

	do
	{
		// cout << "logs bcp: iterating in do while loop for unchanged" << endl;
		unchanged = true;
		while (!q.empty())
		{
			long long int litno = q.front().first;
			bool assignedValue = q.front().second;
			// cout << "logs bcp: litno: " << litno << " sign: " << assignedValue << endl;
			eraseClause = -1;
			i = 0;
			while (i < clauses.size())
			{
				eraseLit = -1;
				j = 0;
				// cout << "logs bcp: taking clause: " << i << endl;
				
				while (j < clauses[i].size())
				{
					// if (assignment.find(clauses[i][j].litno) != assignment.end())
					// cout << j << endl;
					if (clauses[i][j].litno == litno)
					{
						// print(clauses);
						if (assignedValue == clauses[i][j].sign)
						{
							// cout << "logs bcp: clause satisfied: " << i << endl;
							eraseClause = i;
							break;
						}
						else
						{
							// cout << "logs bcp: var takes false value, remove var: " << j << endl;
							eraseLit = j;
							break;
						}
					}
					j++;
				}
				if (eraseLit >= 0)
				{
					unchanged = false;
					if(clauses[i].size() == 1)
					{
						//unsat because the assignment is not matching the unit literal
						// cout << "logs bcp: single literal in clause, clause size reduced to 0, erase it: " << i << endl;
						clauses.clear();
						emptyClauses = true;
						unsat = true;
						// cout << "logs bcp: clauses size after dropping: " << clauses.size() << endl;
						// // popq = false;
						// i--;
						break;
					}
					else
					{
						// cout << "logs bcp: erase literal at pos: " << eraseLit << endl;
						clauses[i].erase(clauses[i].begin() + eraseLit);
						// cout << "logs bcp: clause size after erase: " << clauses[i].size() << endl;
					}					
					// exit(0);
				}
				else if (eraseClause >= 0)
				{
					if(clauses.size() == 1)
					{
						// cout << "logs bcp: only clause left" << endl;
						clauses.clear();
						// cout << "logs bcp: clauses size after dropping: " << clauses.size() << endl;
						emptyClauses = true;
						// popq = false;
						break;
					}
					else
					{
						unchanged = false;
						// cout << "logs bcp: clauses size before dropping: " << clauses.size() << endl;
						clauses.erase(clauses.begin() + eraseClause);
						// cout << "logs bcp: clauses size after dropping: " << clauses.size() << endl;
						// popq = false;
						i--;
						eraseClause = -1;
						// break;
					}
				}
				if (clauses[i].size() == 1 && assignment.find(clauses[i][0].litno) == assignment.end())
				{
					// cout << "logs bcp: clause size is 1 and is unassigned value: " << clauses[i][0].litno << " sign is: " << clauses[i][0].sign << endl;
					unchanged = false;
					assignment[clauses[i][0].litno] = clauses[i][0].sign;
					q.push(make_pair(clauses[i][0].litno, clauses[i][0].sign));
				}
				i++;
			}
			if (emptyClauses)
			{
				unchanged = true;
				break;
			}
			q.pop();
		}
		// cout << "logs bcp: unchanged: " << unchanged << endl;
	} while (!unchanged);

	if (clauses.size() < 1 || unsat)
	{
		clauses.clear();
		vector<Lit> temp;
		temp.push_back(Lit(0, !unsat));
		clauses.push_back(temp);
	}
	return clauses;
}

vector<vector<Lit>> plp(vector<vector<Lit>> clauses, map<long long int, bool> assignment)
{
	long long int i, j;
	map<long long int, pair<bool, bool>> unchanged;
	long long int eraseClause;
	bool emptyClauses = false;

	i = 0;
	while (i < clauses.size())
	{
		j = 0;
		while (j < clauses[i].size())
		{
			if (unchanged.find(clauses[i][j].litno) == unchanged.end())
			{
				unchanged[clauses[i][j].litno] = make_pair(clauses[i][j].sign, true);
			}
			else if (unchanged[clauses[i][j].litno].first != clauses[i][j].sign)
			{
				unchanged[clauses[i][j].litno].second = false;
			}
			j++;
		}
		i++;
	}

	for (map<long long int, pair<bool, bool>>::iterator it = unchanged.begin(); it != unchanged.end(); ++it)
	{
		if (!(it->second.second))
		{
			continue;
		}
		// cout << "logs plp: unchanged vars: " << it->first << endl;
		bool sign = it->second.first;
		assignment[it->first] = sign;
		i = 0;
		eraseClause = -1;
		while (i < clauses.size())
		{
			j = 0;
			while (clauses[i].size())
			{
				if (clauses[i][j].litno == it->first)
				{
					// cout << "logs plp: matched litno: " << clauses[i][j].litno << endl;
					eraseClause = i;
					break;
				}
				j++;
			}
			if (eraseClause >= 0)
			{
				if(clauses.size() == 1)
				{
					// cout << "logs bcp: only clause left" << endl;
					clauses.clear();
					// cout << "logs bcp: clauses size after dropping: " << clauses.size() << endl;
					emptyClauses = true;
					--it;
					break;
				}
				clauses.erase(clauses.begin() + eraseClause);
				--it;
				break;
			}
			i++;
		}
		if (emptyClauses)
		{
			break;
		}
	}
	if (clauses.size() < 1)
	{
		// cout << "logs plp: clauses became empty, so create a sat literal to end" << endl;
		clauses.clear();
		vector<Lit> temp;
		temp.push_back(Lit(0, true));
		clauses.push_back(temp);
	}
	return clauses;
}

bool dpll(vector<vector<Lit>> clauses, map<long long int, bool> assignment)
{
	// return true;
	// cout << "logs dpll: calling bcp" << endl;
	clauses = bcp(clauses, assignment);
	if (clauses.size() == 1 && clauses[0].size() == 1 && clauses[0][0].litno == 0)
	{
		// cout << "logs dpll: found last clause after bcp" << endl;
		return clauses[0][0].sign;
	}

	// cout << "logs dpll: calling plp" << endl;
	clauses = plp(clauses, assignment);

	if (clauses.size() == 1 && clauses[0].size() == 1 && clauses[0][0].litno == 0)
	{
		// cout << "logs dpll: found last clause after plp" << endl;
		return clauses[0][0].sign;
	}
	// cout << "logs dpll: choosing var assignment" << endl;
	long long int t = chooseVar(clauses, assignment);
	assignment[t] = true;
	if (dpll(clauses, assignment))
	{
		return true;
	}
	assignment[t] = false;
	return dpll(clauses, assignment);
}

#endif
