#include "Differenciator.h"

const char* s = nullptr;
int p = 0;

int GetN()
{
	int val = 0;

	int save_p = p;
	while ('0' <= s[p] and s[p] <= '9')
	{
		val = val * 10 + (s[p] - '0');
		p++;
	} 
	if (p == save_p)
	{
		puts("Syntax Error");
	}
	return val;
}

int GetT()
{
	int val = GetP();

	while (s[p] == '*' or s[p] == '/')
	{
		int op = s[p];
		p++;
		int val2 = GetP();
		if (op == '*') val *= val2;
		else val /= val2;
	}
	return val;
}

int GetE()
{
	int val = GetT();

	while (s[p] == '+' or s[p] == '-')
	{
		int op = s[p];
		p++;
		int val2 = GetT();
		if (op == '+') val += val2;
		else val -= val2;
	}
	return val;
}


int GetP()
{
	if (s[p] == '(')
	{
		p++;
		int val = GetE();
		if (s[p] != ')') puts("SYNTAX ERROR");
		p++;
		return val;
	}
	else return GetN();
}


int GetG(const char* str)
{
	s = str;
	p = 0;
	int val = GetE();
	if (s[p] != '$')
		puts("SYNTAX ERROR");
	return val;
}


const char* cringe_array[1] = {
	"Очевтчно, что"
};
