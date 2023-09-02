
#include "std_lib_facilities.h"
#include "mastermind.h"
#include "masterVisual.h"
#include "tests.h"

char fun(char var);

int main()
{
	
	cout << fun('b');

	return 0;
}

char fun(char var) 
{
	if (tolower(var) > 'f' - 1) return var;
	return fun(var + 1);
}