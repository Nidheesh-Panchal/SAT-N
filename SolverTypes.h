#ifndef SOLVERTYPES_H
#define SOLVERTYPES_H

#include <iostream>
#include <vector>

class Lit
{
	public:
		long long int litno;
		bool sign;

		Lit()
		{}

		Lit(long long int n, bool sign_in=false)
		{
			if(n < 0)
			{
				litno = -1 * n;
				sign = false;
			}
			else if(n==0)
			{
				litno = n;
				sign = sign_in;
			}
			else
			{
				litno = n;
				sign = true;
			}
		}
};

#endif