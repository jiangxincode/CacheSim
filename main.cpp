#include "functions.h"

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
        ch = tolower(ch);
    }
    while(ch != 'e');
    return 0;
}
