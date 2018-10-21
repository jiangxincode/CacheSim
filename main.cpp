#include "base.h"

int main()
{
	char ch = '\0';

	do
	{
		InitVariables();
		GetInput(); // get input information
		CalcInfo();
		CreateCache();
		FileTest();
		PrintOutput(); // output the result
		std::cout << "Continue/Exit(C/E)" << std::endl;
		std::cin >> ch;
	} while ((ch != 'e') && (ch != 'E'));

	return 0;
}
