#include "base.h"

int main(int argc, char* argv[])
{
	char ch = '\0';

	do
	{
		InitVariables();
		GetInput();
		CalcInfo();
		CreateCache();
		FileTest();
		PrintOutput();
		std::cout << "Continue/Exit(C/E)" << std::endl;
		std::cin >> ch;
	} while ((ch != 'e') && (ch != 'E'));

	return 0;
}
