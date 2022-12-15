#include <iostream>
#include "tokenizer.h"
using namespace std;

Tokenizer::Tokenizer(std::string ln)
{
	// complete the constructor
	line = ln;
	index = 0;
	unused = false;
}

bool Tokenizer::advanceToken()
{
	// your code starts here
	// ignore white spaces in middle for next token
	index++;
	if(index>=line.length())
	{
		return false;
	}

	while (index < line.length() 
	&& (line[index] == '\n' || line[index] == '\r' || line[index] == '\t' || line[index] == ' '))
	{
		index++;
	}

	return true;
}

bool Tokenizer::hasToken() const
{
	// your code starts here
	if (index < line.length())
	{
		return true;
	}
	return false;
}

/*
In case the token is read but did not match the grammar rule, then we need
not read the token and advance the token, it will be reading the next input 
which will not be correct
*/
Token Tokenizer::getUnUsedToken()
{
	return token;
}

// only can be called when hasToken() is true
/*
This function will get the next token by reading the string, if it finds any
error it will throw 0 int excpetion. The token will atuomatically check for the end
of line and advance the token once to the next unread character. 
*/
Token Tokenizer::getToken()
{
	// your code starts there
	if (!hasToken())
	{
		// cout << "logs getToken: expected a token but got none";
		throw 0;
	}
	Token resultToken;

	switch (line[index])
	{
	case '*':
		resultToken.content = "*";
		resultToken.type = "and_op";
		break;
	case '-':
		resultToken.content = "-";
		resultToken.type = "negate_op";
		break;
	case '+':
		resultToken.content = "+";
		resultToken.type = "or_op";
		break;
	case '(':
		resultToken.content = "(";
		resultToken.type = "para_open";
		break;
	case ')':
		resultToken.content = ")";
		resultToken.type = "para_close";
		break;
	case ':':
		resultToken.content = ":";
		resultToken.type = "assign_op";
		break;
	case ',':
		resultToken.content = ",";
		resultToken.type = "comma";
		break;

	/* case '0':
	case '1':
		resultToken.content = line[index];
		resultToken.type = "const";
		break; */
	default:
		char temp = line[index];
		if(!isalpha(temp))
		{
			throw 0;
		}

		int cnt = 1;

		resultToken.content.push_back(temp);
		index++;

		while (index < line.length() && cnt < 10)
		{
			temp = line[index];
			if(isalnum(temp))
			{
				resultToken.content.push_back(temp);
				index++;
				cnt++;
			}
			else
			{
				break;
			}
		}
		index--;

		resultToken.type = "var";
	}

	advanceToken();

	token = resultToken;
	unused = true;

	// cout << "token : " << token.content;
	return resultToken;
}
